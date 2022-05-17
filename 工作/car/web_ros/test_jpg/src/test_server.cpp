#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

//#include <cv_bridge/cv_bridge.h>
#include <string>
#include <vector>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include "std_msgs/String.h"





using namespace std;

bool Base64Encode(const string& input, string* output) {
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

int main(int argc, char **argv)
{
    ros::init(argc,argv,"jpg_string_pub");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::String>("jpg_string",1);


    vector<unsigned char> buff;
    cv::Mat img = cv::imread("/home/ros_util/tn.png");



    cout << img.size()<<endl;
    cv::imencode(".jpg", img, buff);
    string strJPGData = string(buff.begin(), buff.end());
    string output_str;
    Base64Encode(strJPGData,&output_str) ;
   // cout << output_str.size()<<endl;
    //std_msgs::String msg;
    //msg.data = output_str;
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        std_msgs::String msg;
        //Base64Encode(strJPGData,&output_str) ;
        msg.data = output_str;
        pub.publish(msg);
        loop_rate.sleep();
    }



    return 0;

}
