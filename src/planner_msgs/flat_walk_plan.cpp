/* 
 *  YARP Implementation of a flat_walk_plan message as a sequence of flat_walk_cmd
 *  with a few conversion utilities. 
 *
 *  email: v.varricchio@gmail.com 
 */

#include <drc_shared/planner_msgs/flat_walk_plan.h>
#include <drc_shared/yarp_msgs/YARP_Pose.h>

#include <tuple>

flat_walk_plan::flat_walk_plan(){
};

yarp::os::ConstString flat_walk_plan::getTypeName() const {
  return "flat_walk_plan";
}

bool flat_walk_plan::read(yarp::os::ConnectionReader& connection) {
  controls.clear();
  status = connection.expectInt();
  progress = connection.expectInt(); 
  int len = connection.expectInt();
  
  for (uint i=0; i<len; i++){
    flat_walk_cmd p; 
    p.read(connection);
    controls.push_back(p);
  }
  
  init_pose.read(connection);
  
  iteration = connection.expectInt();
  cost = connection.expectDouble();
  
  return !connection.isError();
}

bool flat_walk_plan::write(yarp::os::ConnectionWriter& connection) {
  connection.appendInt(status);
  connection.appendInt(progress);
  connection.appendInt(controls.size());
  
  for(flat_walk_cmd cmd: controls){
    cmd.write(connection);
  }
  
  init_pose.write(connection);
  
  connection.appendInt(iteration);
  connection.appendDouble(cost);
  
  return !connection.isError();
}

std::vector<YARP_Point> flat_walk_plan::to_path(){
  std::vector<YARP_Point> res;
  res.push_back(init_pose);
  YARP_Point p;
  Pose2D next;
  Pose2D cur(init_pose.x, init_pose.y, init_pose.z);
  for(flat_walk_cmd cmd: controls){
    next = next_pose(cur, cmd);
    p.x = next.x;
    p.y = next.y;
    if(strcmp(cmd.action.c_str(), FLAT_WALK_ROT_L)!=0 && strcmp(cmd.action.c_str(), FLAT_WALK_ROT_R)!=0){
      res.push_back(p);
    }
    cur = next;
  }
  return res;
}

std::vector<Pose2D> flat_walk_plan::to_traj(){
  std::vector<Pose2D> res;
  res.push_back(Pose2D(init_pose.x, init_pose.y, init_pose.z));

  for(flat_walk_cmd cmd: controls){
    int num;
    flat_walk_cmd elem_cmd;
    std::tie(elem_cmd, num) = flat_walk_cmd::split(cmd);
    auto inp = res.back();
    for(size_t n=0; n<num; n++){
      res.push_back(next_pose(res.back(), elem_cmd));
    } 
    res.push_back(next_pose(inp, cmd)); // force exact final position
  }
  return res;
}


Pose2D flat_walk_plan::next_pose(const Pose2D& ip, const flat_walk_cmd& cmd){
  cmd_struct cmd_transl= cmd.to_struct();
  
  /*std::cout << "Called next pose from " << ip.x << " " << ip.y << " " << ip.yaw << std::endl; 
  std::cout << "with command " << cmd.action << " " << cmd.amount << std::endl; */

  Pose2D res;
  res.x = ip.x + cmd_transl.walk_meters*cos(ip.yaw) - cmd_transl.side_meters*sin(ip.yaw);
  res.y = ip.y + cmd_transl.walk_meters*sin(ip.yaw) + cmd_transl.side_meters*cos(ip.yaw);
  res.yaw = ip.yaw + cmd_transl.turn_deg*M_PI/180;
  
  return res;
}

void flat_walk_plan::append_cmd(const flat_walk_cmd& cmd, bool simplify){
  if(controls.size()==0){
    controls.push_back(cmd);
  }else{
    if(!simplify){
      controls.push_back(cmd);
      
    }else if(!controls.back().add(cmd)){
      controls.push_back(cmd);
    }
  }
}

void flat_walk_plan::append(const flat_walk_plan& pl, bool simplify){
  this->append_cmd(pl.controls[0], simplify);
  for(size_t i=1; i<pl.controls.size(); i++)
    controls.push_back(pl.controls[i]);
}

void flat_walk_plan::from_rrts_unicycle_controls(const float* init_state, std::vector<float*> traj_controls, int seq_num_offset){
  // this function could be rewritten by using append_cmd()!
  
  init_pose = YARP_Point(init_state[0], init_state[1], init_state[2]);

  controls.clear();
  flat_walk_cmd cmd;
  double turn2 = 0;
  int i=0;
  
  for(auto c:traj_controls){
    // To be compliant with interfaces, a
    // conversion to degrees here is needed
    c[1] = c[1]*180/M_PI; 
    c[3] = c[3]*180/M_PI;

    cmd.seq_num = i;
    i++;
    cmd.amount = c[1]+turn2;
    cmd.action = FLAT_WALK_ROT_L; 
    cmd.normalize();
    // Little HACK to correct meaningless rotations if present
    if(cmd.amount>180 && c[0]==1){
      cmd.amount-=180; 
      c[2] = -c[2];
      c[3] += 180;
      while(c[3]>360) c[3]-= 360;
      while(c[3]<0) c[3]+=360;
    }
    controls.push_back(cmd);
    cmd.seq_num = i;
    i++;
    cmd.amount = c[2];
    cmd.action = (c[0]==0) ? FLAT_WALK_FWD : FLAT_WALK_SIDE_L;
    cmd.normalize();
    controls.push_back(cmd);
    turn2 = c[3];
  }
  cmd.seq_num = i;
  cmd.amount = turn2;
  cmd.action = FLAT_WALK_ROT_L;
  cmd.normalize();
  controls.push_back(cmd);
}

void flat_walk_plan::clear(){
  controls.clear();
  status = 0;
  cost = 0;
  progress = 0;
  iteration = 0;
}

/*void flat_walk_plan::simplify(int offset=0){
  std::vector<flat_walk_cmd> new_controls;
  flat_walk_cmd tmp;
  new_control.push_back(tmp);
  for(auto cmd: controls){
    if(!new_controls.back().add(cmd))
      new_controls.push_back(cmd);
  }
  controls = new_controls;
}*/