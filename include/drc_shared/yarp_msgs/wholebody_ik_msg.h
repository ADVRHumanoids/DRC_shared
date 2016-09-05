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

#ifndef WHOLEBODY_IK_MSG
#define WHOLEBODY_IK_MSG

#include <string>
#include <vector>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

class wholebody_ik_msg
{
public:
    wholebody_ik_msg()
    {
        command="";
        frame="";
        desired_poses.clear();
    }
  
    std::string command;
    
    std::string frame;

    std::map<std::string,KDL::Frame> desired_poses;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

        list.addString(command);

        if(command=="poses")
        {
            list.addString(frame);

            list.addInt(desired_poses.size());

            for(auto pose:desired_poses)
            {
                list.addString(pose.first);
                list.addDouble(pose.second.p.x());
                list.addDouble(pose.second.p.y());
                list.addDouble(pose.second.p.z());
                double qx,qy,qz,qw;
                pose.second.M.GetQuaternion(qx,qy,qz,qw);
                list.addDouble(qx);
                list.addDouble(qy);
                list.addDouble(qz);
                list.addDouble(qw);
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

        if(command=="poses")
        {
            frame = list->get(1).asString();

            int num = list->get(2).asInt();

            int index=3;

            desired_poses.clear();

            for(int i=0; i<num; i++)
            {
                KDL::Frame temp_frame;
                std::string temp_name = list->get(index++).asString();

                temp_frame.p.x(list->get(index++).asDouble());
                temp_frame.p.y(list->get(index++).asDouble());
                temp_frame.p.z(list->get(index++).asDouble());
                double qx,qy,qz,qw;
                qx = list->get(index++).asDouble();
                qy = list->get(index++).asDouble();
                qz = list->get(index++).asDouble();
                qw = list->get(index++).asDouble();
                temp_frame.M = KDL::Rotation::Quaternion(qx,qy,qz,qw);

                desired_poses[temp_name] = temp_frame;
            }
        }

        return;
    }
  
};

#endif // WHOLEBODY_IK_MSG