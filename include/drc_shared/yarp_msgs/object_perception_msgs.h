#ifndef OBJECT_PERCEPTION_MSGS
#define OBJECT_PERCEPTION_MSGS

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl_parser/kdl_parser.hpp>
class object_perception_in_msg
{
public:
    object_perception_in_msg():command("")
    {}

    std::string command;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

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

	return;
    }
  
};


class object_perception_out_msg
{
public:
    std::string reference_frame;
    double radius;
    KDL::Frame object_pose;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(reference_frame);
	list.addDouble(radius);
	
	list.addDouble(object_pose.p.x());
	list.addDouble(object_pose.p.y());
	list.addDouble(object_pose.p.z());
	double qx,qy,qz,qw;
	object_pose.M.GetQuaternion(qx,qy,qz,qw);
	list.addDouble(qx);
	list.addDouble(qy);
	list.addDouble(qz);
	list.addDouble(qw);

        return temp;
    }
    
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            reference_frame="";
	    radius=0;
	    object_pose = KDL::Frame::Identity();
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            reference_frame="";
	    radius=0;
	    object_pose = KDL::Frame::Identity();
            return;
        }
        if (list->get(0).isNull())
        {
            reference_frame="";
	    radius=0;
	    object_pose = KDL::Frame::Identity();
            return;
        }

        reference_frame = list->get(0).asString();
        radius=list->get(1).asDouble();
        
	object_pose.p.x(list->get(2).asDouble());
	object_pose.p.y(list->get(3).asDouble());
	object_pose.p.z(list->get(4).asDouble());
	double qx,qy,qz,qw;
	qx = list->get(5).asDouble();
	qy = list->get(6).asDouble();
	qz = list->get(7).asDouble();
	qw = list->get(8).asDouble();
	object_pose.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);

	return;
    }
  
};

#endif // OBJECT_PERCEPTION_MSGS