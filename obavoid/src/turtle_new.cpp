#include "ros/ros.h"
#include "turtlesim/Spawn.h"
#include <string>
int main(int argc,char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc,argv,"turtle_new");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("/spawn");
    ros::service::waitForService("/spawn");

    turtlesim::Spawn turtle2;
    turtle2.request.name = "turtle2";
    turtle2.request.x = 1.0;
    turtle2.request.y = 2.0;
    turtle2.request.theta = 3.12415926; 
    bool flag2 = client.call(turtle2);
        if (flag2)
        {
            ROS_INFO("乌龟%s创建成功!", turtle2.response.name.c_str());
        }
        else
        {
            ROS_INFO("乌龟创建失败!");
        }
    

    turtlesim::Spawn turtle3;
    turtle3.request.name = "turtle3";
    turtle3.request.x = 5.0;
    turtle3.request.y = 3.0;
    turtle3.request.theta = 6.12;
    bool flag3 = client.call(turtle3);
        if (flag3)
        {
            ROS_INFO("乌龟%s创建成功!", turtle3.response.name.c_str());
        }
        else
        {
            ROS_INFO("乌龟创建失败!");
        }

    turtlesim::Spawn turtle4;
    turtle4.request.name = "turtle4";
    turtle4.request.x = 8.0;
    turtle4.request.y = 6.0;
    turtle4.request.theta = 2.1564;
    bool flag4 = client.call(turtle4);
        if (flag4)
        {
            ROS_INFO("乌龟%s创建成功!", turtle4.response.name.c_str());
        }
        else
        {
            ROS_INFO("乌龟创建失败!");
        }


    turtlesim::Spawn turtle5;
    turtle5.request.name = "turtle5";
    turtle5.request.x = 4.6;
    turtle5.request.y = 8.50;
    turtle5.request.theta = 6.12;
    bool flag5 = client.call(turtle5);
        if (flag5)
        {
            ROS_INFO("乌龟%s创建成功!", turtle5.response.name.c_str());
        }
        else
        {
            ROS_INFO("乌龟创建失败!");
        }

    turtlesim::Spawn turtle6;
    turtle6.request.name = "turtle6";
    turtle6.request.x = 10.0;
    turtle6.request.y = 2.0;
    turtle6.request.theta = 6.12;
    bool flag6 = client.call(turtle6);
        if (flag6)
        {
            ROS_INFO("乌龟%s创建成功!", turtle6.response.name.c_str());
        }
        else
        {
            ROS_INFO("乌龟创建失败!");
        }

    ros::spin();
    return 0;
}