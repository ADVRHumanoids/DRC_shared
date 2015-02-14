#ifndef VALVE_MSG
#define VALVE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include <vector>

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

    int affordances_number;

    std::vector<KDL::Frame> affordances;

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

	list.addInt(affordances_number);

	for(int i=0;i<affordances_number;i++)
	{
	    list.addDouble(affordances.at(i).p.x());
	    list.addDouble(affordances.at(i).p.y());
	    list.addDouble(affordances.at(i).p.z());
	    double qx,qy,qz,qw;
	    affordances.at(i).M.GetQuaternion(qx,qy,qz,qw);
	    list.addDouble(qx);
	    list.addDouble(qy);
	    list.addDouble(qz);
	    list.addDouble(qw);
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

	affordances.clear();
	affordances_number = list->get(9).asInt();

	int position = 9;
	for(int i=0;i<affordances_number;i++)
	{
	    KDL::Frame temp_frame;
	    temp_frame.p.x(list->get(position+1).asDouble());
	    temp_frame.p.y(list->get(position+2).asDouble());
	    temp_frame.p.z(list->get(position+3).asDouble());
	    double qx,qy,qz,qw;
	    qx = list->get(position+4).asDouble();
	    qy = list->get(position+5).asDouble();
	    qz = list->get(position+6).asDouble();
	    qw = list->get(position+7).asDouble();
	    temp_frame.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    affordances.push_back(temp_frame);
	    position+=7;
	}

	return;
    }
  
};

#endif // VALVE_MSG