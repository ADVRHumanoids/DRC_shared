#ifndef EXAMPLEMODULE_H
#define EXAMPLEMODULE_H

#include <map>

#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/dev/DeviceDriver.h>
#include <yarp/os/ConstString.h>


// Include the Helper for Motor Control
#include "RobotHelper.h"
//#include "MotorControlHelper.h"

class ExampleModule: public yarp::os::RFModule,
                     public yarp::dev::DeviceDriver,
                     public yarp::dev::IMultipleWrapper
{
public:
    ExampleModule();

    // Yarp RF Module core functions
    bool    setPeriod(double period);
    double  getPeriod();
    bool    updateModule();                                //!  Loop thread function
    bool    configure(yarp::os::ResourceFinder &rf);       //! Config function, called at the module start-up.
//    bool respond(const yarp::os::Bottle &command, yarp::os::Bottle &reply);  //! Called when a new message is received from the rpc input port

    // Yarp device driver functions
    bool open(yarp::os::Searchable &conf);

    RobotHelper         coman;

    std::map<yarp::os::ConstString, MotorControlHelper *> _parts;

    // IMultipleWrapper interface
    bool attachAll(const yarp::dev::PolyDriverList &device2attach);
    bool detachAll();

private:
    double                              _period;
    bool                                _verbose;
};

#endif // EXAMPLEMODULE_H
