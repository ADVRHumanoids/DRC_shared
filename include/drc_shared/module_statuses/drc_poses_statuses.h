#ifndef DRC_POSES_STATUSES_H
#define DRC_POSES_STATUSES_H

#include <map>
#include <vector>

#define HOMING_STATUS "homing"
#define STAND_STATUS "stand"
#define HOMING_GUARD_STATUS "homing_guard"

namespace walkman
{
namespace drc
{
namespace poses
{
class status_definitions
{
public:
    status_definitions()
    {
        std::vector<std::string> states;
	
	states.push_back("ready");
	states.push_back("homing");
	states.push_back("stand");
	states.push_back("homing_guard");
	states.push_back("homing_guard_left");
	states.push_back("homing_guard_right");
	states.push_back("lower");
	states.push_back("squat");
	states.push_back("debris");
	states.push_back("driving");
	states.push_back("car_exit");
	states.push_back("car_exit_mod");
	states.push_back("demo0");
	states.push_back("demo1");
	states.push_back("demo2");
	states.push_back("demo3");
	states.push_back("demo4");
	states.push_back("demo5");
	states.push_back("demo6");
	states.push_back("demo7");
	states.push_back("demo8");
	states.push_back("demo9");
	states.push_back("demo10");
	states.push_back("demo11");
	states.push_back("demo12");
	states.push_back("demo13");
	states.push_back("demo14");
	states.push_back("demo15");
	states.push_back("demo16");
	states.push_back("demo17");
	
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

#endif //DRC_POSES_STATUSES_H