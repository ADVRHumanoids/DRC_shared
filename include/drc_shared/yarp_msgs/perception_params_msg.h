/* Copyright [2014,2015] [Mirko Ferrati, Alessandro Settimi, Valerio Varricchio]
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.*/

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