#ifndef DRILL_MSG
#define DRILL_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class drill_msg
{
public:
    drill_msg()
    {
	// TODO ADD RIGHT CUSTOM DATA
	command="";
	frame="";
	drill_data.p.x(0.0);
	drill_data.p.y(0.0);
	drill_data.p.z(0.0);
	drill_data.M = KDL::Rotation::Identity();
    }
  
    KDL::Frame drill_data, wall_data;
    std::string command;  
    std::string frame;
    double radius;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="drilldatasent")
	{
	    list.addString(frame);
	    list.addDouble(drill_data.p.x());
	    list.addDouble(drill_data.p.y());
	    list.addDouble(drill_data.p.z());
	    double ro,pi,ya;
	    drill_data.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	}
	
	if(command=="walldatasent")
	{
	    list.addString(frame);
	    list.addDouble(drill_data.p.x());
	    list.addDouble(drill_data.p.y());
	    list.addDouble(drill_data.p.z());
	    double ro,pi,ya;
	    drill_data.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	    list.addDouble(radius);
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
	if(command=="drilldatasent")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		drill_data = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		drill_data.p.x(list->get(index++).asDouble());
		drill_data.p.y(list->get(index++).asDouble());
		drill_data.p.z(list->get(index++).asDouble());
		double ro,pi,ya;
		ro = list->get(index++).asDouble();
		pi = list->get(index++).asDouble();
		ya = list->get(index++).asDouble();
		drill_data.M = KDL::Rotation::RPY(ro,pi,ya);
	    }
	}

	index=1;
	if(command=="walldatasent")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		drill_data = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		drill_data.p.x(list->get(index++).asDouble());
		drill_data.p.y(list->get(index++).asDouble());
		drill_data.p.z(list->get(index++).asDouble());
		double ro,pi,ya;
		ro = list->get(index++).asDouble();
		pi = list->get(index++).asDouble();
		ya = list->get(index++).asDouble();
		drill_data.M = KDL::Rotation::RPY(ro,pi,ya);
	    }
	    radius = list->get(index++).asDouble();
	}
	
	
	return;
    }
  
};

#endif // DOOR_MSG