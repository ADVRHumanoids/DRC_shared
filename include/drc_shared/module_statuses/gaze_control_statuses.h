#ifndef GAZE_CONTROL_STATUSES_H
#define GAZE_CONTROL_STATUSES_H

#include <map>
#include <vector>

namespace walkman
{
namespace drc
{
namespace gaze
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;

	states.push_back("running");

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

#endif //GAZE_CONTROL_STATUSES_H