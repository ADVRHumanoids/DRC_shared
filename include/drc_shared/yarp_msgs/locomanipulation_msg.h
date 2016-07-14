/* Copyright [2016] [Alessandro Settimi]
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

#ifndef LOCOMANIPULATION_MSG
#define LOCOMANIPULATION_MSG

#include <string>
#include <vector>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

#define STATE_DIM 5

class locomanipulation_msg
{
public:
    locomanipulation_msg()
    {
        // TODO ADD RIGHT CUSTOM DATA
        command="";
        frame="";
        scale_x=scale_y=scale_z=0.0;
        data = KDL::Frame::Identity();
        t_T_h = KDL::Frame::Identity();
        desired_position = KDL::Frame::Identity();
        stepLengthX = 0.1;
        stepLengthY = 0.05;
        trajType="linear";
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame data;
    KDL::Frame t_T_h;
    
    double scale_x,scale_y,scale_z;
    
    KDL::Frame desired_position;
    double stepLengthX;
    double stepLengthY;
    std::string trajType;
    
    std::vector<std::vector<double>> solution_nodes;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

        list.addString(command);

        if(command=="data")
        {
            list.addString(frame);
            
            list.addDouble(data.p.x()); //object data
            list.addDouble(data.p.y());
            list.addDouble(data.p.z());
            double qx,qy,qz,qw;
            data.M.GetQuaternion(qx,qy,qz,qw);
            list.addDouble(qx);
            list.addDouble(qy);
            list.addDouble(qz);
            list.addDouble(qw);
            
            list.addDouble(scale_x);
            list.addDouble(scale_y);
            list.addDouble(scale_z);
        }
        
        if(command=="solution")
        {
            list.addDouble(solution_nodes.size());
            for(auto node:solution_nodes)
                for(auto item:node)
                {
                    list.addDouble(item);
                }
        }
        
        if(command=="locomanipulate")
        {
            list.addDouble(desired_position.p.x()); //waist position
            list.addDouble(desired_position.p.y());
            list.addDouble(desired_position.p.z());
            double qx,qy,qz,qw;
            desired_position.M.GetQuaternion(qx,qy,qz,qw);
            list.addDouble(qx);
            list.addDouble(qy);
            list.addDouble(qz);
            list.addDouble(qw);

            list.addDouble(stepLengthX);
            list.addDouble(stepLengthY);

            list.addString(frame);

            list.addDouble(data.p.x()); //hand position
            list.addDouble(data.p.y());
            list.addDouble(data.p.z());
            data.M.GetQuaternion(qx,qy,qz,qw);
            list.addDouble(qx);
            list.addDouble(qy);
            list.addDouble(qz);
            list.addDouble(qw);
            
            list.addDouble(t_T_h.p.x()); // position of the head w.r.t. the object
            list.addDouble(t_T_h.p.y());
            list.addDouble(t_T_h.p.z());
            t_T_h.M.GetQuaternion(qx,qy,qz,qw);
            list.addDouble(qx);
            list.addDouble(qy);
            list.addDouble(qz);
            list.addDouble(qw);

            list.addString(trajType);

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
        if(command=="data")
        {
            frame = list->get(index++).asString();

            data.p.x(list->get(index++).asDouble());
            data.p.y(list->get(index++).asDouble());
            data.p.z(list->get(index++).asDouble());
            double qx,qy,qz,qw;
            qx = list->get(index++).asDouble();
            qy = list->get(index++).asDouble();
            qz = list->get(index++).asDouble();
            qw = list->get(index++).asDouble();
            data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);

            scale_x = list->get(index++).asDouble();
            scale_y = list->get(index++).asDouble();
            scale_z = list->get(index++).asDouble();
        }
        
        if(command=="solution")
        {
            solution_nodes.clear();

            double sol_dim = list->get(index++).asDouble();

            for(int ii=0; ii<sol_dim;ii++)
            {
                std::vector<double> node;
                for(int i=0; i<STATE_DIM;i++)
                {
                    node.push_back(list->get(index++).asDouble());
                }
                solution_nodes.push_back(node);
            }
        }

        if(command=="locomanipulate")
        {
            desired_position.p.x(list->get(index++).asDouble()); //NOTE: the robot position w.r.t. frame
            desired_position.p.y(list->get(index++).asDouble());
            desired_position.p.z(list->get(index++).asDouble());
            double qx,qy,qz,qw;
            qx = list->get(index++).asDouble();
            qy = list->get(index++).asDouble();
            qz = list->get(index++).asDouble();
            qw = list->get(index++).asDouble();
            desired_position.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);

            stepLengthX = list->get(index++).asDouble();
            stepLengthY = list->get(index++).asDouble();

            frame = list->get(index++).asString();

            data.p.x(list->get(index++).asDouble()); //NOTE: the hand position w.r.t. frame
            data.p.y(list->get(index++).asDouble());
            data.p.z(list->get(index++).asDouble());
            qx = list->get(index++).asDouble();
            qy = list->get(index++).asDouble();
            qz = list->get(index++).asDouble();
            qw = list->get(index++).asDouble();
            data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);

            t_T_h.p.x(list->get(index++).asDouble()); //NOTE: the position of the head w.r.t. the object
            t_T_h.p.y(list->get(index++).asDouble());
            t_T_h.p.z(list->get(index++).asDouble());
            qx = list->get(index++).asDouble();
            qy = list->get(index++).asDouble();
            qz = list->get(index++).asDouble();
            qw = list->get(index++).asDouble();
            t_T_h.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);
            trajType = list->get(index++).asString();
        }

        return;
    }
  
};

#endif // LOCOMANIPULATION_MSG