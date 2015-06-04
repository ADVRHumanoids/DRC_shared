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