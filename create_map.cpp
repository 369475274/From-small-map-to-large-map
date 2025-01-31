#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <tf/transform_listener.h>
  //  std::vector<uint8_t> globalData;  
void grid( ros::NodeHandle n,double x, double y, int height,int width)
{
    ros::Publisher pub = n.advertise<nav_msgs::OccupancyGrid>("/map3",10);
    ros::Publisher pub1=n.advertise<nav_msgs::OccupancyGrid>("/gas_map",10);
    ros::Rate r(1);
      tf::TransformListener listener;
  while (ros::ok()) {
    tf::StampedTransform transform;
    try {
      listener.lookupTransform("map", "base_footprint"， ros::Time(0), transform);
      x = transform.getOrigin().x();
     y = transform.getOrigin().y();
    } 
    catch (tf::TransformException& ex) {
      ROS_ERROR("%s", ex.what());
     x =0.0;
     y = 0.0;
    }
        nav_msgs::OccupancyGrid msg;
        msg.header.frame_id = "map";
        msg.header.stamp = ros::Time::now();
        msg.info.origin.position.x =x-0.2;
        msg.info.origin.position.y = y-0.2;
        msg.info.resolution =0.05;
        msg.info.width = width;
        msg.info.height = height;
        msg.data.resize(width*height);
        msg.data[0] =-125.5;
        msg.data[1] = -100;
        msg.data[2] = -90;
        msg.data[3] = -85;
        msg.data[4] = -80;
        msg.data[5] = -70;
        msg.data[6] = -60;
        msg.data[7] = -50;
        msg.data[8] =-40;
        msg.data[9] = -30;
        msg.data[10] = -90;
        msg.data[11] = -85;
        msg.data[12] = -80;
        msg.data[13] = -70;
        msg.data[14] = -60;
        msg.data[15] = -50;
        pub.publish(msg);
        nav_msgs::OccupancyGrid msg1;
        msg1.header.frame_id="map";
        msg1.header.stamp = ros::Time::now();
        msg1.info.origin.position.x =-9;
        msg1.info.origin.position.y = -4;
        msg1.info.resolution =0.1;
        msg1.info.width = 55;
        msg1.info.height =32;
        double t=55*(4*(y+4)-1)+4*(x+9);
        // double t=861;
         msg1.data.resize(55*32);
        msg1.data[t]=-90;
        pub1.publish(msg1);
        ROS_INFO("%f,%f",x,y);
        r.sleep();
        ros::Duration(1.0)。sleep();
}
}
int main(int argc, char** argv) {
  ros::init(argc, argv, "robot_position");
  ros::NodeHandle nh;
    double x;
    double y ;
    int width =4;
    int height=4;
     grid(nh,x,y,height,width);
    return 0;
}
