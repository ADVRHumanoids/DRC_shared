#ifndef ROBOTMODULE_H
#define ROBOTMODULE_H

#include <map>

#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/dev/DeviceDriver.h>
#include <yarp/os/ConstString.h>


// Include the Helper for Motor Control
#include "MotorControlHelper.h"

class RobotHelper:   public yarp::dev::DeviceDriver,
                     public yarp::dev::IMultipleWrapper
{
public:
    RobotHelper();

    // Yarp device driver functions
    bool open(yarp::os::Searchable &conf);

    MotorControlHelper             left_arm;
    MotorControlHelper             left_leg;
    MotorControlHelper             right_arm;
    MotorControlHelper             right_leg;
    MotorControlHelper             torso;

    std::map<yarp::os::ConstString, MotorControlHelper *> _parts;

    // IMultipleWrapper interface
    bool attachAll(const yarp::dev::PolyDriverList &device2attach);
    bool detachAll();

private:
    bool                                _verbose;
};

#endif // ROBOTMODULE_H
