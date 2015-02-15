#include <iostream>
#include "ros/ros.h"
#include "tf/tf.h"
#include "tf/transform_listener.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
using namespace std;

ros::Publisher *p;
string laser_frame("/laser");
 string odom_frame("/world");

 tf::TransformListener tflistener;

void imucallback(const sensor_msgs::Imu::ConstPtr & imumsg)
{
    tf::StampedTransform transform;

    tflistener.lookupTransform(odom_frame,laser_frame,ros::Time(),transform);

    geometry_msgs::PoseWithCovarianceStamped cov;
   cov.header.frame_id= "/odom";
   cov.header.stamp = imumsg->header.stamp;

   tf::Vector3 v = transform.getOrigin();
   tf::Quaternion q  = transform.getRotation();


  cov.pose.pose.position.x=v.getX();
  cov.pose.pose.position.y=v.getY();
  cov.pose.pose.position.z=v.getZ();

  cov.pose.pose.orientation.x=q.getX();
  cov.pose.pose.orientation.y=q.getY();
  cov.pose.pose.orientation.z=q.getZ();
  cov.pose.pose.orientation.w=q.getW();

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
    ros::init(argc,argv,"posetwod_add_cov");

    ros::NodeHandle n;
    //ros::Publishers       `````

    ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/slam_out_pose_cov",1000);



    ros::Subscriber sub = n.subscribe("/imu/data",100,&imucallback);
    p=&pub;
    ros::spin();

}
