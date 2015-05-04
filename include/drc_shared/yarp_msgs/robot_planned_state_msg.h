#ifndef ROBOT_PLANNED_STATE_MSG_H
#define ROBOT_PLANNED_STATE_MSG_H

#include <string>
#include <map>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>

#include <eigen3/Eigen/Eigen>

/*
 * MESSAGE STRUCTURE
 * 
 * N° of joints | "robot joints" | values
 * 
 * e.g: 3 robot joints 0.3 0.4 0.1
 * 
 */

class robot_planned_state_msg
{
public:
    
    std::map<std::string,double> joints;
    std::string base_link;
    Eigen::Affine3d FixedFrame_BaseLink;
        
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString("robot joints");
	list.addInt(joints.size());

	for(std::map<std::string,double>::iterator it=joints.begin();it!=joints.end();++it)
	{
	    list.addString(it->first);
	    list.addDouble(it->second);
	}

	list.addString(base_link);
	list.addDouble(FixedFrame_BaseLink.data()[0]);
	list.addDouble(FixedFrame_BaseLink.data()[1]);
	list.addDouble(FixedFrame_BaseLink.data()[2]);

        return temp;
    }
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        yarp::os::Bottle* list = temp->get(0).asList();
	
	std::string header = list->get(0).asString();
		
	int joint_number = list->get(1).asInt();
			
	unsigned int j=2;
	for(unsigned int i=0; i<joint_number;i++)
	{
	    joints[list->get(j).asString()] = list->get(j+1).asDouble(); 
	    	    
	    j+=2;
	}

	base_link = list->get(j).asString();
	FixedFrame_BaseLink.data()[0] = list->get(j+1).asDouble();
	FixedFrame_BaseLink.data()[1] = list->get(j+2).asDouble();
	FixedFrame_BaseLink.data()[2] = list->get(j+3).asDouble();

	return;
    }
  
};

#endif // ROBOT_PLANNED_STATE_MSG_H