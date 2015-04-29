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