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

#ifndef MULTICONTACT_MSG
#define MULTICONTACT_MSG

#include <string>
#include <vector>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

class multicontact_msg
{
public:
    multicontact_msg()
    {
        command="";
        frame="";
		traj_type=0;
        desired_poses.clear();
		touch["LSoftHand"] = false;
		touch["RSoftHand"] = false;
		touch["l_sole"] = false;
		touch["r_sole"] = false;
		duration=5.0;
		height=0.1;
    }
  
    std::string command;
    
    std::string frame;
	
	int traj_type;

	double duration;

	double height;

    std::map<std::string,KDL::Frame> desired_poses;

	std::map<std::string,bool> touch;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

        list.addString(command);

        if(command=="poses")
        {
            list.addString(frame);

			list.addInt(traj_type);

			list.addDouble(duration);

			list.addDouble(height);

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

		if(command=="touch")
		{
            for(auto t:touch)
			{
				list.addString(t.first);
				list.addInt(t.second);
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
			int index=1;

			frame = list->get(index++).asString();
			traj_type = list->get(index++).asInt();
			duration = list->get(index++).asDouble();
			height = list->get(index++).asDouble();
			int num = list->get(index++).asInt();

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

		if(command=="touch")
		{
			int index=1;

            for(int i=0;i<4;i++)
			{
				std::string ee = list->get(index++).asString();
				touch[ee] = list->get(index++).asInt();
			}
        }

        return;
    }
  
};

#endif // MULTICONTACT_MSG