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

#ifndef ODOMETRY_MSG
#define ODOMETRY_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class odometry_msg
{
public:
    odometry_msg()
    {
        odometry_data.p.x(0.0);
        odometry_data.p.y(0.0);
        odometry_data.p.z(0.0);
        odometry_data.M = KDL::Rotation::Identity();
    }

    KDL::Frame odometry_data;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();
        list.add(yarp_KDL::getBlob(odometry_data));
        return temp;
    }
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            return;
        }
        if (list->get(0).isNull())
        {
            return;
        }
        int index=0;
        if(list->get(index).asBlobLength()!=0)
        {
            odometry_data = yarp_KDL::fromBlob(list->get(index++));
        }
        else
        {  
            odometry_data.p.x(list->get(index++).asDouble());
            odometry_data.p.y(list->get(index++).asDouble());
            odometry_data.p.z(list->get(index++).asDouble());
            double qx,qy,qz,qw;
            qx = list->get(index++).asDouble();
            qy = list->get(index++).asDouble();
            qz = list->get(index++).asDouble();
            qw = list->get(index++).asDouble();
            odometry_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
        }
        return;
    }
    
};

#endif // ODOMETRY_MSG