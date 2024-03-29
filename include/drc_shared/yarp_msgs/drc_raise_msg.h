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

#ifndef DRC_RAISE_MSG
#define DRC_RAISE_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl_parser/kdl_parser.hpp>
class drc_raise_msg
{
public:
    drc_raise_msg():reference_frame("")
    {}

    std::string reference_frame;

    int pose_number;
    std::map<std::string,KDL::Frame> poses;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();
	double qx,qy,qz,qw;
	list.addString(reference_frame);

	list.addInt(poses.size());

	for(auto pose:poses)
	{
	    list.addString(pose.first);

	    list.addDouble(pose.second.p.x());
	    list.addDouble(pose.second.p.y());
	    list.addDouble(pose.second.p.z());
	    pose.second.M.GetQuaternion(qx,qy,qz,qw);
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
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            reference_frame="";
            return;
        }
        if (list->get(0).isNull())
        {
            reference_frame="";
            return;
        }

        reference_frame = list->get(0).asString();

	pose_number = list->get(1).asInt();

	double qx,qy,qz,qw;

	poses.clear();

	for(int i=2;i<2+pose_number*7;)
	{
	    std::string temp_str = list->get(i).asString();

	    poses[temp_str].p.x(list->get(i+1).asDouble());
	    poses[temp_str].p.y(list->get(i+2).asDouble());
	    poses[temp_str].p.z(list->get(i+3).asDouble());
	    
	    poses[temp_str].M = KDL::Rotation::Quaternion(list->get(i+4).asDouble(),list->get(i+5).asDouble(),list->get(i+6).asDouble(),list->get(i+7).asDouble());
	    i+=8;
	}

	return;
    }
};

#endif // DRC_RAISE_MSG