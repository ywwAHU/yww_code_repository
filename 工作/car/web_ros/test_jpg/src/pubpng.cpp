// 发布一个png

#include <ros/ros.h>
#include <opencv2/core/core.hpp>
#include <image_transport/image_transport.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


using namespace std;
int main(int argc,char **argv){
    ros::init(argc,argv,"pub_png");
    image_transport::Publisher pub = n.advertise<sense_msgs::>("pub_png_node",1);

    cv::Mat img = cv::imread("/home/ros_util/tn.png");

    sensor_msgs::ImageConstPtr output; // 输出

    ros::Rate loop_sleep(10);
    while(ros::ok())
    {
        output =  cv_bridge::CvImage(std_msgs::Header(), "bgr8",img).toImageMsg(); // 转化发送

        pub.publish(output);
        loop_rate.sleep();
    }




    return 0;
}