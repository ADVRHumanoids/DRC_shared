#ifndef VALVE_MSG
#define VALVE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

class valve_msg
{
public:
    valve_msg()
    {
	command="";
	frame="";
	valve_data.p.x(0.25);
	valve_data.p.y(0.0);
	valve_data.p.z(0.2);
	valve_data.M = KDL::Rotation::Identity();
	radius=0.13;
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame valve_data;
    
    double radius;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="valvedatasent")
	{
	    list.addString(frame);
	    list.addDouble(valve_data.p.x());
	    list.addDouble(valve_data.p.y());
	    list.addDouble(valve_data.p.z());
	    double ro,pi,ya;
	    valve_data.M.GetRPY(ro,pi,ya);
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

	if(command=="valvedatasent")
	{
	    frame = list->get(1).asString();
	    valve_data.p.x(list->get(2).asDouble());
	    valve_data.p.y(list->get(3).asDouble());
	    valve_data.p.z(list->get(4).asDouble());
	    double ro,pi,ya;
	    ro = list->get(5).asDouble();
	    pi = list->get(6).asDouble();
	    ya = list->get(7).asDouble();
	    valve_data.M = KDL::Rotation::RPY(ro,pi,ya);
	    radius = list->get(8).asDouble();
	}

	return;
    }
  
};

#endif // VALVE_MSG