#include <ros/ros.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <cv_bridge/cv_bridge.h>
#include <string>
#include <vector>

ros::Publisher *pub;


void getpic(const sensor_msgs::Image::ConstPtr &img_msg) {
    vector<unsigned char> buff;

    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(img_msg, sensor_msgs::image_encodings::BGR8);
    cv::Mat img = cv_ptr->image;
    
    // 转jpe
    cv::imencode(".jpg", img, buff);
    string strJPGData = string(buff.begin(), buff.end());

}


int main(int argc, char **argv)
{
    ros::init(argc, argv , "节点名");
    ros::NodeHandle n;
    
    ros::Subscriber sub = n.subscriber("节点名", 1, getpic); // getcallback 为 回传函数
    ros::Publisher  pic_pub = n.advertise<std_msgs::String>("json",1) // 发布
    pub = & pic_pub;

}