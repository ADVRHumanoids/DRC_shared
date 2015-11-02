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

#include <drc_shared/utils/Pose2D.h>
#include "YARP_grabber.hpp"

class YARP_Pose2D_grabber: public yarp_msg_grabber<yarp::os::Bottle, Pose2D>  {
public: 
  void update_data(yarp::os::Bottle& b){
    this->data.x = b.get(0).asDouble();
    this->data.y = b.get(1).asDouble();
    this->data.yaw = b.get(2).asDouble();
  }
};