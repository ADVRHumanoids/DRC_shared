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

/* 
 *  YARP Implementation of a flat_walk_plan message as a sequence of flat_walk_cmd
 *  with a few conversion utilities. 
 *
 *  email: v.varricchio@gmail.com 
 */

#ifndef YARPMSG_TYPE_flat_walk_plan
#define YARPMSG_TYPE_flat_walk_plan

#include <string.h>
#include <vector>
#include <drc_shared/yarp_msgs/YARP_Point.h>
#include <yarp/os/Portable.h>
#include <drc_shared/utils/Pose2D.h>

#include "flat_walk_cmd.h"

#define FLAT_WALK_PLAN_WORKING -1
#define FLAT_WALK_PLAN_SUCCESS 0
#define FLAT_WALK_PLAN_NOSOLUTION 1
#define FLAT_WALK_PLAN_GOALOBS 2
#define FLAT_WALK_PLAN_STOPPED 3

class flat_walk_plan : public yarp::os::Portable{
  
public:
  int status;
  
  int progress;
  std::vector<flat_walk_cmd> controls;
  YARP_Point init_pose;
  
  int iteration;
  double cost;

  flat_walk_plan();
  
  yarp::os::ConstString getTypeName() const;
 
  bool read(yarp::os::ConnectionReader&);

  bool write(yarp::os::ConnectionWriter& connection);

  // Utils
  
  void append_cmd(const flat_walk_cmd&, bool simplify=true);
  
  void append(const flat_walk_plan&, bool simplify=true);
  
  std::vector<YARP_Point> to_path();

  std::vector<Pose2D> to_traj();
 
  Pose2D next_pose(const Pose2D& ip, const flat_walk_cmd&);
  
  void from_rrts_unicycle_controls(const float* init_state, std::vector<float*> traj_controls, int seq_num_offset = 0);
    
  void clear();

  //void simplify();

};

#endif