/*  
 *  Copyright: (C) 2016 Walkman
 *  Authors: Luca Muratore, Dimitrios Kanoulas
 *  email: luca.muratore@iit.it, dimitrios.kanoulas@iit.it
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

#ifndef VALVE_PLANNER_MSG
#define VALVE_PLANNER_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include <vector>

class valve_planner_msg
{
public:  
    
    std::string command;
    std::string module_prefix;
    
    valve_planner_msg()
    {
        command="";
        module_prefix="";

    }


    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle my_bottle;
        yarp::os::Bottle& list= my_bottle.addList();

	list.addString(command);

	if(command=="start_module")
	{
	    list.addString(module_prefix);
	}

        return my_bottle;
    }

    bool fromBottle(const yarp::os::Bottle* temp)
    {
        // checks
        if (temp->get(0).isNull())
        {
            command="";
            return false;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            command="";
            return false;
        }
        if (list->get(0).isNull())
        {
            command="";
            return false;
        }
        
        // get the command
        command = list->get(0).asString();
        // swtich the commands
        if(command=="start_module")
        {
            module_prefix = list->get(1).asString();
            return true;
        }
    }
  
};

#endif // VALVE_PLANNER_MSG
