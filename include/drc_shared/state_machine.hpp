/* Copyright [2014,2015] [Mirko Ferrati, Alessandro Settimi, Valerio Varricchio]
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.*/

#ifndef BASIC_STATE_MACHINE_HPP
#define BASIC_STATE_MACHINE_HPP

#include <map>
#include <vector>

namespace walkman{
    namespace drc{

/** 
 * @brief STATE MACHINE EXAMPLE
 *
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
};*/
    
template <class state_type>
class state_machine
{
public:
    std::map<state_type,std::map<std::string,state_type>> transition_table;
    state_type evolve_state_machine(state_type current_state, std::string command)
    {
        if (transition_table.count(current_state))
        {
            if (transition_table.at(current_state).count(command))
                return transition_table.at(current_state).at(command);
        }
        return current_state;
    }
    
    void insert(std::vector< std::tuple< state_type, std::string, state_type > > table)
    {
        for (auto row:table)
            insert(row);
    }
    
    void insert(std::tuple< state_type, std::string, state_type > row)
    {
        transition_table[std::get<0>(row)][std::get<1>(row)]=std::get<2>(row);
    }
    
    state_machine()
    {
    }
};

}
}
#endif // BASIC_STATE_MACHINE_HPP
