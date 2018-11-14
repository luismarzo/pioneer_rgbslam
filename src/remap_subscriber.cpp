#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sstream>

/*

void Callback(const geometry_msgs::Twist::ConstPtr& msg)
{
// std::cout<<"linear_x:"<< msg->linear.x<<std::endl;
// std::cout<<"linear_y:"<< msg->linear.y<<std::endl;
// std::cout<<"linear_z:"<< msg->linear.z<<std::endl;
// std::cout<<"angular_x:"<< msg->angular.x<<std::endl;
// std::cout<<"angular_y:"<< msg->angular.y<<std::endl;
// std::cout<<"angular_z:"<< msg->angular.z<<std::endl;
flag=1;

std::cout<<"publishing msg"<<std::endl;
pub.publish(msg);
}

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "cmd_vel_subs_pub");

  
  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe("cmd_vel", 1000, Callback);

 
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel", 1000);
  ros::spin();



  return 0;
}

*/

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_ = n_.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel", 1);

    //Topic you want to subscribe
    sub_ = n_.subscribe("/cmd_vel", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const geometry_msgs::Twist& input)
  {
    geometry_msgs::Twist output;
    //.... do something with the input and generate the output...
    pub_.publish(input);
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;

  ros::spin();

  return 0;
}