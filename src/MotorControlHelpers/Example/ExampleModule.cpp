#include "ExampleModule.h"

#include <stdexcept>      // std::out_of_range


using namespace yarp::os;
using namespace yarp::dev;
using namespace std;

ExampleModule::ExampleModule() : _verbose(true)
{
    cout << "\n\n$$$ExampleModule::Constructor" << endl;

    _period = 2;
//    _parts["left_arm"]  = &left_arm;
//    _parts["left_leg"]  = &left_leg;
//    _parts["right_arm"] = &right_arm;
//    _parts["right_leg"] = &right_leg;
//    _parts["torso"]     = &torso;
}

bool ExampleModule::open(yarp::os::Searchable &rf)
{
    cout << "\n\n$$$ExampleModule::open" << endl;
    cout << "params are " << rf.toString();
    return coman.open(rf);
}

bool ExampleModule::configure(yarp::os::ResourceFinder &rf)
{
    Property config;
    config.fromString(rf.toString());
    cout << "\n\n$$$ExampleModule::configure" << endl;
    cout << "params are " << rf.toString();
    return coman.open(rf);
}


// RFmodule functions
double ExampleModule::getPeriod()
{
//    cout << "\n\n$$$ExampleModule::getPeriod" << endl;
    return _period;
}

bool ExampleModule::setPeriod(double period)
{
    cout << "\n\n$$$ExampleModule::setPeriod" << endl;

    _period = period;
    return true;
}

bool ExampleModule::updateModule()
{
    int axes;
    coman.left_arm.posCtrl2_p->getAxes(&axes);
    cout << "ExampleModule axes: " << axes << endl;
    return true;
}


// IMultipleWrapper interface
bool ExampleModule::attachAll(const yarp::dev::PolyDriverList &device2attach)
{
    cout << "\n\n$$$ExampleModule::attachAll" << endl;
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
		cout << "ExampleModule: Device to attach to (" << device2attach[0]->key << ") was not found in the map!!!" << std::endl;
		return false;
	}

    if(!device->attach(device2attach[0]->poly))
	{
    	return false;
	}

    this->runModule();
    return true;
}

bool ExampleModule::detachAll()
{
    cout << "\n\n$$$ExampleModule::detachAll" << endl;

    return true;
}
