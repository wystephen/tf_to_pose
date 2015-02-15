#include <iostream>
#include "ros/ros.h"
#include "tf/tf.h"
#include "tf/transform_listener.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "tf/transform_listener.h"

#include "sensor_msgs/Imu.h"
using namespace std;








ros::Publisher *p;
////////////////////////////////////////////////////

//void imucallback(const sensor_msgs::Imu::ConstPtr & imumsg)
//{
//    tf::StampedTransform transform;

//    tflistener.lookupTransform(odom_frame,laser_frame,ros::Time(),transform);

//    geometry_msgs::PoseWithCovarianceStamped cov;
//   cov.header.frame_id= "/odom";
//   cov.header.stamp = imumsg->header.stamp;

//   tf::Vector3 v = transform.getOrigin();
//   tf::Quaternion q  = transform.getRotation();


//  cov.pose.pose.position.x=v.getX();
//  cov.pose.pose.position.y=v.getY();
//  cov.pose.pose.position.z=v.getZ();

//  cov.pose.pose.orientation.x=q.getX();
//  cov.pose.pose.orientation.y=q.getY();
//  cov.pose.pose.orientation.z=q.getZ();
//  cov.pose.pose.orientation.w=q.getW();

//    // cov.pose.covariance.at()
//    for(int i=0;i<cov.pose.covariance.size();i++)
//    {
//        cov.pose.covariance[i]=0;
//    }
//    cov.pose.covariance[0] = 0.05;
//    cov.pose.covariance[7] = 0.05;
//    cov.pose.covariance[14]= 0.05;
//    cov.pose.covariance[21] = 0.05;
//    cov.pose.covariance[28] = 0.05;
//    cov.pose.covariance[35] = 0.05;

//    p->publish(cov);
//}



int main(int argc,char **argv)
{
    ros::init(argc,argv,"tf_to_pose_node");
    ros::NodeHandle n;
    //ros::Publishers       `````

    ros::Publisher pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/slam_out_pose_cov",1000);
    tf::TransformListener tflistener;


    //ros::Rate loop_rate(10);
   string laser_frame("base_link");
    string odom_frame("map");
    tflistener.waitForTransform(odom_frame,laser_frame,ros::Time(),ros::Duration(1.0));

    p=&pub;
    //ros::Subscriber sub = n.subscribe("/imu/data",1000,&imucallback);



    while(1)
    {
        tf::StampedTransform transform;

        tflistener.lookupTransform("world","base_link",ros::Time(),transform);

        geometry_msgs::PoseWithCovarianceStamped cov;
       cov.header.frame_id= "map";
       cov.header.stamp = ros::Time::now();

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
        //ros::s
    }
    ros::spin();

}
