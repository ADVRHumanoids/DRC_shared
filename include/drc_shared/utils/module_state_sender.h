/* 
 *  Small utility to stream a module's state at a 
 *  costant rate from a dedicated thread.
 * 
 *  email: v.varricchio@gmail.com 
 * 
 */

#ifndef __MODULE_STATE_SENDER__
#define __MODULE_STATE_SENDER__

#include <iostream>
#include <yarp/os/RateThread.h>
#include <yarp/os/BufferedPort.h>
#include <mutex>

class module_state_sender : public yarp::os::RateThread{

public:
	std::string state;	// String description of the module's state (quite common)
	yarp::os::Bottle data;	// Optional additional data
	
private: 
	yarp::os::BufferedPort<yarp::os::Bottle> port;
	std::mutex mtx; 
	std::string port_name;
	void send();


	module_state_sender(const std::string& port_name_, const int& period_ms_= 500, 
		const std::string& init_state_ = "initializing");

	void run();

	void setState(const std::string& new_state, const yarp::os::Bottle& data = yarp::os::Bottle());

	bool threadInit();

	void threadRelease();

}; 

#endif