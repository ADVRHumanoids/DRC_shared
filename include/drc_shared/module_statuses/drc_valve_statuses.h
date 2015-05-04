#ifndef DRC_VALVE_STATUSES_H
#define DRC_VALVE_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace valve
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;

	states.push_back("idle");
	states.push_back("ready");
	states.push_back("reaching");
	states.push_back("reached");
	states.push_back("approaching");
	states.push_back("approached");
	states.push_back("grasping");
	states.push_back("grasped");
	states.push_back("valve_rotating");
	states.push_back("valve_rotated");
	states.push_back("ungrasping");
	states.push_back("ungrasped");
	states.push_back("moving_away");
	states.push_back("moved_away");
	states.push_back("moving_home");
	states.push_back("moved_home");
	states.push_back("going_back");
	states.push_back("went_back");

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

#endif //DRC_VALVE_STATUSES_H