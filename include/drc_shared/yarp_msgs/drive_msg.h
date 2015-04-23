#ifndef DRIVE_MSG
#define DRIVE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class drive_msg
{
public:
    drive_msg()
    {
	// TODO ADD RIGHT CUSTOM DATA
	command="";
	frame="";
	drive_data.p.x(0.0);
	drive_data.p.y(0.0);
	drive_data.p.z(0.0);
	drive_data.M = KDL::Rotation::Identity();
    }
  
    KDL::Frame drive_data;
    std::string command;  
    std::string frame;
    double radius;
    double angle;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="steeringwheeldatasent")
	{
	    list.addString(frame);
	    list.add(yarp_KDL::getBlob(drive_data));
	    list.addDouble(radius);
	}
	
	if(command=="turn_left" || command=="turn_right")
	{
	    list.addDouble(angle);
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
	if(command=="steeringwheeldatasent")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		drive_data = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		drive_data.p.x(list->get(index++).asDouble());
		drive_data.p.y(list->get(index++).asDouble());
		drive_data.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		drive_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	    radius = list->get(index++).asDouble();
	}
	
	if(command=="turn_left" || command=="turn_right")
	{
	    angle = list->get(1).asDouble();
	}
	
	return;
    }
  
};

#endif // DRIVE_MSG