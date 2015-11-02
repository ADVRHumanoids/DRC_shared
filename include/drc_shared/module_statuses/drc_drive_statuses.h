/* Copyright [2014,2015] [Mirko Ferrati, Alessandro Settimi, Valerio Varricchio, Enrico Corvaglia]
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

#ifndef DRC_DRIVE_STATUSES_H
#define DRC_DRIVE_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace drive
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;
		
	states.push_back("idle");//"idle";
	states.push_back("ready");//"ready";
	states.push_back("reaching");//"reaching";
	states.push_back("reached");//"reached";
	states.push_back("approaching");//"approaching";
	states.push_back("approached");//"approached";
	states.push_back("rotating_foot");//"rotating_foot";
	states.push_back("rotated_foot");//"rotated_foot";
	states.push_back("drive");//"drive";
	states.push_back("turning_left");//"turning_left";
	states.push_back("turning_right");//"turning_right";
	states.push_back("accelerating");//"accelerating";
	states.push_back("moving_away_hand");//"moving_away_hand";
	states.push_back("moved_away_hand");//"moved_away_hand";
	states.push_back("grasping");//"grasping";
	states.push_back("grasped");//"grasped";
	states.push_back("ungrasping");//"ungrasping";
	states.push_back("ungrasped");//"ungrasped";
	states.push_back("moving_away_foot");//"moving_away_foot";
	states.push_back("moved_away_foot");//"moved_away_foot";

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

#endif //DRC_DRIVE_STATUSES_H