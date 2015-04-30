#ifndef TOPIC_CHANGE_MSG
#define TOPIC_CHANGE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>

class topic_change_msg
{
public:
    topic_change_msg()
    {
	display="";
	topic="";
    };

    std::string display;
    std::string topic;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(display);
	list.addString(topic);

        return temp;
    }

    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            display="";
	    topic="";
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            display="";
	    topic="";
            return;
        }
        if (list->get(0).isNull())
        {
            display="";
	    topic="";
            return;
        }

        display = list->get(0).asString();
	topic = list->get(1).asString();

	return;
    }
  
};

#endif // TOPIC_CHANGE_MSG