#ifndef DRC_PLUG_STATUSES_H
#define DRC_PLUG_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace plug
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;
    
	states.push_back("idle");
	states.push_back("ready_stick");
	states.push_back("ready_hand");
	states.push_back("reaching");
	states.push_back("reached");
	states.push_back("approaching");
	states.push_back("approached");
	states.push_back("rotating");
	states.push_back("rotated");
	states.push_back("moving_away");
	states.push_back("moved_away");
	states.push_back("moving_back");
	states.push_back("moved_back");
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

#endif //DRC_PLUG_STATUSES_H