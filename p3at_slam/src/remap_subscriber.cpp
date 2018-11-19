#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sstream>



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
