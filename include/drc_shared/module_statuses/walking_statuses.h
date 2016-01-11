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

#ifndef DRC_WALKING_STATUSES_H
#define DRC_WALKING_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace walking
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;

	states.push_back("starting");
	states.push_back("initialized");
	states.push_back("robotPowerUp");
	states.push_back("robotPowerUp");
	states.push_back("homing");
	states.push_back("homingDone");
	states.push_back("walk");
	states.push_back("walkDone");
	states.push_back("emergencyStop");
	states.push_back("goingToValvePos");
	states.push_back("takeOverControl");
	states.push_back("taskSpaceHoming");
	states.push_back("pause");

	char code='a';
	for(auto state:states)
	{
	    status_to_code[state]=std::string(1,code);
	    code_to_status[std::string(1,code)]=state;
	    code = (char)(code+1);
	}
    }
    std::map<std::string,std::string> status_to_code;
    std::map<std::string,std::string> code_to_status;
};
}
}
}

#endif //DRC_WALKING_STATUSES_H