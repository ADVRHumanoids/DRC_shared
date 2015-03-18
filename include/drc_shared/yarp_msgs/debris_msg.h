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
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame debris_data;

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
	}

	return;
    }
  
};

#endif // DEBRIS_MSG