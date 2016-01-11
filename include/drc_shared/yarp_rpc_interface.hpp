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

#ifndef _YARP_RPC_INTERFACE_H_
#define _YARP_RPC_INTERFACE_H_
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <vector>
#include <iostream>
#include <yarp/os/RateThread.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Bottle.h>
#include <mutex>
#include "internal_yarp_rpc_interface.hpp"

namespace walkman
{
namespace drc
{

    

template<class receive_type, class response_type>
class yarp_custom_rpc_client_interface:public internal_yarp_rpc_client_interface<receive_type, response_type>
{
public:
    yarp_custom_rpc_client_interface(const std::string& module_prefix):internal_yarp_rpc_client_interface< receive_type, response_type >(module_prefix,"/rpc")
    {
    }
};

class yarp_rpc_client_interface:public yarp_custom_rpc_client_interface<std::string,std::string>
{
public:
    yarp_rpc_client_interface(const std::string& module_prefix):yarp_custom_rpc_client_interface<std::string,std::string>(module_prefix)
    {
    }
};

template<class receive_type, class response_type>
class yarp_custom_rpc_server_interface:public internal_yarp_rpc_server_interface<receive_type, response_type>
{
public:
    yarp_custom_rpc_server_interface(const std::string& module_prefix):internal_yarp_rpc_server_interface< receive_type, response_type >(module_prefix,"/rpc")
    {
    }
};

class yarp_rpc_server_interface:public yarp_custom_rpc_server_interface<std::string,std::string>
{
public:
    yarp_rpc_server_interface(const std::string& module_prefix):yarp_custom_rpc_server_interface<std::string,std::string>(module_prefix)
    {
    }
};

}
}
#endif
