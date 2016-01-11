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

#ifndef FS_PLANNER_MSG
#define FS_PLANNER_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl_parser/kdl_parser.hpp>
class fs_planner_msg
{
public:
    double x,y,z;
    std::string command;
    int num_steps;
    std::string starting_foot;
    KDL::Frame left_foot;
    KDL::Frame right_foot;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	if(command=="direction")
	{
	    list.addDouble(x);
	    list.addDouble(y);
	    list.addDouble(z);
	}
	if (command=="set_starting_foot")
        {
            list.addString(starting_foot.c_str());
        }
	if (command=="send_plan_to_walking")
        {
            //Nothing to do for now
        }
	if (command=="plan_num")
        {
            list.addInt(num_steps);
        }
        if(command=="ik_check" || command=="ik_com_check" || command=="custom_step")
	{
	    list.addDouble(left_foot.p.x());
	    list.addDouble(left_foot.p.y());
	    list.addDouble(left_foot.p.z());
	    double ro,pi,ya;
	    left_foot.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	    
	    list.addDouble(right_foot.p.x());
	    list.addDouble(right_foot.p.y());
	    list.addDouble(right_foot.p.z());
	    right_foot.M.GetRPY(ro,pi,ya);
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
        if (command=="set_stance_foot")
        {
            starting_foot=list->get(1).asString();
        }
        if (command=="send_plan_to_walking")
        {
            //nothing to do for now
        }
	if(command=="direction")
	{
	    x = list->get(1).asDouble();
	    y = list->get(2).asDouble();
	    z = list->get(3).asDouble();
	}
	if (command=="plan_num")
        {
            num_steps=list->get(1).asInt();
        }
        if(command=="ik_check" || command=="ik_com_check" || command=="custom_step")
	{
	    left_foot.p.x(list->get(1).asDouble());
	    left_foot.p.y(list->get(2).asDouble());
	    left_foot.p.z(list->get(3).asDouble());
	    double ro,pi,ya;
	    ro = list->get(4).asDouble();
	    pi = list->get(5).asDouble();
	    ya = list->get(6).asDouble();
	    left_foot.M = KDL::Rotation::RPY(ro,pi,ya);
	    
	    right_foot.p.x(list->get(7).asDouble());
	    right_foot.p.y(list->get(8).asDouble());
	    right_foot.p.z(list->get(9).asDouble());
	    ro = list->get(10).asDouble();
	    pi = list->get(11).asDouble();
	    ya = list->get(12).asDouble();
	    right_foot.M = KDL::Rotation::RPY(ro,pi,ya);
	}
	return;
    }
  
};

#endif // FS_PLANNER_MSG