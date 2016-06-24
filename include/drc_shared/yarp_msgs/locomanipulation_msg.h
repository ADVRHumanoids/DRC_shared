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
        object_data.p.x(0.0);
        object_data.p.y(0.0);
        object_data.p.z(0.0);
        object_data.M = KDL::Rotation::Identity();
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame object_data;
    
    double scale_x,scale_y,scale_z;
    
    std::vector<std::vector<double>> solution_nodes;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

        list.addString(command);

        if(command=="data")
        {
            list.addString(frame);
            
            list.addDouble(object_data.p.x());
            list.addDouble(object_data.p.y());
            list.addDouble(object_data.p.z());
            double qx,qy,qz,qw;
            object_data.M.GetQuaternion(qx,qy,qz,qw);
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

            object_data.p.x(list->get(index++).asDouble());
            object_data.p.y(list->get(index++).asDouble());
            object_data.p.z(list->get(index++).asDouble());
            double qx,qy,qz,qw;
            qx = list->get(index++).asDouble();
            qy = list->get(index++).asDouble();
            qz = list->get(index++).asDouble();
            qw = list->get(index++).asDouble();
            object_data.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);

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

        return;
    }
  
};

#endif // LOCOMANIPULATION_MSG