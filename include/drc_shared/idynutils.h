#ifndef IDYNUTILS_H
#define IDYNUTILS_H

#include <urdf/model.h>
#include <iCub/iDynTree/DynTree.h>
#include <kdl_parser/kdl_parser.hpp>
#include <yarp/math/Math.h>
#include <yarp/sig/all.h>


struct kinematic_chain
{
public:
    kinematic_chain(std::string chain_name):chain_name(chain_name)
    {
        
    }
  std::string chain_name;
  std::string name;
  std::vector<std::string> joint_names;
  int index;
  std::vector<unsigned int> joint_numbers;
};

class iDynUtils
{
public:
    iDynUtils();
    kinematic_chain left_leg, left_arm,right_leg,right_arm,torso;
    iCub::iDynTree::DynTree coman_iDyn3; // iDyn3 Model
    void fromRobotToIDyn(const yarp::sig::Vector& q_chain,yarp::sig::Vector& q_out,kinematic_chain& chain);
    void updateiDyn3Model(const yarp::sig::Vector& q,const yarp::sig::Vector& dq_ref,const yarp::sig::Vector& ddq_ref);
    void setWorldPose(const yarp::sig::Vector& q,const yarp::sig::Vector& dq_ref,const yarp::sig::Vector& ddq_ref);
    
private:
    KDL::Tree coman_tree; // A KDL Tree
    urdf::Model coman_model; // A URDF Model
    void setJointNumbers(kinematic_chain& chain);
    void setChainIndex(std::string endeffector_name,kinematic_chain& chain);
    void setControlledKinematicChainsLinkIndex();
    void setControlledKinematicChainsJointNumbers();
    void setJointNames();
    void iDyn3Model();
    
};

#endif // IDYNUTILS_H