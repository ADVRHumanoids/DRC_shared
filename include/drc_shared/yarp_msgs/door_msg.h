#ifndef DOOR_MSG
#define DOOR_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class door_msg
{
public:
    door_msg()
    {
	// TODO ADD RIGHT CUSTOM DATA
	command="";
	frame="";
	door_data.p.x(0.0);
	door_data.p.y(0.0);
	door_data.p.z(0.0);
	door_data.M = KDL::Rotation::Identity();
	handle_length=0.1;
	door_width=0.5;
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame door_data;
    
    double handle_length, door_width;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="doordatasent")
	{
	    list.addString(frame);
	    list.add(yarp_KDL::getBlob(door_data));
	    list.addDouble(handle_length);
	    list.addDouble(door_width);
	}
	
        return temp;
    }

    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            command="";
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            command="";
            return;
        }
        if (list->get(0).isNull())
        {
            command="";
            return;
        }

        command = list->get(0).asString();

	int index=1;
	if(command=="doordatasent")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		door_data = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		door_data.p.x(list->get(index++).asDouble());
		door_data.p.y(list->get(index++).asDouble());
		door_data.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		door_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	    handle_length = list->get(index++).asDouble();
	    door_width = list->get(index++).asDouble();
	}

	return;
    }
  
};

#endif // DOOR_MSG