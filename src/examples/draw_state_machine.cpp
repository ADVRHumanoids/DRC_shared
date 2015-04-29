#include <yarp/os/all.h>
#include <stdio.h>
#include <sstream>
#include <drc_shared/draw_state_machine.hpp>
#include <yarp/sig/all.h>
#include <yarp/os/all.h>

#define WALKMAN_DRC_VALVE_COMMAND_NONE ""
#define WALKMAN_DRC_VALVE_COMMAND_REACH "reach"
#define WALKMAN_DRC_VALVE_COMMAND_APPROACH "approach"
#define WALKMAN_DRC_VALVE_COMMAND_GRASP "grasp"
#define WALKMAN_DRC_VALVE_COMMAND_TURN "turn"
#define WALKMAN_DRC_VALVE_COMMAND_UNGRASP "ungrasp"
#define WALKMAN_DRC_VALVE_COMMAND_MOVE_AWAY "move_away"
#define WALKMAN_DRC_VALVE_COMMAND_HOMING "home"
#define WALKMAN_DRC_VALVE_COMMAND_VALVE_DATA_SENT "valvedatasent"
#define WALKMAN_DRC_VALVE_COMMAND_VALVE_DONE "valvedone"
#define WALKMAN_DRC_VALVE_COMMAND_ACTION_DONE "action_done"
#define WALKMAN_DRC_VALVE_COMMAND_HAND_DONE "hand_done"

#define WALKMAN_DRC_VALVE_COMMAND_LEFT "left_hand"
#define WALKMAN_DRC_VALVE_COMMAND_RIGHT "right_hand"
#define WALKMAN_DRC_VALVE_COMMAND_BOTH "both_hands"
#define WALKMAN_DRC_VALVE_COMMAND_CLOSING_HANDS "hands_close"
#define WALKMAN_DRC_VALVE_COMMAND_OPENING_HANDS "hands_open"

#define WALKMAN_DRC_VALVE_STATUS_WAITING "waiting"
#define WALKMAN_DRC_VALVE_STATUS_READY "ready"
#define WALKMAN_DRC_VALVE_STATUS_REACHING "reaching"
#define WALKMAN_DRC_VALVE_STATUS_REACHED "reached"
#define WALKMAN_DRC_VALVE_STATUS_GRASPING "grasping"
#define WALKMAN_DRC_VALVE_STATUS_GRASPED "grasped"
#define WALKMAN_DRC_VALVE_STATUS_APPROACHING "approaching"
#define WALKMAN_DRC_VALVE_STATUS_APPROACHED "approached"
#define WALKMAN_DRC_VALVE_STATUS_TURNING "turning"
#define WALKMAN_DRC_VALVE_STATUS_TURNED "turned"
#define WALKMAN_DRC_VALVE_STATUS_UNGRASPING "ungrasping"
#define WALKMAN_DRC_VALVE_STATUS_UNGRASPED "ungrasped"
#define WALKMAN_DRC_VALVE_STATUS_MOVING_AWAY "moving_away"
#define WALKMAN_DRC_VALVE_STATUS_MOVED_AWAY "moved_away"



#define RAD2DEG    (180.0/M_PI)
#define DEG2RAD    (M_PI/180.0)

enum class state {
    idle,
    ready,
    reaching,
    reached,
    approaching,
    approached,
    grasping,
    grasped,
    valve_rotating,
    valve_rotated,
    ungrasping,
    ungrasped,
    moving_away,
    moved_away,
    moving_home,
    moved_home,
    stopped
};

std::map<state,std::string> state_map;

int main(int argc, char *argv[]) {
    state_map[state::idle] = "idle";
    state_map[state::ready] = "ready";
    state_map[state::reaching] = "reaching";
    state_map[state::reached] = "reached";
    state_map[state::approaching] = "approaching";
    state_map[state::approached] = "approached";
    state_map[state::grasping] = "grasping";
    state_map[state::grasped] = "grasped";
    state_map[state::valve_rotating] = "valve_rotating";
    state_map[state::valve_rotated] = "valve_rotated";
    state_map[state::ungrasping] = "ungrasping";
    state_map[state::ungrasped] = "ungrasped";
    state_map[state::moving_away] = "moving_away";
    state_map[state::moved_away] = "moved_away";
    state_map[state::moving_home] = "moving_home";
    state_map[state::moved_home] = "moved_home";
    
    std::vector<std::tuple<state,std::string,state>> transition_table{
        //--------------initial state ----------+--------- command ---------------------------+------ final state--------- +
        std::make_tuple( state::idle            ,   WALKMAN_DRC_VALVE_COMMAND_VALVE_DATA_SENT ,    state::ready            ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::ready           ,   WALKMAN_DRC_VALVE_COMMAND_REACH           ,    state::reaching         ),
        std::make_tuple( state::ready           ,   WALKMAN_DRC_VALVE_COMMAND_VALVE_DONE      ,    state::idle             ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::reaching        ,   WALKMAN_DRC_VALVE_COMMAND_ACTION_DONE     ,    state::reached          ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::reached         ,   WALKMAN_DRC_VALVE_COMMAND_APPROACH        ,    state::approaching      ),
        std::make_tuple( state::reached         ,   WALKMAN_DRC_VALVE_COMMAND_MOVE_AWAY       ,    state::moving_away      ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::approaching     ,   WALKMAN_DRC_VALVE_COMMAND_ACTION_DONE     ,    state::approached       ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::approached      ,   WALKMAN_DRC_VALVE_COMMAND_REACH           ,    state::reaching         ),
        std::make_tuple( state::approached      ,   WALKMAN_DRC_VALVE_COMMAND_MOVE_AWAY       ,    state::moving_away      ),
        std::make_tuple( state::approached      ,   WALKMAN_DRC_VALVE_COMMAND_GRASP           ,    state::grasping         ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::grasping        ,   WALKMAN_DRC_VALVE_COMMAND_HAND_DONE       ,    state::grasped          ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::grasped         ,   WALKMAN_DRC_VALVE_COMMAND_TURN            ,    state::valve_rotating   ),
        std::make_tuple( state::grasped         ,   WALKMAN_DRC_VALVE_COMMAND_UNGRASP         ,    state::ungrasping       ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::valve_rotating  ,   WALKMAN_DRC_VALVE_COMMAND_ACTION_DONE     ,    state::valve_rotated    ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::valve_rotated   ,   WALKMAN_DRC_VALVE_COMMAND_UNGRASP         ,    state::ungrasping       ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::ungrasping      ,   WALKMAN_DRC_VALVE_COMMAND_HAND_DONE       ,    state::ungrasped        ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::ungrasped       ,   WALKMAN_DRC_VALVE_COMMAND_GRASP           ,    state::grasping         ),
        std::make_tuple( state::ungrasped       ,   WALKMAN_DRC_VALVE_COMMAND_REACH           ,    state::reaching         ),
        std::make_tuple( state::ungrasped       ,   WALKMAN_DRC_VALVE_COMMAND_MOVE_AWAY       ,    state::moving_away      ),
        std::make_tuple( state::ungrasped       ,   WALKMAN_DRC_VALVE_COMMAND_VALVE_DONE      ,    state::idle             ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::moving_away     ,   WALKMAN_DRC_VALVE_COMMAND_ACTION_DONE     ,    state::moved_away       ),
        //--------------------------------------+---------------------------------------------+----------------------------+
        std::make_tuple( state::moved_away      ,   WALKMAN_DRC_VALVE_COMMAND_REACH           ,    state::reaching         ),
        std::make_tuple( state::moved_away      ,   WALKMAN_DRC_VALVE_COMMAND_VALVE_DONE      ,    state::idle             ),
    };
    walkman::drc::draw_state_machine<state,std::string> drawer;
    drawer.insert(transition_table);
    drawer.draw_on_file("asd",state_map);
    return 0;
}
