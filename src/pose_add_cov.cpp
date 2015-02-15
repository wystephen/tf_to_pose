#include <iostream>
#include "ros/ros.h"
#include "tf/tf.h"
#include "tf/transform_listener.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
using namespace std;

ros::Publisher *p;


void covcallback(const geometry_msgs::PoseStamped::ConstPtr & msg)
{

    geometry_msgs::PoseWithCovarianceStamped cov;
   cov.header = msg->header;

  cov.pose.pose=msg->pose;
    // cov.pose.covariance.at()
    for(int i=0;i<cov.pose.covariance.size();i++)
    {
        cov.pose.covariance[i]=0;
    }
    cov.pose.covariance[0] = 0.05;
    cov.pose.covariance[7] = 0.05;
    cov.pose.covariance[14]= 0.05;
    cov.pose.covariance[21] = 0.05;
    cov.pose.covariance[28] = 0.05;
    cov.pose.covariance[35] = 0.05;

    p->publish(cov);

}





int main(int argc,char **argv)
{
    ros::init(argc,argv,"pose_add_cov");
    ros::NodeHandle n;
    //ros::Publishers       `````

    ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/slam_out_pose_cov",1000);



    ros::Subscriber sub = n.subscribe("/slam_out_pose",1000,&covcallback);
    p=&pub;
    ros::spin();

}
