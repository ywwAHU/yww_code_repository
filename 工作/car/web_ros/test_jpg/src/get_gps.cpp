#include <iostream>
#include <ros/ros.h>

#include <getPng/ivsensorgps.h> //gps消息
#include "std_msgs/String.h"

#include <string>
#include <vector>

using namespace std;

class SubscribeAndPublish
{
private:
        ros::Publisher pub;

        ros::Subscriber sub;

public:
        SubscribeAndPublish(ros::NodeHandle &nh)
        {
                pub = nh.advertise<std_msgs::String>("/jpg_string", 1);
                sub = nh.subscribe("/gpsimu", 1, &SubscribeAndPublish::callback, this); //订阅的节点
        }

        void thresholdImage(const getPng::ivsensorgps &gps_msg, std_msgs::String &out)
        {
                string lon = std::to_string(gps_msg.lon);
                string lat = std::to_string(gps_msg.lat);
                // string param_;
                // ros::param::get("",param_);

                out.data = lon + ',' + lat;
        }

        void callback(const getPng::ivsensorgps &msg)
        {
                std_msgs::String output;
                thresholdImage(msg, output);
                pub.publish(output);
        }
}; // End of class SubscribeAndPublish

int main(int argc, char **argv)
{
        // Initiate ROS
        ros::init(argc, argv, "gps_string_pub");
        ros::NodeHandle nh;

        SubscribeAndPublish SAPObject(nh);

        string tag;
        ros::param::get("/rosdistro", tag);   // 直接读取参数
        cout << tag << endl;
        
        
        
        ros::spin();

        return 0;
}
