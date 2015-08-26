#ifndef COM_MSG
#define COM_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class com_msg
{
public:
    com_msg()
    {
	// TODO ADD RIGHT CUSTOM DATA
	command="";
	frame="";
	com_data.p.x(0.0);
	com_data.p.y(0.0);
	com_data.p.z(0.0);
	com_data.M = KDL::Rotation::Identity();
	handle_length=0.1;
	com_width=0.5;
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame com_data;
    
    double handle_length, com_width;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="comdatasent")
	{
	    list.addString(frame);
	    list.add(yarp_KDL::getBlob(com_data));
	    list.addDouble(handle_length);
	    list.addDouble(com_width);
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
	if(command=="comdatasent")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		com_data = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		com_data.p.x(list->get(index++).asDouble());
		com_data.p.y(list->get(index++).asDouble());
		com_data.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		com_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	    handle_length = list->get(index++).asDouble();
	    com_width = list->get(index++).asDouble();
	}

	return;
    }
  
};

#endif // COM_MSG
