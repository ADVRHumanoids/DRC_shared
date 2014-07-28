#ifndef ROBOT_PLANNED_STATE_MSG_H
#define ROBOT_PLANNED_STATE_MSG_H

#include <string>
#include <map>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>

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

	return;
    }
  
};

#endif // ROBOT_PLANNED_STATE_MSG_H