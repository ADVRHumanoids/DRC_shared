#ifndef PLUG_MSG
#define PLUG_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class plug_msg
{
public:
    plug_msg()
    {
	// TODO ADD RIGHT CUSTOM DATA
	command="";
	frame="";
	valve_data.p.x(0.0);
	valve_data.p.y(0.0);
	valve_data.p.z(0.0);
	valve_data.M = KDL::Rotation::Identity();
    }
  
    KDL::Frame valve_data, button_data;
    std::string command;  
    std::string frame;
    double angle;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="rotate")
	{
	  list.addDouble(angle);
	}
	
	if(command=="valvedatasent")
	{
	    list.addString(frame);
	    list.add(yarp_KDL::getBlob(valve_data));
	}
	
	if(command=="buttondatasent")
        {
            list.addString(frame);
            list.add(yarp_KDL::getBlob(button_data));
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
	if(command=="valvedatasent")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		valve_data = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		valve_data.p.x(list->get(index++).asDouble());
		valve_data.p.y(list->get(index++).asDouble());
		valve_data.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		valve_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	}

	index=1;
        if(command=="buttondatasent")
        {
            frame = list->get(index++).asString();
            if(list->get(index).asBlobLength()!=0)
            {
                button_data = yarp_KDL::fromBlob(list->get(index++));
            }
            else
            {  
                button_data.p.x(list->get(index++).asDouble());
                button_data.p.y(list->get(index++).asDouble());
                button_data.p.z(list->get(index++).asDouble());
                double qx,qy,qz,qw;
                qx = list->get(index++).asDouble();
                qy = list->get(index++).asDouble();
                qz = list->get(index++).asDouble();
                qw = list->get(index++).asDouble();
                button_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
            }
	}

	index=1;
	if(command=="rotate")
	{
	    angle = list->get(1).asDouble();
	}
	
	return;
    }
};

#endif // PLUG_MSG