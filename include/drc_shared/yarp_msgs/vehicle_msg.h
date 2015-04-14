#ifndef VEHICLE_MSG
#define VEHICLE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

class vehicle_msg
{
public:
    vehicle_msg()
    {
	// TODO ADD RIGHT CUSTOM DATA
	command="";
	frame="";
	vehicle_data.p.x(0.0);
	vehicle_data.p.y(0.0);
	vehicle_data.p.z(0.0);
	vehicle_data.M = KDL::Rotation::Identity();
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame vehicle_data;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="vehicledatasent")
	{
	    list.addString(frame);
	    list.addDouble(vehicle_data.p.x());
	    list.addDouble(vehicle_data.p.y());
	    list.addDouble(vehicle_data.p.z());
	    double ro,pi,ya;
	    vehicle_data.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
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

	if(command=="vehicledatasent")
	{
	    frame = list->get(1).asString();
	    vehicle_data.p.x(list->get(2).asDouble());
	    vehicle_data.p.y(list->get(3).asDouble());
	    vehicle_data.p.z(list->get(4).asDouble());
	    double ro,pi,ya;
	    ro = list->get(5).asDouble();
	    pi = list->get(6).asDouble();
	    ya = list->get(7).asDouble();
	    vehicle_data.M = KDL::Rotation::RPY(ro,pi,ya);
	}

	return;
    }
};

#endif // VEHICLE_MSG