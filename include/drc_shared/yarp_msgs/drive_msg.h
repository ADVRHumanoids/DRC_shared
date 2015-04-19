#ifndef DRIVE_MSG
#define DRIVE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

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

	if(command=="drivedatasent")
	{
	    list.addString(frame);
	    list.addDouble(drive_data.p.x());
	    list.addDouble(drive_data.p.y());
	    list.addDouble(drive_data.p.z());
	    double ro,pi,ya;
	    drive_data.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	    list.addDouble(radius);
	}
	
	if(command=="turn_left")
	{
	    list.addDouble(angle);
	}
	
	if(command=="turn_right")
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

	if(command=="drivedatasent")
	{
	    frame = list->get(1).asString();
	    drive_data.p.x(list->get(2).asDouble());
	    drive_data.p.y(list->get(3).asDouble());
	    drive_data.p.z(list->get(4).asDouble());
	    double ro,pi,ya;
	    ro = list->get(5).asDouble();
	    pi = list->get(6).asDouble();
	    ya = list->get(7).asDouble();
	    drive_data.M = KDL::Rotation::RPY(ro,pi,ya);
	    radius = list->get(8).asDouble();
	}
	
	if(command=="turn_left")
	{
	    angle = list->get(1).asDouble();
	}
	
	if(command=="turn_right")
	{
	    angle = list->get(1).asDouble();
	}
	return;
    }
  
};

#endif // DRIVE_MSG