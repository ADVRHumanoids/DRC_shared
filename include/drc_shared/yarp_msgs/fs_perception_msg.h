#ifndef FS_PERCEPTION_MSG
#define FS_PERCEPTION_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>


class fs_perception_msg
{
public:
    std::string command;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	if(command=="send_stereo_cloud")
	{
	    list.addString(command);
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

	if(command=="send_stereo_cloud") {
	    //TODO
	}
	return;
    }
  
};

#endif // FS_PLANNER_MSG