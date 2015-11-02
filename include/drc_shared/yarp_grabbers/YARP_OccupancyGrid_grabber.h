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
 *  Grabber for a YARP_OccupancyGrid_msg that outputs an OccupancyGrid object.
 *
 *  email: v.varricchio@gmail.com 
 */

#include <drc_shared/utils/OccupancyGrid.h>
#include "YARP_grabber.hpp"

class YARP_OccupancyGrid_grabber : public yarp_msg_grabber<YARP_OccupancyGrid_msg, OccupancyGrid>  {
         
public: 
  void update_data(YARP_OccupancyGrid_msg& msg){
    //std::cout << "YARP_OccupancyGrid_grabber.h: msg frame_id: '" << msg.header.frame_id << "' " << std::endl;
    this->data = OccupancyGrid(msg);
    //std::cout << "YARP_OccupancyGrid_grabber.h: this->data frame_id: '" << this->data.header.frame_id << "' " << std::endl;
  }
};