#ifndef GAZE_CONTROL_MSG
#define GAZE_CONTROL_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>


class gaze_control_msg
{
public:
    std::string command;
    double amount;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	list.addDouble(amount);

        return temp;
    }

    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            command="";
	    amount=0.0;
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            command="";
	    amount=0.0;
            return;
        }
        if (list->get(0).isNull())
        {
            command="";
	    amount=0.0;
            return;
        }

        command = list->get(0).asString();
	amount = list->get(1).asDouble();

	return;
    }
  
};

#endif // GAZE_CONTROL_MSG