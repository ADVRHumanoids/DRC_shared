#ifndef YARP_SINGLE_CHAIN_INTERFACE_H
#define YARP_SINGLE_CHAIN_INTERFACE_H
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <vector>
#include <iostream>
#include <mutex>
#include <math.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/BufferedPort.h>


/**
 * These strings are supposed to be found into the SRDF of any robot we are working with
 */
namespace walkman{
    namespace robot{
        static const std::string left_arm = "left_arm";
        static const std::string right_arm = "right_arm";
        static const std::string left_leg = "left_leg";
        static const std::string right_leg = "right_leg";
        static const std::string torso = "torso";
        static const std::string chains = "chains";
        static const std::string sensors = "sensors";
        static const std::string base = "base";
    }
}

namespace walkman{
    namespace drc{

class yarp_single_chain_interface
{
public:
    /**
     * @brief yarp_single_chain_interface is a simple interface for control of kinematic chains
     * @param kinematic_chain the name of the kinematic chain as defined in the robot srdf
     * @param module_prefix_with_no_slash the module name
     * @param useSI does the sense() and move() use SI units? defaults to false
     */
    yarp_single_chain_interface(std::string kinematic_chain,
                                std::string module_prefix_with_no_slash,
                                bool useSI = false,
                                const int controlModeVocab = VOCAB_CM_POSITION
                                );
    virtual yarp::sig::Vector sense();
    virtual void sense(yarp::sig::Vector& q_sensed);

    yarp::sig::Vector sensePosition();
    void sensePosition(yarp::sig::Vector &q_sensed);

    yarp::sig::Vector senseVelocity();
    void senseVelocity(yarp::sig::Vector &velocity_sensed);

    yarp::sig::Vector senseTorque();
    void senseTorque(yarp::sig::Vector &tau_sensed);

    virtual void move(const yarp::sig::Vector& q_d);

    const int& getNumberOfJoints();
    const std::string &getChainName();

    ~yarp_single_chain_interface();

private:

    bool createPolyDriver ( const std::string &kinematic_chain, yarp::dev::PolyDriver &polyDriver );
    std::string kinematic_chain;
    int joint_numbers;
    std::string module_prefix;
    yarp::sig::Vector q_buffer;
    yarp::sig::Vector qdot_buffer;
    yarp::sig::Vector tau_buffer;
    bool internal_isAvailable;
    yarp::dev::PolyDriver polyDriver;
    bool _useSI;

    void convertEncoderToSI(yarp::sig::Vector& vector);
    void convertMotorCommandToSI(yarp::sig::Vector& vector);
    yarp::sig::Vector convertMotorCommandToSI(const yarp::sig::Vector& vector);
public:
    bool& isAvailable;

    yarp::dev::IEncodersTimed *encodersMotor;
    yarp::dev::IPositionDirect *positionDirect;
    yarp::dev::IControlMode *controlMode;
    yarp::dev::IPositionControl2 *positionControl;
    yarp::dev::IImpedanceControl *impedancePositionControl;
    yarp::dev::ITorqueControl *torqueControl;
    yarp::dev::IVelocityControl *velocityControl;

};


}
}


#endif // YARP_SINGLE_CHAIN_INTERFACE_H
