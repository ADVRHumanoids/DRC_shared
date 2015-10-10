#ifndef MANIPULATION_MSG
#define MANIPULATION_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class manipulation_msg
{
public:
    manipulation_msg()
    {
	command="";
	frame="";
	left_hand.p.x(0.0);
	left_hand.p.y(0.0);
	left_hand.p.z(0.0);
	left_hand.M = KDL::Rotation::Identity();
	right_hand.p.x(0.0);
	right_hand.p.y(0.0);
	right_hand.p.z(0.0);
	right_hand.M = KDL::Rotation::Identity();
    }
  
    KDL::Frame left_hand, right_hand;
    bool left=true;
    bool right=true;
    std::string command;  
    std::string frame;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="data_sent")
	{
	    list.addString(frame);
	    list.add(yarp_KDL::getBlob(left_hand));
	    list.add(yarp_KDL::getBlob(right_hand));
	    list.addInt(left);
	    list.addInt(right);
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
	if(command=="data_sent")
	{
	    frame = list->get(index++).asString();

	    if(list->get(index).asBlobLength()!=0)
	    {
		left_hand = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		left_hand.p.x(list->get(index++).asDouble());
		left_hand.p.y(list->get(index++).asDouble());
		left_hand.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		left_hand.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	    
	    if(list->get(index).asBlobLength()!=0)
	    {
		right_hand = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		right_hand.p.x(list->get(index++).asDouble());
		right_hand.p.y(list->get(index++).asDouble());
		right_hand.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		right_hand.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	    
	    left = list->get(index++).asInt();
	    right = list->get(index++).asInt();
	}

	return;
    }
};

#endif // MANIPULATION_MSG