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

#ifndef VALVE_MSG
#define VALVE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include <vector>

class valve_msg
{
public:
    valve_msg()
    {
	command="";
	frame="";
	valve_data.p.x(0.25);
	valve_data.p.y(0.0);
	valve_data.p.z(0.2);
	valve_data.M = KDL::Rotation::Identity();
	radius=0.13;
	rotation=-1.4;
	affordances_number = 0;
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame valve_data;

    int affordances_number;

    std::vector<KDL::Frame> affordances;

    double radius;

    double rotation;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="valvedatasent")
	{
	    list.addString(frame);
	    list.addDouble(valve_data.p.x());
	    list.addDouble(valve_data.p.y());
	    list.addDouble(valve_data.p.z());
	    double ro,pi,ya;
	    valve_data.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	    list.addDouble(radius);
	    list.addDouble(rotation);

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
	}

        return temp;
    }

    bool fromBottle(const yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            command="";
            return false;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            command="";
            return false;
        }
        if (list->get(0).isNull())
        {
            command="";
            return false;
        }

        command = list->get(0).asString();

        if(command=="valvedatasent")
        {
            frame = list->get(1).asString();

            if(list->size() < 9)
                return false;

            /* checking valve position */
            if(!(list->get(2).isDouble() &&
                 list->get(3).isDouble() &&
                 list->get(4).isDouble()))
                return false;

            valve_data.p.x(list->get(2).asDouble());
            valve_data.p.y(list->get(3).asDouble());
            valve_data.p.z(list->get(4).asDouble());

            /* checking valve orientation */
            if(!(list->get(5).isDouble() &&
                 list->get(6).isDouble() &&
                 list->get(7).isDouble()))
                return false;

            double ro,pi,ya;
            ro = list->get(5).asDouble();
            pi = list->get(6).asDouble();
            ya = list->get(7).asDouble();
            valve_data.M = KDL::Rotation::RPY(ro,pi,ya);

            /* checking radius */
            if(!(list->get(8).isDouble()))
                return false;

            radius = list->get(8).asDouble();

            /* OPTIONAL PARAMETERS */

            if(list->size() > 9)
            {
                if(list->get(9).isDouble())
                    rotation = list->get(9).asDouble();
            }


            affordances.clear();
            affordances_number = 0;

            if(list->size() > 10 && list->get(10).isInt())
                affordances_number = list->get(10).asInt();

            int position = 10;
            for(int i = 0; i < affordances_number; i++)
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

            return true;
        }

        return false;
    }
  
};

#endif // VALVE_MSG
