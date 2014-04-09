/* 
 *  WARNING: This class was recently copy-pasted and renamed into yarp_status_interface,
 *           and might disappear when a common agreement on the shared interfaces is reached
 * 
 *  Small utility to stream a module's state as (a string + a Bottle)
 *  at a costant rate from a dedicated yarp::os::RateThread.
 * 
 *  email: v.varricchio@gmail.com 
 * 
 */

#ifndef __MODULE_STATE_STREAMER__
#define __MODULE_STATE_STREAMER__

#include <iostream>
#include <yarp/os/RateThread.h>
#include <yarp/os/BufferedPort.h>
#include <mutex>

#define DEF_MODULE_STATE "initializing"
#define DEF_MODULE_PERIOD_MS 500

class module_state_streamer : public yarp::os::RateThread{

  yarp::os::BufferedPort<yarp::os::Bottle> port;
  std::mutex mtx; 
  std::string port_name;
  void send();
    
public:
  std::string state;		// String description of the module's state (quite common)
  yarp::os::Bottle data;	// Optional additional data

  module_state_streamer(const int& period_ms_= DEF_MODULE_PERIOD_MS);

  module_state_streamer(const std::string& port_name_, const int& period_ms_= DEF_MODULE_PERIOD_MS, 
	  const std::string& init_state_ = DEF_MODULE_STATE);

  void setPort(const std::string& port_name_);
  
  void run();

  void setState(const std::string& new_state, const yarp::os::Bottle& data = yarp::os::Bottle());

  bool threadInit();

  void threadRelease();

}; 

#endif