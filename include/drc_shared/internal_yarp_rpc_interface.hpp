#ifndef _INTERNAL_YARP_RPC_INTERFACE_H_
#define _INTERNAL_YARP_RPC_INTERFACE_H_
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <vector>
#include <iostream>
#include <yarp/os/RateThread.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Bottle.h>
#include <mutex>
#include <boost/concept_check.hpp>


namespace walkman
{
    namespace drc
    {
        
        template<class request_type, class response_type > class internal_yarp_rpc_client_interface
        {
        public:
            internal_yarp_rpc_client_interface(const std::string& module_prefix_,const std::string& port_suffix)
            {
	        auto module_prefix=module_prefix_;
                if (module_prefix[0]=='/') module_prefix=module_prefix.substr(1);
                std::string temp_o="/"+module_prefix+port_suffix+"_rpc:o";
                std::string temp_i="/"+module_prefix+port_suffix+"_rpc:i";
                
                client_port.open(temp_o.c_str());
                yarp::os::ContactStyle style;
                style.persistent = true;
                yarp::os::Network::connect(temp_o.c_str(),temp_i.c_str(), style);
            }
            
            bool sendCommand(request_type& cmd, response_type& resp, int seq_num=0)
            {
                yarp::os::Bottle b, response;
		b.clear();
                b.append(cmd.toBottle());
		b.addInt(seq_num);
                client_port.write(b,response);
                resp.fromBottle(response);
                return true;
            }
        private:
            yarp::os::RpcClient client_port;
        };
        
        
        template<> class internal_yarp_rpc_client_interface<std::string,std::string>
        {
        public:
            internal_yarp_rpc_client_interface(const std::string& module_prefix_,const std::string& port_suffix)
            {
                auto module_prefix=module_prefix_;
                if (module_prefix[0]=='/') module_prefix=module_prefix.substr(1);
                std::string temp_o="/"+module_prefix+port_suffix+"_rpc:o";
                std::string temp_i="/"+module_prefix+port_suffix+"_rpc:i";
                client_port.setRpcMode(true);
                
                client_port.open(temp_o.c_str());
                yarp::os::ContactStyle style;
                style.persistent = true;
                yarp::os::Network::connect(temp_o.c_str(),temp_i.c_str(), style);
            }
            
            bool sendCommand(const std::string& cmd, std::string& resp, int seq_num=0)
            {   
                yarp::os::Bottle b, response;
                b.clear();
                b.addString(cmd);
                b.addInt(seq_num);
                client_port.write(b,response);
                resp=response.get(0).asString();
                return true;
            }
            
            bool sendCommand(int cmd, int& resp, int seq_num=0)
            {
                yarp::os::Bottle b, response;
                b.clear();
                b.addInt(cmd);
                client_port.write(b,response);
                resp=response.get(0).asInt();
                return true;
            }
            
        private:
            yarp::os::RpcClient client_port;
        };
        
        

        template<class receive_type, class response_type> class internal_yarp_rpc_server_interface
        {
            
        public:
            
            internal_yarp_rpc_server_interface(const std::string& module_prefix,const std::string& port_suffix)
            {
                std::string temp="/"+module_prefix+port_suffix+"_rpc:i";
                server_port.open(temp.c_str());
                server_port.setRpcMode(true);
                
            }
            
            bool getCommand ( receive_type& cmd, int& seq_num )
            {
                yarp::os::Bottle bot_command;
                seq_num=-1;
                if (!server_port.read(bot_command))
                {
                    return false;
                }
                else
                {
                    seq_num = bot_command.pop().asInt();
		    command_i.fromBottle(bot_command);
		    cmd=command_i;
		    return true;
                }
            }
            
            bool reply(response_type &resp,int& seq_num)
            {
                yarp::os::Bottle response;
                response.clear();
                response.append(resp.toBottle());
                response.addInt(seq_num);
                server_port.reply(response);
            }
            
        private:
            receive_type command_i;
            yarp::os::RpcServer server_port;
        };
        
        template<> class internal_yarp_rpc_server_interface<std::string,std::string>
        {
        public:
            
            internal_yarp_rpc_server_interface(const std::string& module_prefix,const std::string& port_suffix)
            {
                std::string temp="/"+module_prefix+port_suffix+"_rpc:i";
                server_port.open(temp.c_str());
                server_port.setRpcMode(true);
            }
            
            bool getCommand(int& command)
            {
                yarp::os::Bottle bot_command;
                if (!server_port.read(bot_command))
                {
                    return false;
                }
                else
                {
                    command= bot_command.get(0).asInt();
                    return true;
                }
            }
            
            bool reply(int resp)
            {
                yarp::os::Bottle response;
                response.clear();
                response.addInt(resp);
                server_port.reply(response);
            }
            
            std::string getCommand()
            {
                yarp::os::Bottle bot_command;
                if (!server_port.read(bot_command))
                {
                    return "";
                }
                else
                {
                    std::string command_i= bot_command.get(0).asString();
                    return command_i;
                }
            }
            
            bool reply(std::string &resp,int& seq_num)
            {
                yarp::os::Bottle response;
                response.clear();
                response.addString(resp);
                response.addInt(seq_num);
                server_port.reply(response);
            }
            
            bool getCommand (std::string & cmd)
            {
                yarp::os::Bottle bot_command;
                if (!server_port.read(bot_command))
                {
                    cmd="";
                    return false;
                }
                else
                {
                    cmd=bot_command.get(0).asString();
                    return true;
                }
            }
            
            bool getCommand ( std::string& cmd, int& seq_num )
            {
                yarp::os::Bottle bot_command;
                seq_num=-1;
                if (!server_port.read(bot_command))
                {
                    return false;
                }
                else
                {
                    seq_num = bot_command.pop().asInt();
                    cmd=bot_command.get(0).asString();
                    return true;
                }
            }

        private:
            yarp::os::RpcServer server_port;
        };
    }
}


#endif
