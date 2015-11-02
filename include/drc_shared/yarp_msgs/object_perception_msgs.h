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

#ifndef OBJECT_PERCEPTION_MSGS
#define OBJECT_PERCEPTION_MSGS

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl_parser/kdl_parser.hpp>
class object_perception_in_msg
{
public:
    object_perception_in_msg():command("")
    {}

    std::string command;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

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

	return;
    }
  
};


class object_perception_out_msg
{
public:
    std::string reference_frame;
    double radius;
    KDL::Frame object_pose;
    std::string status;
    int affordances_number;
    std::vector<KDL::Frame> affordances;
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(reference_frame);
	list.addDouble(radius);
	
	list.addDouble(object_pose.p.x());
	list.addDouble(object_pose.p.y());
	list.addDouble(object_pose.p.z());
	double qx,qy,qz,qw;
	object_pose.M.GetQuaternion(qx,qy,qz,qw);
	list.addDouble(qx);
	list.addDouble(qy);
	list.addDouble(qz);
	list.addDouble(qw);

  list.addString(status);

	list.addInt(affordances_number);

	for(int i=0;i<affordances_number;i++)
	{
	    list.addDouble(affordances.at(i).p.x());
	    list.addDouble(affordances.at(i).p.y());
	    list.addDouble(affordances.at(i).p.z());
	    double qx,qy,qz,qw;
	    affordances.at(i).M.GetQuaternion(qx,qy,qz,qw);
	    list.addDouble(qx);
	    list.addDouble(qy);
	    list.addDouble(qz);
	    list.addDouble(qw);
	}

        return temp;
    }
    
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            reference_frame="";
	    radius=0;
	    object_pose = KDL::Frame::Identity();
	    status="";
	    affordances_number=0;
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            reference_frame="";
	    radius=0;
	    object_pose = KDL::Frame::Identity();
	    status="";
	    affordances_number=0;
            return;
        }
        if (list->get(0).isNull())
        {
            reference_frame="";
	    radius=0;
	    object_pose = KDL::Frame::Identity();
	    status="";
	    affordances_number=0;
            return;
        }

        reference_frame = list->get(0).asString();
        radius=list->get(1).asDouble();
        
	object_pose.p.x(list->get(2).asDouble());
	object_pose.p.y(list->get(3).asDouble());
	object_pose.p.z(list->get(4).asDouble());
	double qx,qy,qz,qw;
	qx = list->get(5).asDouble();
	qy = list->get(6).asDouble();
	qz = list->get(7).asDouble();
	qw = list->get(8).asDouble();
	object_pose.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);

  status=list->get(9).asString();

	affordances.clear();
	affordances_number = list->get(10).asInt();
	
	int position = 10;
	for(int i=0;i<affordances_number;i++)
	{
	    KDL::Frame temp_frame;
	    temp_frame.p.x(list->get(position+1).asDouble());
	    temp_frame.p.y(list->get(position+2).asDouble());
	    temp_frame.p.z(list->get(position+3).asDouble());
	    double qx,qy,qz,qw;
	    qx = list->get(position+4).asDouble();
	    qy = list->get(position+5).asDouble();
	    qz = list->get(position+6).asDouble();
	    qw = list->get(position+7).asDouble();
	    temp_frame.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
	    affordances.push_back(temp_frame);
	    position+=7;
	}
	return;
    }
  
};

#endif // OBJECT_PERCEPTION_MSGS