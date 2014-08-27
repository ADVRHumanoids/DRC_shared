#ifndef FS_PLANNER_MSG
#define FS_PLANNER_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>

class fs_planner_msg
{
public:
    double x,y,z;
    std::string command;
    int num_steps;
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	if(command=="direction")
	{
	    list.addDouble(x);
	    list.addDouble(y);
	    list.addDouble(z);
	}
	if (command=="plan_num")
        {
            list.addInt(num_steps);
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
	    x = list->get(1).asDouble();
	    y = list->get(2).asDouble();
	    z = list->get(3).asDouble();
	}
	if (command=="plan_num")
        {
            num_steps=list->get(1).asInt();
        }

	return;
    }
  
};

#endif // FS_PLANNER_MSG