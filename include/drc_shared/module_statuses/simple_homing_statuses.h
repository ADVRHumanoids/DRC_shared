#ifndef SIMPLE_HOMING_STATUSES_H
#define SIMPLE_HOMING_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace homing
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;

	states.push_back("ready");
	states.push_back("moving");
	states.push_back("home");

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

#endif //SIMPLE_HOMING_STATUSES_H