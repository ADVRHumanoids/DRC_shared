#ifndef DEBRIS_MSG
#define DEBRIS_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include <vector>

class debris_msg
{
public:
    debris_msg()
    {
	command="";
	frame="";
	debris_data = KDL::Frame::Identity();
	left_hand = KDL::Frame::Identity();
	right_hand = KDL::Frame::Identity();
	length = 0.0;
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame debris_data;
    
    KDL::Frame left_hand;
    
    KDL::Frame right_hand;
    
    double length;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="debris_data")
	{
	    list.addString(frame);
	    list.addDouble(debris_data.p.x());
	    list.addDouble(debris_data.p.y());
	    list.addDouble(debris_data.p.z());
	    double qx,qy,qz,qw;
	    debris_data.M.GetQuaternion(qx,qy,qz,qw);
	    list.addDouble(qx);
	    list.addDouble(qy);
	    list.addDouble(qz);
	    list.addDouble(qw);
	    list.addDouble(length);
	}
	
	if(command=="hands_data")
	{
	    list.addString(frame);
	    list.addDouble(left_hand.p.x());
	    list.addDouble(left_hand.p.y());
	    list.addDouble(left_hand.p.z());
	    double qx,qy,qz,qw;
	    left_hand.M.GetQuaternion(qx,qy,qz,qw);
	    list.addDouble(qx);
	    list.addDouble(qy);
	    list.addDouble(qz);
	    list.addDouble(qw);
	    
	    list.addDouble(right_hand.p.x());
	    list.addDouble(right_hand.p.y());
	    list.addDouble(right_hand.p.z());
	    right_hand.M.GetQuaternion(qx,qy,qz,qw);
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

	if(command=="debris_data")
	{
	    frame = list->get(1).asString();
	    debris_data.p.x(list->get(2).asDouble());
	    debris_data.p.y(list->get(3).asDouble());
	    debris_data.p.z(list->get(4).asDouble());
	    double qx,qy,qz,qw;
	    qx = list->get(5).asDouble();
	    qy = list->get(6).asDouble();
	    qz = list->get(7).asDouble();
	    qw = list->get(8).asDouble();
	    debris_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    length = list->get(9).asDouble();
	}
	
	if(command=="hands_data")
	{
	    frame = list->get(1).asString();
	    left_hand.p.x(list->get(2).asDouble());
	    left_hand.p.y(list->get(3).asDouble());
	    left_hand.p.z(list->get(4).asDouble());
	    double qx,qy,qz,qw;
	    qx = list->get(5).asDouble();
	    qy = list->get(6).asDouble();
	    qz = list->get(7).asDouble();
	    qw = list->get(8).asDouble();
	    left_hand.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    
	    right_hand.p.x(list->get(9).asDouble());
	    right_hand.p.y(list->get(10).asDouble());
	    right_hand.p.z(list->get(11).asDouble());
	    qx = list->get(12).asDouble();
	    qy = list->get(13).asDouble();
	    qz = list->get(14).asDouble();
	    qw = list->get(15).asDouble();
	    right_hand.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	}

	return;
    }
  
};

#endif // DEBRIS_MSG