#ifndef FS_WALKING_MSG
#define FS_WALKING_MSG

#include <string>
#include <vector>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>


class fs_walking_msg
{
public:
    std::string command;

    std::vector<KDL::Frame> steps;
    KDL::Frame current_left_foot, current_right_foot;
    std::string starting_foot;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	if(command=="steps")
	{
            list.addInt(steps.size());
            for (KDL::Frame step:steps)
            {
                list.addDouble(step.p.x());
                list.addDouble(step.p.y());
                list.addDouble(step.p.z());
                double x,y,z,w;
                step.M.GetQuaternion(x,y,z,w);
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
            double x,y,z,w;
            current_right_foot.M.GetQuaternion(x,y,z,w);
            list.addDouble(x);
            list.addDouble(y);
            list.addDouble(z);
            list.addDouble(w);
            list.addString(starting_foot.c_str());
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
            int steps_size=list->get(counter++).asInt();
            steps.resize(steps_size);
            for (int i=0;i<steps_size;i++)
            {
                KDL::Frame step;
                step.p.x(list->get(counter++).asDouble());
                step.p.y(list->get(counter++).asDouble());
                step.p.z(list->get(counter++).asDouble());
                double x,y,z,w;
                x = list->get(counter++).asDouble();
                y = list->get(counter++).asDouble();
                z = list->get(counter++).asDouble();
                w = list->get(counter++).asDouble();
                step.M = KDL::Rotation::Quaternion(x,y,z,w);
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
            double x,y,z,w;
            x = list->get(counter++).asDouble();
            y = list->get(counter++).asDouble();
            z = list->get(counter++).asDouble();
            w = list->get(counter++).asDouble();
            current_right_foot.M = KDL::Rotation::Quaternion(x,y,z,w);
            starting_foot=list->get(counter++).asString();
	}
	return;
    }
  
};

#endif // FS_WALKING_MSG