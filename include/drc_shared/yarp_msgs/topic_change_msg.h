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