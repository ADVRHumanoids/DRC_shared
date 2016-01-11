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

#ifndef DEBRIS_MSG
#define DEBRIS_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Value.h>
#include <kdl/frames.hpp>
#include <vector>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class debris_msg
{
public:
    debris_msg()
    {
	command="";
	frame="";
	debris_data = KDL::Frame::Identity();
	left_hand = KDL::Frame::Identity();
	right_hand = KDL::Frame::Identity();
	length = 0.0;
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame debris_data;
    
    KDL::Frame left_hand;
    
    KDL::Frame right_hand;
    
    double length;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="debris_data")
	{
	    list.addString(frame);
	    list.add(yarp_KDL::getBlob(debris_data));
	    list.addDouble(length);
	}
	
	if(command=="hands_data")
	{
	    list.addString(frame);
	    list.add(yarp_KDL::getBlob(left_hand));
	    list.add(yarp_KDL::getBlob(right_hand));
	}

        return temp;
    }

    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            command="";
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            command="";
            return;
        }
        if (list->get(0).isNull())
        {
            command="";
            return;
        }

        command = list->get(0).asString();
	int index=1;
	if(command=="debris_data")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		debris_data = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		debris_data.p.x(list->get(index++).asDouble());
		debris_data.p.y(list->get(index++).asDouble());
		debris_data.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		debris_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	    length = list->get(index++).asDouble();
	}
	
	if(command=="hands_data")
	{
	    frame = list->get(index++).asString();
	    if(list->get(index).asBlobLength()!=0)
	    {
		left_hand = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		left_hand.p.x(list->get(index++).asDouble());
		left_hand.p.y(list->get(index++).asDouble());
		left_hand.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		left_hand.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	    
	    if(list->get(index).asBlobLength()!=0)
	    {
		right_hand = yarp_KDL::fromBlob(list->get(index++));
	    }
	    else
	    {  
		right_hand.p.x(list->get(index++).asDouble());
		right_hand.p.y(list->get(index++).asDouble());
		right_hand.p.z(list->get(index++).asDouble());
		double qx,qy,qz,qw;
		qx = list->get(index++).asDouble();
		qy = list->get(index++).asDouble();
		qz = list->get(index++).asDouble();
		qw = list->get(index++).asDouble();
		right_hand.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    }
	}

	return;
    }
  
};

#endif // DEBRIS_MSG