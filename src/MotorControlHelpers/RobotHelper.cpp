#include "RobotHelper.h"

#include <stdexcept>      // std::out_of_range


using namespace yarp::os;
using namespace yarp::dev;
using namespace std;

RobotHelper::RobotHelper() : _verbose(true)
{
    cout << "\n\n$$$RobotHelper::Constructor" << endl;

    _parts["left_arm"]  = &left_arm;
    _parts["left_leg"]  = &left_leg;
    _parts["right_arm"] = &right_arm;
    _parts["right_leg"] = &right_leg;
    _parts["torso"]     = &torso;
}

bool RobotHelper::open(yarp::os::Searchable &rf)
{
    cout << "\n\n$$$RobotHelper::open" << endl;

    Value parts = rf.find("parts");
	if( parts.isNull())
	{
		cout << "no parts group found." << endl;
		return false;
	}
    Bottle *partList = parts.asList();


    _verbose = rf.check("verbose");

    if(_verbose)
        std::cout << "rf params are " << rf.toString() << std::endl;

    std::string name = rf.find("robot").asString();
    cout << "robot is " << name << endl;

    Property prop;
    prop.fromString(rf.toString().c_str());

    if(_verbose)
        prop.put(yarp::os::ConstString("verbose"), true);

    cout << "prop is " << prop.toString() << endl;

    std::cout << " \npartList->size() is " <<  partList->size() << "\n";
    for(int p=0; p < partList->size(); p++)
    {
        ConstString partName = partList->get(p).asString();
        std::cout << "Handling part " << partName << std::endl;

        prop.put("part", partName);
        if(!_parts[partName]->open(&prop) )
            return false;
    }
    return true;
}




// IMultipleWrapper interface
bool RobotHelper::attachAll(const yarp::dev::PolyDriverList &device2attach)
{
    cout << "\n\n$$$RobotHelper::attachAll" << endl;
    MotorControlHelper * device;

    try
	{
		// USE .at AND NOT the '[ ]' alternative!!! It will create a bug!!!
		/* The bug is caused by the fact that the [] version will create an unitialized element inside the map,
		 * causing the return of a wrong pointer.
		 * Furthermore the insert method used to correctly initialze the element will fail because a (wrong)
		 * element is already present preventing the map to be corrected.
		 */
	device =_parts.at(device2attach[0]->key);

	}
	catch (const std::out_of_range& errMsg)
	{
        cout << "RobotHelper: Device to attach to (" << device2attach[0]->key << ") was not found in the map!!!" << std::endl;
		return false;
	}

    if(!device->attach(device2attach[0]->poly))
	{
    	return false;
	}
    return true;
}

bool RobotHelper::detachAll()
{
    cout << "\n\n$$$RobotHelper::detachAll" << endl;

    return true;
}
