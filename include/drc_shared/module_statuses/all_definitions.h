#ifndef ALL_DEFINITION_H
#define ALL_DEFINITION_H

#include "drc_shared/module_statuses/drc_poses_statuses.h"
#include "drc_shared/module_statuses/drc_door_statuses.h"
#include "drc_shared/module_statuses/drc_wall_statuses.h"
#include "drc_shared/module_statuses/walking_statuses.h"
#include "drc_shared/module_statuses/drc_drive_statuses.h"
#include "drc_shared/module_statuses/gaze_control_statuses.h"
#include "drc_shared/module_statuses/drc_valve_statuses.h"
#include "drc_shared/module_statuses/drc_debris_statuses.h"
#include "drc_shared/module_statuses/simple_homing_statuses.h"
#include "drc_shared/module_statuses/drc_plug_statuses.h"

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

	walking::status_definitions walk_states;
	module_code_to_status["walking"] = walk_states.code_to_status;
	module_status_to_code["walking"] = walk_states.status_to_code;

	drive::status_definitions drive_states;
	module_code_to_status["drc_drive"] = drive_states.code_to_status;
	module_status_to_code["drc_drive"] = drive_states.status_to_code;

	gaze::status_definitions gaze_states;
	module_code_to_status["gaze_control"] = gaze_states.code_to_status;
	module_status_to_code["gaze_control"] = gaze_states.status_to_code;

	valve::status_definitions valve_states;
	module_code_to_status["drc_valve"] = valve_states.code_to_status;
	module_status_to_code["drc_valve"] = valve_states.status_to_code;

	debris::status_definitions debris_states;
	module_code_to_status["drc_debris"] = debris_states.code_to_status;
	module_status_to_code["drc_debris"] = debris_states.status_to_code;

	homing::status_definitions homing_states;
	module_code_to_status["simple_homing"] = homing_states.code_to_status;
	module_status_to_code["simple_homing"] = homing_states.status_to_code; 
	
	plug::status_definitions plug_states;
	module_code_to_status["drc_plug"] = plug_states.code_to_status;
	module_status_to_code["drc_plug"] = plug_states.status_to_code; 
	
    }
    
    std::map<std::string, std::map<std::string,std::string>> module_code_to_status;
    std::map<std::string, std::map<std::string,std::string>> module_status_to_code;
};
}
}

#endif //ALL_DEFINITION_H