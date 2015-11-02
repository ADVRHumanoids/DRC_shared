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

#ifndef VEHICLE_MSG
#define VEHICLE_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

class vehicle_msg
{
public:
    vehicle_msg()
    {
	// TODO ADD RIGHT CUSTOM DATA
	command="";
	frame="";
	vehicle_data.p.x(0.0);
	vehicle_data.p.y(0.0);
	vehicle_data.p.z(0.0);
	vehicle_data.M = KDL::Rotation::Identity();
    }
  
    std::string command;
    
    std::string frame;
    
    KDL::Frame vehicle_data;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="vehicledatasent")
	{
	    list.addString(frame);
	    list.addDouble(vehicle_data.p.x());
	    list.addDouble(vehicle_data.p.y());
	    list.addDouble(vehicle_data.p.z());
	    double ro,pi,ya;
	    vehicle_data.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
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

	if(command=="vehicledatasent")
	{
	    frame = list->get(1).asString();
	    vehicle_data.p.x(list->get(2).asDouble());
	    vehicle_data.p.y(list->get(3).asDouble());
	    vehicle_data.p.z(list->get(4).asDouble());
	    double ro,pi,ya;
	    ro = list->get(5).asDouble();
	    pi = list->get(6).asDouble();
	    ya = list->get(7).asDouble();
	    vehicle_data.M = KDL::Rotation::RPY(ro,pi,ya);
	}

	return;
    }
};

#endif // VEHICLE_MSG