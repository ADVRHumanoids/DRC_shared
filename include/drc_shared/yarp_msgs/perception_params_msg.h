#ifndef PERCEPTION_PARAMS_MSG
#define PERCEPTION_PARAMS_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>

class perception_params_msg
{
  public:
    perception_params_msg()
    {
      command = "";
      param = 0.0;
    }

    std::string command;

    double param;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

        list.addString(command);
        list.addDouble (param);

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

      int index=1;
      param = list->get(index++).asDouble();

      return;
    }
};

#endif // PERCEPTION_PARAMS_MSG