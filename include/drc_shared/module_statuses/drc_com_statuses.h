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

#ifndef DRC_COM_STATUSES_H
#define DRC_COM_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace com
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;

	states.push_back("idle");
	states.push_back("ready");
	states.push_back("prereaching");
	states.push_back("prereached");
	states.push_back("reaching");
	states.push_back("reached");
	states.push_back("approaching");
	states.push_back("approached");
	states.push_back("grasping");
	states.push_back("grasped");
	states.push_back("turning");
	states.push_back("turned");
	states.push_back("opening com");
	states.push_back("opened com");
	states.push_back("supporting hand");
	states.push_back("supported hand");
	states.push_back("ungrasping");
	states.push_back("ungrasped");
	states.push_back("leaving handle");
	states.push_back("left handle");
        states.push_back("more opening");
        states.push_back("more opened");
        states.push_back("homing");
        states.push_back("homed");
	states.push_back("safe exiting");
	states.push_back("safe exited");

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

#endif //DRC_COM_STATUSES_H
