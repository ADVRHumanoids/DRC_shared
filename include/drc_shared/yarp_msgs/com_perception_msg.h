#ifndef COM_PERCEPTION_MSG
#define COM_PERCEPTION_MSG

#include <string>
#include <vector>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <boost/concept_check.hpp>
#include <kdl/frames.hpp>

class com_perception_msg
{
  public:
    com_perception_msg ()
    {
    }

  std::string command;

  yarp::os::Bottle toBottle ()
  {
    yarp::os::Bottle temp;
    yarp::os::Bottle& list= temp.addList();
    list.addString(command);

    return temp;
  }

  void fromBottle (yarp::os::Bottle* temp)
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

#endif