#ifndef DRC_RAISE_MSG
#define DRC_RAISE_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl_parser/kdl_parser.hpp>
class drc_raise_msg
{
public:
    drc_raise_msg():reference_frame("")
    {}

    std::string reference_frame;

    int pose_number;
    std::map<std::string,KDL::Frame> poses;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();
	double qx,qy,qz,qw;
	list.addString(reference_frame);

	list.addInt(poses.size());

	for(auto pose:poses)
	{
	    list.addString(pose.first);

	    list.addDouble(pose.second.p.x());
	    list.addDouble(pose.second.p.y());
	    list.addDouble(pose.second.p.z());
	    pose.second.M.GetQuaternion(qx,qy,qz,qw);
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
            reference_frame="";
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            reference_frame="";
            return;
        }
        if (list->get(0).isNull())
        {
            reference_frame="";
            return;
        }

        reference_frame = list->get(0).asString();

	pose_number = list->get(1).asInt();

	double qx,qy,qz,qw;

	for(int i=2;i<2+pose_number*7;)
	{
	    std::string temp_str = list->get(i++).asString();

	    poses[temp_str].p.x(list->get(i++).asDouble());
	    poses[temp_str].p.y(list->get(i++).asDouble());
	    poses[temp_str].p.z(list->get(i++).asDouble());
	    
	    poses[temp_str].M = KDL::Rotation::Quaternion(list->get(i++).asDouble(),list->get(i++).asDouble(),list->get(i++).asDouble(),list->get(i++).asDouble());
	}

	return;
    }
};

#endif // DRC_RAISE_MSG