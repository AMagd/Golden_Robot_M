#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "math.h"

int main(int argc, char **argv)
{

  ros::init(argc, argv, "controller");

  ros::NodeHandle n;

  ros::Publisher controller = n.advertise<sensor_msgs::JointState>("joint_states", 1000);
  
  int freq = 30;
  double f = 6.28319;
  
  ros::Rate loop_rate(freq);

  float home_time = 2; // go back to home position in 5 seconds
  float motion_time = 10;
  float motion_steps = motion_time*freq;
  float home_steps = home_time*freq;

  float angle1 = 0;
  float angle2 = -f/4;
  float angle3 = f/2;
  float angle4 = f/2;

  int counter = 0;

  for (int i=0; i<=3*freq; i++){

  sensor_msgs::JointState msg;
  msg.header.stamp = ros::Time::now();
  msg.name = {"links-0-1","links-2-3","links-3-4","links-4-5"};
  msg.position = {angle1,angle2,angle3,angle4};

  controller.publish(msg);

  ros::spinOnce();

  loop_rate.sleep();
  }

  ros::Duration(5).sleep();

  while (ros::ok() && counter <= motion_steps)
  {
    sensor_msgs::JointState msg;
    angle1 += 0.5*sin(0.01*counter);
    angle2 += 0.05;
    angle3 += 0.01;
    angle4 += 0.01;
    msg.header.stamp = ros::Time::now();
    msg.name = {"links-0-1","links-2-3","links-3-4","links-4-5"};
    msg.position = {angle1,angle2,angle3,angle4};

    controller.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();

    counter++;
  }

  double angle11 = remainder(angle1, f) + f/2;
  angle11 = remainder(angle11, f);
  double angle22 = remainder(angle2, f) + f/4;
  angle22 = remainder(angle22, f);
  double angle33 = remainder(angle3, f) + f/2;
  angle33 = remainder(angle33, f);
  double angle44 = remainder(angle4, f) + f/2;
  angle44 = remainder(angle44, f);

  float home_angle1 = angle11/home_steps;
  float home_angle2 = angle22/home_steps;
  float home_angle3 = angle33/home_steps;
  float home_angle4 = angle44/home_steps;

  ros::Duration(0.5).sleep();

  for(int i=0; i<home_steps; i++){

    sensor_msgs::JointState msg;

    angle1 -= home_angle1;

    msg.header.stamp = ros::Time::now();
    msg.name = {"links-0-1","links-2-3","links-3-4","links-4-5"};
    msg.position = {angle1,angle2,angle3,angle4};

    controller.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  for(int i=0; i<home_steps; i++){

    sensor_msgs::JointState msg;

    angle2 -= home_angle2;

    msg.header.stamp = ros::Time::now();
    msg.name = {"links-0-1","links-2-3","links-3-4","links-4-5"};
    msg.position = {angle1,angle2,angle3,angle4};

    controller.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  for(int i=0; i<home_steps; i++){

    sensor_msgs::JointState msg;

    angle3 -= home_angle3;

    msg.header.stamp = ros::Time::now();
    msg.name = {"links-0-1","links-2-3","links-3-4","links-4-5"};
    msg.position = {angle1,angle2,angle3,angle4};

    controller.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  for(int i=0; i<home_steps; i++){

    sensor_msgs::JointState msg;

    angle4 -= home_angle4;

    msg.header.stamp = ros::Time::now();
    msg.name = {"links-0-1","links-2-3","links-3-4","links-4-5"};
    msg.position = {angle1,angle2,angle3,angle4};

    controller.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }
  
  
    return 0;
}