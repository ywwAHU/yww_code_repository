#include <iostream> 
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
 
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include "std_msgs/String.h"

#include <string>
#include <vector>

using namespace std;
using namespace cv;

bool Base64Encode(const string& input, string* output) 
{
    typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<string::const_iterator, 6, 8> > Base64EncodeIterator;
    stringstream result;
    copy(Base64EncodeIterator(input.begin()) , Base64EncodeIterator(input.end()), ostream_iterator<char>(result));
    size_t equal_count = (3 - input.length() % 3) % 3;
    for (size_t i = 0; i < equal_count; i++) {
        result.put('=');
    }
    *output = result.str();
    return output->empty() == false;
}

class SubscribeAndPublish
{
private:
	ros::Publisher  pub;
	image_transport::Subscriber sub;
 
public:



	SubscribeAndPublish(ros::NodeHandle &nh, image_transport::ImageTransport &it)
	{
		pub = nh.advertise<std_msgs::String>("/jpg_string",1);
		sub = it.subscribe("/pub_png_node", 1, &SubscribeAndPublish::callback, this);   //订阅的节点
	}
 
	void thresholdImage(const sensor_msgs::ImageConstPtr& msg, std_msgs::String& out)
	{
		Mat img = cv_bridge::toCvShare(msg, "bgr8")->image;
        string output_str;
        
        holdImagehelper(img,output_str);
        out.data = output_str;        
        
	}

    void holdImagehelper(const Mat &img,string& output_str)
    {
        //  resize->jpg->based64;
        Mat res;
        cv::resize(img,res,cv::Size(100,70),0,0,INTER_AREA);

        // jpg
        vector<unsigned char> buff;
        cv::imencode(".jpg", res, buff);
        string strJPGData = string(buff.begin(), buff.end());

        // based64
        Base64Encode(strJPGData,&output_str);

        cout << strJPGData.size()<<endl;
    }
 
	void callback(const sensor_msgs::ImageConstPtr& msg)
	{
		std_msgs::String output;
		thresholdImage(msg,output);
		pub.publish(output);
	}
};//End of class SubscribeAndPublish


int main(int argc, char **argv)
{
	//Initiate ROS
	ros::init(argc, argv, "jpg_string_pub");
	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
 
	//cv::namedWindow("Image");
	//cv::startWindowThread();
	//Create an object of class SubscribeAndPublish that will take care of everything
	SubscribeAndPublish SAPObject(nh,it);
 
	ros::spin();
	//cv::destroyWindow("Image"); 
	return 0;
}
