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

	states.push_back("idle");
	states.push_back("ready");
	states.push_back("data_received");
	states.push_back("aligning_hand");
	states.push_back("turning_left");
	states.push_back("turning_right");
	states.push_back("accelerating");

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