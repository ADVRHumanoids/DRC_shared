/* Copyright [2014,2015] [Mirko Ferrati, Alessandro Settimi, Valerio Varricchio]
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.*/

#include <yarp/os/all.h>
#include <stdio.h>
#include <sstream>
#include "YARP_grabber.hpp"

int main(int argc, char *argv[]) {

  yarp::os::Network yarp;

  yarp::os::BufferedPort<yarp::os::Bottle> inputPort;
  yarp::os::Bottle b;
  
  // Instantiating a simple grabber
  yarp_msg_simple_grabber <yarp::os::Bottle> g;
  
  // Associating a grabber to a yarp port, with a 4-seconds timeout
  g.grab_from_port(inputPort, 4);  // this can be even done before opening the port! :O
  
  inputPort.open("/test/input");
  yarp::os::ContactStyle persist;
  persist.persistent = true;
  yarp.connect("/data", inputPort.getName(), persist);
  
  while (true){    
    if(g.expired()){	
      std::cout << " Port 1 expired." << std::endl;
    }
    
    if(g.get_updates(b)){
      std::cout << " Got \"" << b.toString() << "\" on input port." << std::endl;
    }
  }
  
  return 0;
}
