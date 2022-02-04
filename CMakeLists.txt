cmake_minimum_required(VERSION 2.8.3)
project(save_gps)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy sensor_msgs genmsg)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(save_gps src/save_gps.cpp)
target_link_libraries(save_gps ${catkin_LIBRARIES})