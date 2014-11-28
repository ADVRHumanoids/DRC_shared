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
 
 
# How to add a new message

- Create a new file similar to the following one:

```javascript
#ifndef A_NAME_MSG_H
#define A_NAME_MSG_H

#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>

/*
 * MESSAGE STRUCTURE EXAMPLE
 * 
 * N° of joints | "robot joints" | values
 * 
 * e.g: 3 robot joints 0.3 0.4 0.1
 * 
 */

class a_name_msg
{
public:
    
    //DATA STRUCTURE HERE, make your own
    std::map<std::string,double> joints;
        
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

        //ADD YOUR OWN STUFF HERE
    	list.addString("robot joints");
    	list.addInt(joints.size());
    	for(std::map<std::string,double>::iterator it=joints.begin();it!=joints.end();++it)
    	{
    	    list.addString(it->first);
    	    list.addDouble(it->second);
    	}
    	
        return temp;
    }
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        yarp::os::Bottle* list = temp->get(0).asList();
	
	    //READ YOUR OWN STUFF HERE IN THE SAME ORDER AS WRITING
    	std::string header = list->get(0).asString();
    	int joint_number = list->get(1).asInt();
    	unsigned int j=2;
    	for(unsigned int i=0; i<joint_number;i++)
    	{
    	    joints[list->get(j).asString()] = list->get(j+1).asDouble(); 
    	    j+=2;
    	}
    
    	return;
    }
  
};

#endif // A_NAME_MSG_H
```