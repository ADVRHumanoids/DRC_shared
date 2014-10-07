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
	if(command=="direction")
	{
	}
	if (command=="plan_num")
        {
        }
        if(command=="ik_check" || command=="ik_com_check" || command=="custom_step")
	{
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

	if(command=="direction")
	{
	}
	if (command=="plan_num")
        {
        }
        if(command=="ik_check" || command=="ik_com_check" || command=="custom_step")
	{
	}
	return;
    }
  
};


class fs_perception_patch_msg
{
public:
    std::string command;
    KDL::Frame patch;
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();
        
        list.addString(command);
        if(command=="direction")
        {
        }
        if (command=="plan_num")
        {
        }
        if(command=="ik_check" || command=="ik_com_check" || command=="custom_step")
        {
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
        
        if(command=="direction")
        {
        }
        if (command=="plan_num")
        {
        }
        if(command=="ik_check" || command=="ik_com_check" || command=="custom_step")
        {
        }
        return;
    }
    
};
#endif // FS_PLANNER_MSG