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
 *  YARP Implementation of the ros message geometry_msgs/Pose
 *
 *  email: v.varricchio@gmail.com 
 */

#ifndef YARPMSG_TYPE_geometry_msgs_Pose
#define YARPMSG_TYPE_geometry_msgs_Pose

#include <string>
#include "YARP_Point.h"
#include "YARP_Quaternion.h"

class YARP_Pose : public yarp::os::Portable{
public:
  YARP_Point position;
  YARP_Quaternion orientation;
  
  yarp::os::ConstString getTypeName() const {
    return "YARP_Point";
  }

  YARP_Pose(){
  };
 
  bool read(yarp::os::ConnectionReader& connection) {
    if (!position.read(connection)) return false;
    if (!orientation.read(connection)) return false; 
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    if (!position.write(connection)) return false;
    if (!orientation.write(connection)) return false; 
    
    return !connection.isError();
  }

  
};

#endif
