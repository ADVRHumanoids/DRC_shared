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
#include <yarp/os/BufferedPort.h>
#include <GYM/internal_yarp_command_interface.hpp>

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
                std::string temp_i=port_suffix+"_client:i";
                std::string temp_o=port_suffix+"_server";
                sender=new internal_yarp_command_sender_interface<request_type>(module_prefix,temp_o);
                receiver=new internal_yarp_command_interface<response_type>(module_prefix,temp_i);
            }
            
            bool sendCommand(request_type& cmd, response_type& resp, int seq_num=0)
            {
//                 yarp::os::Bottle b, response;
// 		b.clear();
//              b.append(cmd.toBottle());
// 		b.addInt(seq_num);
                sender->sendCommand(cmd,seq_num);
//                 client_port.write(b,response);
                receiver->getCommand(resp,seq_num,true); //Client will block until a response!!
//                 resp.fromBottle(&response);
                return true;
            }
        private:
            internal_yarp_command_interface<response_type>* receiver;
            internal_yarp_command_sender_interface<request_type>* sender;
//             yarp::os::RpcClient client_port;
        };
        
        
        template<> class internal_yarp_rpc_client_interface<std::string,std::string>
        {
        public:
            internal_yarp_rpc_client_interface(const std::string& module_prefix_,const std::string& port_suffix)
            {
                auto module_prefix=module_prefix_;
                if (module_prefix[0]=='/') module_prefix=module_prefix.substr(1);
                std::string temp_i=port_suffix+"_client:i";
                std::string temp_o=port_suffix+"_server";
                sender=new internal_yarp_command_sender_interface<std::string>(module_prefix,temp_o);
                receiver=new internal_yarp_command_interface<std::string>(module_prefix,temp_i);
            }
            
            bool sendCommand(const std::string& cmd, std::string& resp, int seq_num=0)
            {   
                sender->sendCommand(cmd,seq_num);
                receiver->getCommand(resp,true); //Client will block until a response!!
            }
            
            bool sendCommand(int cmd, int& resp, int seq_num=0)
            {
                sender->sendCommand(cmd,seq_num);
                receiver->getCommand(resp,true); //Client will block until a response!!
            }
            
        private:
            internal_yarp_command_interface<std::string>* receiver;
            internal_yarp_command_sender_interface<std::string>* sender;
        };
        
        

        template<class receive_type, class response_type> class internal_yarp_rpc_server_interface
        {
            
        public:
            
            internal_yarp_rpc_server_interface(const std::string& module_prefix,const std::string& port_suffix)
            {
                std::string temp_i=port_suffix+"_server:i";
                std::string temp_o=port_suffix+"_client";
                sender=new internal_yarp_command_sender_interface<response_type>(module_prefix,temp_o);
                receiver=new internal_yarp_command_interface<receive_type>(module_prefix,temp_i);
            }
            
            bool getCommand ( receive_type& cmd, int& seq_num )
            {
                return receiver->getCommand(cmd,seq_num);
//                 yarp::os::Bottle bot_command;
//                 seq_num=-1;
//                 
//                 if (!server_port.read(bot_command))
//                 {
//                     return false;
//                 }
//                 else
//                 {
//                     seq_num = bot_command.pop().asInt();
// 		    command_i.fromBottle(&bot_command);
// 		    cmd=command_i;
// 		    return true;
//                 }
            }

            ~internal_yarp_rpc_server_interface()
            {
//                 server_port.close();
            }

            bool reply(response_type &resp,int seq_num)
            {
//                 yarp::os::Bottle response;
//                 response.clear();
//                 response.append(resp.toBottle());
//                 response.addInt(seq_num);
//                 server_port.reply(response);
                return sender->sendCommand(resp,seq_num);
            }

        private:
            receive_type command_i;
            internal_yarp_command_interface<receive_type>* receiver;
            internal_yarp_command_sender_interface<response_type>* sender;
//             yarp::os::RpcServer server_port;
        };
        
        template<> class internal_yarp_rpc_server_interface<std::string,std::string>
        {
        public:
            internal_yarp_rpc_server_interface(const std::string& module_prefix,const std::string& port_suffix)
            {
                std::string temp_i=port_suffix+"_server:i";
                std::string temp_o=port_suffix+"_client";
                sender=new internal_yarp_command_sender_interface<std::string>(module_prefix,temp_o);
                receiver=new internal_yarp_command_interface<std::string>(module_prefix,temp_i);
            }

            bool getCommand(int& command)
            {
                return receiver->getCommand(command);
            }

            bool reply(int resp)
            {
                return sender->sendCommand(resp);
            }

            std::string getCommand()
            {
                return receiver->getCommand();
            }

            bool reply(std::string &resp,int& seq_num)
            {
                return sender->sendCommand(resp,seq_num);
            }

            bool getCommand (std::string & cmd)
            {
                return receiver->getCommand(cmd);
            }

            bool getCommand ( std::string& cmd, int& seq_num )
            {
                return receiver->getCommand(cmd,seq_num);
            }

            ~internal_yarp_rpc_server_interface()
            {

            }

        private:
            std::string command_i;
            internal_yarp_command_interface<std::string>* receiver;
            internal_yarp_command_sender_interface<std::string>* sender;
        };
    }
}


#endif
