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
 *  Grabber for YARP_PointCloud2 messages with generic pcl::PointCloud<T> output. 
 *
 *  email: v.varricchio@gmail.com 
 */

#include <drc_shared/yarp_msgs/YARP_PointCloud2.h>
#include "YARP_grabber.hpp"

template <class PCL_PointCloud_t>
class YARP_PointCloud2_grabber : public yarp_msg_grabber<YARP_PointCloud2, PCL_PointCloud_t>  {
         
public: 
  void update_data(YARP_PointCloud2& msg){
    pcl::fromPCLPointCloud2(msg.getPointCloud2(), this->data);
  }
};