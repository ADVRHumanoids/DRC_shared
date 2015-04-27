#ifndef DRC_DOOR_STATUSES_H
#define DRC_DOOR_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace door
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
	states.push_back("opening_door");
	states.push_back("opened_door");
	states.push_back("supporting hand");
	states.push_back("supported hand");
	states.push_back("ungrasping");
	states.push_back("ungrasped");
	states.push_back("leaving handle");
	states.push_back("left handle");
	states.push_back("safe_exiting");
	states.push_back("safe_exited");

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

#endif //DRC_DOOR_STATUSES_H