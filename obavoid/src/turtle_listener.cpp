#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Twist.h"
#include"std_msgs/String.h"
#include<string>
#include "stdlib.h"
#include"turtlesim/Pose.h"
float ROBOT_X =0;
float ROBOT_Y =0;
void poseCallback(const turtlesim::PoseConstPtr& msg)
{	
	//ROS_INFO("turtle1_postion:(%f,%f,%f)",msg->x,msg->y,msg->theta);
	ROBOT_X = msg->x;
    ROBOT_Y = msg->y;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "sub_TF");
    ros::NodeHandle nh;
    // 创建 TF 订阅对象
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    // 处理订阅到的 TF
    // 需要创建发布 /turtle2/cmd_vel 的 publisher 对象
    // follower_vel<<argv[1];
    // follower_vel<<"/cmd_vel";
    // msg.data=follower_vel.str();
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1000);
     ros::Publisher pub1 = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    ros::Subscriber sub = nh.subscribe("turtle1/pose",10,&poseCallback);
    srand(time(0));
    int iterator =0;
    ros::Rate rate(15);
    float dist1, dist2 ,dist3, dist4 =0;
    while (ros::ok())
    {

        try
        {
            //先获取 turtle1 相对 turtle2 的坐标信息
            geometry_msgs::TransformStamped tfs = buffer.lookupTransform("turtle2", "turtle1", ros::Time(0));
            geometry_msgs::TransformStamped tfs2 = buffer.lookupTransform("turtle2", "turtle3", ros::Time(0));
            geometry_msgs::TransformStamped tfs3 = buffer.lookupTransform("turtle2", "turtle4", ros::Time(0));
            geometry_msgs::TransformStamped tfs4 = buffer.lookupTransform("turtle2", "turtle5", ros::Time(0));
            geometry_msgs::TransformStamped tfs5 = buffer.lookupTransform("turtle2", "turtle6", ros::Time(0));
        
            
            dist1 = sqrt(pow(tfs2.transform.translation.x, 2) + pow(tfs2.transform.translation.y, 2));
            dist2 = sqrt(pow(tfs3.transform.translation.x, 2) + pow(tfs3.transform.translation.y, 2));
            dist3 = sqrt(pow(tfs4.transform.translation.x, 2) + pow(tfs4.transform.translation.y, 2));
            dist4 = sqrt(pow(tfs5.transform.translation.x, 2) + pow(tfs5.transform.translation.y, 2));
           
            geometry_msgs::Twist twist;
            if (dist1<1.0)
            {         
                twist.linear.x = 0.5 * sqrt(pow(tfs.transform.translation.x, 2) + pow(tfs.transform.translation.y, 2));
                twist.angular.z = -4 * atan2(tfs2.transform.translation.y, tfs2.transform.translation.x);
               //twist.angular.z = 0.785398;
            }
            else if (dist2<1.0){
                twist.linear.x = 0.5 * sqrt(pow(tfs.transform.translation.x, 2) + pow(tfs.transform.translation.y, 2));
                twist.angular.z = -4 * atan2(tfs3.transform.translation.y, tfs3.transform.translation.x);
            }
            else if (dist3<1.0){
                twist.linear.x = 0.5 * sqrt(pow(tfs.transform.translation.x, 2) + pow(tfs.transform.translation.y, 2));
                twist.angular.z = -4 * atan2(tfs4.transform.translation.y, tfs4.transform.translation.x);
            }
            else if (dist4<1.0){
                twist.linear.x = 0.5 * sqrt(pow(tfs.transform.translation.x, 2) + pow(tfs.transform.translation.y, 2));
                twist.angular.z = -4 * atan2(tfs5.transform.translation.y, tfs5.transform.translation.x);
            }
            else
            {
                twist.linear.x = 0.5 * sqrt(pow(tfs.transform.translation.x, 2) + pow(tfs.transform.translation.y, 2));
                twist.angular.z = 4 * atan2(tfs.transform.translation.y, tfs.transform.translation.x);
            }
            //发布速度信息 -- 需要提前创建 publish 对象
            pub.publish(twist);
        }
        catch (const std::exception& e)
        {
            ROS_INFO("错误提示:%s", e.what());
        }

         geometry_msgs::Twist twist;
        

       twist.linear.x=1.5;
		twist.linear.y=0.0;
		twist.linear.z=0.0;

		iterator++;
		if (iterator==30){
				iterator=0;
				twist.linear.x=0.0;
				twist.angular.z=-10+rand()%20+0.141592;
				//vel_cmd.angular.z=3.141592653;
			}
        
        if (ROBOT_X<=0.3 or  ROBOT_X>=10.5 or ROBOT_Y<=0.2 or ROBOT_Y>=11)
        {       
                 twist.linear.x=0.0;
                 twist.angular.z=3.1415926;
                 twist.linear.x=1.0;
        }
        
		pub1.publish(twist);
        rate.sleep();
        ros::spinOnce();
    }
    return 0;
}

