/* 
 *  YARP Implementation of a flat_walk_command message 
 *  acoording to the agreed interfaces. 
 *
 *  email: v.varricchio@gmail.com 
 */

#include <drc_shared/planner_msgs/flat_walk_cmd.h>
#include <assert.h>
#include <math.h>
#include <string.h>

std::map<std::string,std::string> flat_walk_cmd::opposite = {
  {FLAT_WALK_FWD, FLAT_WALK_BWD},
  {FLAT_WALK_BWD, FLAT_WALK_FWD},
  {FLAT_WALK_ROT_L, FLAT_WALK_ROT_R},
  {FLAT_WALK_SIDE_L, FLAT_WALK_SIDE_R}
};

std::map<std::string,double> flat_walk_cmd::el = {
  {FLAT_WALK_FWD, 0.05},
  {FLAT_WALK_BWD, 0.05},
  {FLAT_WALK_ROT_L, 3},
  {FLAT_WALK_ROT_R, 3}
};

yarp::os::ConstString flat_walk_cmd::getTypeName() const {
  return "flat_walk_cmd";
}


flat_walk_cmd::flat_walk_cmd(){}

bool flat_walk_cmd::read(yarp::os::ConnectionReader& connection) {
  action = connection.expectText();
  amount = connection.expectDouble();
  seq_num = connection.expectInt();
  
  return !connection.isError();
}

bool flat_walk_cmd::write(yarp::os::ConnectionWriter& connection) {
  connection.appendString(action.c_str());
  connection.appendDouble(amount);
  connection.appendInt(seq_num);
  
  return !connection.isError();
}

bool flat_walk_cmd::add(const flat_walk_cmd& cmd){
  // Returns false if commands cannot be added
  cmd_struct cmds0 = this->to_struct();
  cmd_struct cmds1 = cmd.to_struct();
  cmd_struct res;
  res.seq_num = seq_num;
  res.turn_deg = cmds0.turn_deg +cmds1.turn_deg;
  res.walk_meters = cmds0.walk_meters+cmds1.walk_meters;
  
  return from_struct(res);
}

void flat_walk_cmd::normalize(){
  
  if(amount<0){
    amount = -amount;
    action = opposite[action];
  }
}

cmd_struct flat_walk_cmd::to_struct() const{
  cmd_struct cmd_transl;
  cmd_transl.seq_num = seq_num;
  if(strcmp(action.c_str(), FLAT_WALK_FWD)==0){
    cmd_transl.walk_meters = amount;
    cmd_transl.turn_deg = 0;
  }else if(strcmp(action.c_str(), FLAT_WALK_BWD)==0){
    cmd_transl.walk_meters = -amount;
    cmd_transl.turn_deg = 0;
  }else if(strcmp(action.c_str(), FLAT_WALK_ROT_L)==0){
    cmd_transl.walk_meters = 0;
    cmd_transl.turn_deg = amount;
  }else if(strcmp(action.c_str(), FLAT_WALK_ROT_R)==0){
    cmd_transl.walk_meters = 0;
    cmd_transl.turn_deg = -amount;	
  }else{
    std::cout << "Action '" << action << "' is either not valid or not implemented." << std::endl;
    assert(false);
  }
  return cmd_transl;
}

bool flat_walk_cmd::from_struct(const cmd_struct& cmds){
  seq_num = cmds.seq_num;
  if(cmds.walk_meters*cmds.turn_deg != 0)
    return false;
  if(cmds.walk_meters!=0){
    amount = fabs(cmds.walk_meters);
    action = (cmds.walk_meters>0) ? FLAT_WALK_FWD : FLAT_WALK_BWD;
  }else if(cmds.turn_deg!=0){
    amount = fabs(cmds.turn_deg);
    action = (cmds.walk_meters>0) ? FLAT_WALK_ROT_L : FLAT_WALK_ROT_R;
  }
}  

std::pair<flat_walk_cmd, size_t> flat_walk_cmd::split(const flat_walk_cmd& cmd){
  flat_walk_cmd cmd_el;
  cmd_el.action = cmd.action;
  size_t num = cmd.amount/el[cmd.action];
  cmd_el.amount = cmd.amount/num; 
  return std::make_pair(cmd_el, num);
}
