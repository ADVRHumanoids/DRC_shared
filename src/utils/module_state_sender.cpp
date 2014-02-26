#include "module_state_sender.h"

module_state_sender::module_state_sender(const std::string& port_name_, const int& period_ms_, 
	const std::string& init_state_) :
	port_name(port_name_), state(init_state_), RateThread(period_ms_) {
}

void module_state_sender::run(){
	std::unique_lock<std::mutex>lck(mtx);
	send();
}

void module_state_sender::setState(const std::string& new_state, const yarp::os::Bottle& data_){
	std::unique_lock<std::mutex>lck(mtx);
	state = new_state;
	data = data_;
	send();
}

void module_state_sender::send(){
	yarp::os::Bottle& b = port.prepare();
	b.clear();
	b.addString(state);
	b.append(data);
	port.write();
}

bool module_state_sender::threadInit(){
	return port.open(port_name);
}

void module_state_sender::threadRelease(){
	port.close();
}
