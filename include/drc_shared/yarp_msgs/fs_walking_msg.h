#ifndef FS_WALKING_MSG
#define FS_WALKING_MSG

#include <string>
#include <vector>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

class step_with_name
{
public:
  step_with_name()
  {
      pose = KDL::Frame::Identity();
      step_name = "";
  }
  KDL::Frame pose;
  std::string step_name;
};

class fs_walking_msg
{
public:
    std::string command;

	double number=0;

    std::vector<step_with_name> steps;
    KDL::Frame current_left_foot, current_right_foot;
    std::string starting_foot;
	
	//Turning 
	double turnAngle;
	
	//Stepping over obstacle 
    double obstacleHeight, obstacleLength;
    double stepLengthX, stepLengthY;
    
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	if(command=="steps")
	{
            list.addInt(steps.size());
            for (step_with_name step:steps)
            {
	        list.addString(step.step_name);
                list.addDouble(step.pose.p.x());
                list.addDouble(step.pose.p.y());
                list.addDouble(step.pose.p.z());
                double x,y,z,w;
                step.pose.M.GetQuaternion(x,y,z,w);
                list.addDouble(x);
                list.addDouble(y);
                list.addDouble(z);
                list.addDouble(w);
            }
            list.addDouble(current_left_foot.p.x());
            list.addDouble(current_left_foot.p.y());
            list.addDouble(current_left_foot.p.z());
            double x,y,z,w;
            current_left_foot.M.GetQuaternion(x,y,z,w);
            list.addDouble(x);
            list.addDouble(y);
            list.addDouble(z);
            list.addDouble(w);
            list.addDouble(current_right_foot.p.x());
            list.addDouble(current_right_foot.p.y());
            list.addDouble(current_right_foot.p.z());
            current_right_foot.M.GetQuaternion(x,y,z,w);
            list.addDouble(x);
            list.addDouble(y);
            list.addDouble(z);
            list.addDouble(w);
            list.addString(starting_foot.c_str());
	}
	if (command=="go_there")
        {
            list.addDouble(steps.front().pose.p.x());
            list.addDouble(steps.front().pose.p.y());
            list.addDouble(steps.front().pose.p.z());
            double x,y,z,w;
            steps.front().pose.M.GetQuaternion(x,y,z,w);
            list.addDouble(x);
            list.addDouble(y);
            list.addDouble(z);
            list.addDouble(w);
			list.addDouble(stepLengthX);
			list.addDouble(stepLengthY);
			 
        }
	if (command=="Turn")
	{
		list.addDouble(number);
	}
    if (command=="turn")
        {
		  list.addDouble(turnAngle);
        }
	if (command=="side_step_over")
        {
		  list.addDouble(obstacleHeight);
		  list.addDouble(obstacleLength);
        }
    if (command=="valve_turn_conf")
        {
		  list.addDouble(steps.front().pose.p.x());
		  list.addDouble(steps.front().pose.p.y());
		  list.addDouble(steps.front().pose.p.z());
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
        int counter=0;
        
        command = list->get(counter++).asString();

	if(command=="steps")
	{
            steps.clear();
            int steps_size=list->get(counter++).asInt();
            for (int i=0;i<steps_size;i++)
            {
                step_with_name step;
		step.step_name = list->get(counter++).asString();
                step.pose.p.x(list->get(counter++).asDouble());
                step.pose.p.y(list->get(counter++).asDouble());
                step.pose.p.z(list->get(counter++).asDouble());
                double x,y,z,w;
                x = list->get(counter++).asDouble();
                y = list->get(counter++).asDouble();
                z = list->get(counter++).asDouble();
                w = list->get(counter++).asDouble();
                step.pose.M = KDL::Rotation::Quaternion(x,y,z,w);
                steps.push_back(step);
            }
            current_left_foot.p.x(list->get(counter++).asDouble());
            current_left_foot.p.y(list->get(counter++).asDouble());
            current_left_foot.p.z(list->get(counter++).asDouble());
            double x,y,z,w;
            x = list->get(counter++).asDouble();
            y = list->get(counter++).asDouble();
            z = list->get(counter++).asDouble();
            w = list->get(counter++).asDouble();
            current_left_foot.M = KDL::Rotation::Quaternion(x,y,z,w);
            current_right_foot.p.x(list->get(counter++).asDouble());
            current_right_foot.p.y(list->get(counter++).asDouble());
            current_right_foot.p.z(list->get(counter++).asDouble());
            x = list->get(counter++).asDouble();
            y = list->get(counter++).asDouble();
            z = list->get(counter++).asDouble();
            w = list->get(counter++).asDouble();
            current_right_foot.M = KDL::Rotation::Quaternion(x,y,z,w);
            starting_foot=list->get(counter++).asString();
	}
	if (command=="go_there")
        {
            step_with_name step;
            step.pose.p.x(list->get(counter++).asDouble());
            step.pose.p.y(list->get(counter++).asDouble());
            step.pose.p.z(list->get(counter++).asDouble());
            double x,y,z,w;
            x = list->get(counter++).asDouble();
            y = list->get(counter++).asDouble();
            z = list->get(counter++).asDouble();
            w = list->get(counter++).asDouble();
            step.pose.M = KDL::Rotation::Quaternion(x,y,z,w);
            steps.push_back(step);
        }
	if (command=="turn")
        {
		  turnAngle = list->get(counter++).asDouble();
        }
    if (command=="side_step_over")
        {
		  obstacleHeight = list->get(counter++).asDouble();
		  obstacleLength = list->get(counter++).asDouble();
        }
     if (command=="valve_turn_conf")
        {
		  
		  step_with_name step;
		  step.pose.p.x(list->get(counter++).asDouble());
		  step.pose.p.y(list->get(counter++).asDouble());
		  step.pose.p.z(list->get(counter++).asDouble());
		  steps.push_back(step);
        }   

	if (command=="Turn")
	{
		number=list->get(counter++).asDouble();
		std::cout<<"Turn:"<<number<<std::endl;
	}   
        
	return;
    }
  
};

#endif // FS_WALKING_MSG
