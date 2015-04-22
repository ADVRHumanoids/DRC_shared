#ifndef ALL_DEFINITION_H
#define ALL_DEFINITION_H

#include "drc_shared/module_statuses/drc_poses_statuses.h"
#include "drc_shared/module_statuses/drc_door_statuses.h"
#include "drc_shared/module_statuses/drc_wall_statuses.h"

namespace walkman
{
namespace drc
{
class states_maps
{
public:
    states_maps()
    {
        poses::status_definitions poses_states;
	module_code_to_status["drc_poses"] = poses_states.code_to_status;
	module_status_to_code["drc_poses"] = poses_states.status_to_code;

	door::status_definitions door_states;
	module_code_to_status["drc_door"] = door_states.code_to_status;
	module_status_to_code["drc_door"] = door_states.status_to_code;

	wall::status_definitions wall_states;
	module_code_to_status["drc_wall"] = wall_states.code_to_status;
	module_status_to_code["drc_wall"] = wall_states.status_to_code;
    }
    
    std::map<std::string, std::map<std::string,std::string>> module_code_to_status;
    std::map<std::string, std::map<std::string,std::string>> module_status_to_code;
};
}
}

#endif //ALL_DEFINITION_H