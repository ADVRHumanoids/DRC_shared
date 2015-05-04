#ifndef DRC_DEBRIS_STATUSES_H
#define DRC_DEBRIS_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace debris
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
	states.push_back("grasping");
	states.push_back("grasped");
	states.push_back("approaching");
	states.push_back("approached");
	states.push_back("lifting");
	states.push_back("lifted");
	states.push_back("pushing");
	states.push_back("pushed");
	states.push_back("pulling");
	states.push_back("pulled");
	states.push_back("ungrasping");
	states.push_back("ungrasped");
	states.push_back("ready_remove");
	states.push_back("removing");
	states.push_back("removed");
	states.push_back("homing");
	states.push_back("homed");
	states.push_back("squatting");
	states.push_back("squatted");
	states.push_back("standing");
	states.push_back("standed");

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

#endif //DRC_DEBRIS_STATUSES_H