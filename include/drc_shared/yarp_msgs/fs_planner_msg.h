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
	
        return temp;
    }
    void fromBottle(yarp::os::Bottle& temp)
    {
        command = temp.get(0).asString();
	
	if(command=="direction")
	{
	    yarp::os::Bottle* list=temp.get(0).asList();
	    x = list->get(0).asDouble();
	    y = list->get(1).asDouble();
	    z = list->get(2).asDouble();
	}
	return;
    }
  
};

#endif // FS_PLANNER_MSG