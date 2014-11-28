# drc_shared

This repository is a generic container of classes and utilities shared among all the other projects.
It contains:

* yarp_rpc_interface.hpp
    Public yarp_rpc interface wrapper around the yarp rpc port (simplifies usage and construction)
* internal_yarp_rpc_interface.hpp
    Internal implementation of the yarp_rpc_interface 
* planner_msgs
    A set of yarp messages headers related to the flat_walk planner
* state_machine.hpp
    A simple and easy to use state machine, do not use this for complex (more than 30 state) state machines
* utils
   Nothing important here at this time of writing
* yarp_grabbers
   A set of ros-like publishers/subscribers implemented with yarp, to be used for the flat_walk planner
* yarp_msgs
    A set of yarp messages headers (see below)



* ./include/drc_shared/yarp_msgs:
 * door_msg.h
 * fs_perception_msg.h
 * fs_planner_msg.h
 * fs_walking_msg.h
 * robotInterfaceStatus.h
 * robot_planned_state_msg.h
 * TickTime.h
 * trj_generator_msg.h
 * valve_msg.h
 * YARP_Header.h
 * YARP_OccupancyGrid_msg.h
 * YARP_PCLPointField.h
 * YARP_PointCloud2.h
 * YARP_Point.h
 * YARP_Pose.h
 * YARP_Quaternion.h