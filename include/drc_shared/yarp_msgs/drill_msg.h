#ifndef DRILL_MSG
#define DRILL_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

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

	if(command=="drilldatasent")
	{
	    frame = list->get(1).asString();
	    drill_data.p.x(list->get(2).asDouble());
	    drill_data.p.y(list->get(3).asDouble());
	    drill_data.p.z(list->get(4).asDouble());
	    double ro,pi,ya;
	    ro = list->get(5).asDouble();
	    pi = list->get(6).asDouble();
	    ya = list->get(7).asDouble();
	    drill_data.M = KDL::Rotation::RPY(ro,pi,ya);
	}
	
	if(command=="walldatasent")
	{
	    frame = list->get(1).asString();
	    drill_data.p.x(list->get(2).asDouble());
	    drill_data.p.y(list->get(3).asDouble());
	    drill_data.p.z(list->get(4).asDouble());
	    double ro,pi,ya;
	    ro = list->get(5).asDouble();
	    pi = list->get(6).asDouble();
	    ya = list->get(7).asDouble();
	    drill_data.M = KDL::Rotation::RPY(ro,pi,ya);
	    radius = list->get(8).asDouble();
	}
	return;
    }
  
};

#endif // DOOR_MSG