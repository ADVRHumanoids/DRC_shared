#include <drc_shared/utils/module_state_streamer.h>
#include <assert.h>

module_state_streamer::module_state_streamer(const int& period_ms_) : RateThread(period_ms_), state(DEF_MODULE_STATE){
}

module_state_streamer::module_state_streamer(const std::string& port_name_, const int& period_ms_, 
	const std::string& init_state_) :
	port_name(port_name_), state(init_state_), RateThread(period_ms_) {
}

void module_state_streamer::run(){
	std::unique_lock<std::mutex>lck(mtx);
	send();
}

void module_state_streamer::setState(const std::string& new_state, const yarp::os::Bottle& data_){
	std::unique_lock<std::mutex>lck(mtx);
	state = new_state;
	data = data_;
	send();
}

void module_state_streamer::send(){
	yarp::os::Bottle& b = port.prepare();
	b.clear();
	b.addString(state);
	b.append(data);
	port.write();
}

bool module_state_streamer::threadInit(){
	if(port_name == ""){
	  assert(false && "State streaming port not specified.");
	}
	return port.open(port_name);
}

void module_state_streamer::threadRelease(){
	port.close();
}

void module_state_streamer::setPort(const std::string& port_name_){
      port_name = port_name_;
}
