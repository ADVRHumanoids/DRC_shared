#ifndef GENERIC_THREAD_HPP
#define GENERIC_THREAD_HPP

#include <yarp/os/all.h>
#include <drc_shared/yarp_command_interface.hpp>
#include <paramHelp/paramHelperServer.h>
#include <paramHelp/paramProxyBasic.h>
#include <paramHelp/paramProxyInterface.h>


// param helper define for params
#define PARAM_ID_DT 0
#define PARAM_ID_ROBOT 1
#define PARAM_SIZE_DT 1
#define PARAM_SIZE_ROBOT 1

// param helper define for commands
#define COMMAND_ID_HELP 0
#define COMMAND_ID_SAVE_PARAMS 1

/**
 * @brief generic thread
 * 
 * @author Luca Muratore (luca.muratore@iit.it)
 **/
class generic_thread:   public yarp::os::RateThread,
                        public paramHelp::ParamValueObserver,
                        public paramHelp::CommandObserver
{
private:
    
    std::vector<paramHelp::ParamProxyInterface *> create_standard_ph_parameters()
    {
        std::vector<paramHelp::ParamProxyInterface *> standard_ph_parameters;
        // insert dT param
        standard_ph_parameters.push_back( new paramHelp::ParamProxyBasic<double>(   "dT", 
                                                                                    PARAM_ID_DT, 
                                                                                    PARAM_SIZE_DT, 
                                                                                    paramHelp::ParamLowerBound<double>(1e-3), 
                                                                                    paramHelp::PARAM_CONFIG, NULL, 
                                                                                    "control thread period [milliseconds]" ) );
        
        // insert robot name param
        standard_ph_parameters.push_back( new paramHelp::ParamProxyBasic<double>(   "robot", 
                                                                                    PARAM_ID_ROBOT, 
                                                                                    PARAM_SIZE_ROBOT, 
                                                                                    paramHelp::ParamLowerBound<double>(1e-3), 
                                                                                    paramHelp::PARAM_CONFIG, NULL, 
                                                                                    "robot name" ) );
        
        return standard_ph_parameters;
    }
    
    std::vector<paramHelp::CommandDescription> create_standard_ph_commands()
    {
        std::vector<paramHelp::CommandDescription> standard_ph_commands;
        // insert help command
        standard_ph_commands.push_back(paramHelp::CommandDescription(   "help",
                                                                        COMMAND_ID_HELP,
                                                                        "Get instructions about how to communicate with this module") );
        // insert saveParams command
        standard_ph_commands.push_back(paramHelp::CommandDescription(   "saveParams",
                                                                        COMMAND_ID_SAVE_PARAMS,
                                                                        "saveParams(string fileName) # Save the actual configuration parameters to file, inside the sot context folder") );
        return standard_ph_commands;
    }
    
protected:
    
    std::string module_prefix;
    double dT;
    paramHelp::ParamHelperServer *ph;
    yarp::os::ResourceFinder* rf;
    std::string robot;
    yarp::os::Port rpcPort;
    
public: 
    
    /**
     * @brief constructor of the generic thread.
     *
     * @param module_prefix module name.
     * @param thread_period period of the run thread in millisecond.
     * @param rf resource finder.
     **/
    generic_thread( std::string module_prefix, 
                    double thread_period,
                    yarp::os::ResourceFinder* rf) : module_prefix( module_prefix),
                                                    dT( thread_period ),
                                                    rf( rf ),
                                                    RateThread( thread_period )
    {    
        
        // get the data for the param heleper
        std::vector<paramHelp::ParamProxyInterface *> actual_ph_parameters = get_ph_parameters();
        std::vector<paramHelp::CommandDescription> actual_ph_commands = get_ph_commands();
        // switch to standard c const vector
        const paramHelp::ParamProxyInterface * const* ph_parameters =  &actual_ph_parameters[0];
        const paramHelp::CommandDescription* ph_commands =  &actual_ph_commands[0];
        // create the param helper
        ph = new paramHelp::ParamHelperServer( ph_parameters, actual_ph_parameters.size(),
                                               ph_commands , actual_ph_commands.size() );
        // link parameters
        ph_link_parameters();
        
        
    }
    
    std::vector<paramHelp::ParamProxyInterface *> get_ph_parameters()
    {
        // standard params
        std::vector<paramHelp::ParamProxyInterface *> ph_parameters = create_standard_ph_parameters();
        // custom params
        std::vector<paramHelp::ParamProxyInterface *> custom_ph_parameters = custom_get_ph_parameters();
        // concat the two vectors
        ph_parameters.insert(ph_parameters.end(), custom_ph_parameters.begin(), custom_ph_parameters.end() );
    
        return ph_parameters;
    }
    
    virtual std::vector<paramHelp::ParamProxyInterface *> custom_get_ph_parameters()
    {
        std::vector<paramHelp::ParamProxyInterface *> empty_vector;
        return empty_vector;
    }
    
    std::vector<paramHelp::CommandDescription> get_ph_commands()
    {
        // standard params
        std::vector<paramHelp::CommandDescription> ph_commands = create_standard_ph_commands();
        // custom params
        std::vector<paramHelp::CommandDescription> custom_ph_commands = custom_get_ph_commands();
        // concat the two vectors
        ph_commands.insert(ph_commands.end(), custom_ph_commands.begin(), custom_ph_commands.end() );
        
        return ph_commands;
    }
    
    virtual std::vector<paramHelp::CommandDescription> custom_get_ph_commands()
    {
        std::vector<paramHelp::CommandDescription> empty_vector;
        return empty_vector;
    }
    
    void ph_link_parameters() 
    {
        ph->linkParam(PARAM_ID_DT, &dT);
        ph->linkParam(PARAM_ID_ROBOT, &robot);
        custom_ph_link_parameters();
    }
    
    virtual void custom_ph_link_parameters() 
    {
    }
    
    bool threadInit() final
    {
        /*// scheduling priority
        struct sched_param thread_param;
        thread_param.sched_priority = 99;
        pthread_setschedparam(pthread_self(), SCHED_FIFO, &thread_param);*/
        
        // param helper init
        yarp::os::Bottle initMsg;
        ph->initializeParams(*rf, initMsg);
        paramHelp::printBottle(initMsg);
        //open the rpc port for the param helper
        rpcPort.open( ( "/"+ module_prefix +"/rpc" ).c_str() );
        
        // call the init on the param helper
        if( ph->init( module_prefix ) ) {
            // call the custom init on success
            return custom_init();
        }
        else {
            // error on the param helper initialization
            fprintf(stderr, "Error while initializing parameter helper.\n");
            return false;
        }
    }
    
    virtual bool custom_init() 
    {
        return true;
    }
    
    virtual void parameterUpdated(const paramHelp::ParamProxyInterface *pd)
    {
        return;
    }


    virtual void commandReceived(const paramHelp::CommandDescription &cd, const yarp::os::Bottle &params, yarp::os::Bottle &reply)
    {
        switch(cd.id)
        {
        case COMMAND_ID_HELP:
            ph->getHelpMessage(reply);
            break;
        case COMMAND_ID_SAVE_PARAMS:
            {
                /*std::string fileName = CONF_NAME;
                yarp::os::ResourceFinder rf;
                rf.setDefaultContext(MODULE_NAME);
                std::string folderName = rf.getContextPath() + "/";
                std::string confPath = folderName + fileName;
                std::vector<int> configIds;
                for(unsigned int i = 0; i < PARAM_ID_SIZE; ++i)
                    if( sot_VelKinCon_ParamDescr[i]->ioType.value == paramHelp::PARAM_IN_OUT ||
                        sot_VelKinCon_ParamDescr[i]->ioType.value == paramHelp::PARAM_CONFIG )
                        configIds.push_back(i);

                std::cout << "Saving to " << confPath;

                std::stringstream ss;
                boost::posix_time::ptime pt = boost::posix_time::second_clock::local_time();
                boost::posix_time::time_facet* output_facet = new boost::posix_time::time_facet("%Y%m%dT%H%M%S%F%q");
                ss.imbue(std::locale(ss.getloc(), output_facet));
                ss << pt;
                std::string confPathWithTimestamp = confPath + "." + ss.str();

                std::cout << " and " << confPathWithTimestamp;
                reply.addString("saving...");

                if( paramHelper->writeParamsOnFile( confPathWithTimestamp,
                                                    configIds.data(),
                                                    configIds.size())) {
                    if(boost::filesystem::exists(confPath))
                            boost::filesystem::remove(confPath);
                    paramHelper->writeParamsOnFile( confPath,
                                                    configIds.data(),
                                                    configIds.size());
                    reply.addString("ok");
                } else
                    reply.addString("failed!");*/
            }
            break;
        }
    }

        
        
  
};

#endif
