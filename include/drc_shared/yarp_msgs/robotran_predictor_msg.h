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

#ifndef ROBOTRAN_PREDICTOR_MSG
#define ROBOTRAN_PREDICTOR_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/LogStream.h>

#define STATE_INPUT_NUM 10

namespace robotran_predictor {
    class state_input;
    class request;
    class prediction;
}


class robotran_predictor::state_input // NOTE single joint! TBD do an array
{
public:
  
    float        link_pos;           // rad         
    float        motor_pos;          // rad
    float        link_vel;           // rad TBD on the firmware
    int16_t      motor_vel;          // rad/s
    int16_t      torque;             // Nm
    uint16_t     max_temperature;    // C
    uint16_t     fault;
    uint16_t     rtt;                // us
    uint16_t     op_idx_ack;         // op [ack/nack] , idx
    float        aux; 
        
    state_input()
    {
        link_pos = 0.0;
        motor_pos = 0.0;
        link_vel = 0.0;
        motor_vel = 0;
        torque = 0;
        max_temperature = 0;
        fault = 255;
        rtt = 0;
        op_idx_ack = 0;
        aux = 0.0;
    }
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle b;
        
        b.addDouble(link_pos);
        b.addDouble(motor_pos);
        b.addDouble(link_vel);
        b.addInt(motor_vel);
        b.addInt(torque);
        b.addInt(max_temperature);
        b.addInt(fault);
        b.addInt(rtt);
        b.addInt(op_idx_ack);
        b.addDouble(aux);

        return b;
    }

    void fromBottle(yarp::os::Bottle* b)
    {
        if(b->size() != STATE_INPUT_NUM){
            return;
        }
        
        link_pos = (float) b->get(0).asDouble();
        motor_pos = (float) b->get(1).asDouble();
        link_vel = (float) b->get(2).asDouble();
        motor_vel = (int16_t) b->get(3).asInt();
        torque = (int16_t) b->get(4).asInt();
        max_temperature = (uint16_t) b->get(5).asInt();
        fault = (uint16_t) b->get(6).asInt();
        rtt = (uint16_t) b->get(7).asInt();
        op_idx_ack = (uint16_t) b->get(8).asInt();
        aux = (float) b->get(9).asDouble();
        
        return;
    }
    
    void print()
    {
        yInfo("%f, %f, %f, %d, %d, %d, %d, %d, %d, %f", 
              link_pos, motor_pos, link_vel, 
              motor_vel, torque, max_temperature, 
              fault, rtt, op_idx_ack, aux);
    }
};

class robotran_predictor::request
{
public:
    std::string cmd = "";
    float prediction_time;
    bool process_request;
    
    request()
    {
    }
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle b;
        b.addString(cmd);
        b.addDouble(prediction_time);
        b.addInt(process_request);
        return b;
    }
    
    void fromBottle(yarp::os::Bottle* b)
    {
        cmd = b->get(0).asString();
        prediction_time = (float) b->get(1).asDouble();
        process_request = (bool) b->get(2).asInt();
    }
    
};

class robotran_predictor::prediction
{
public:
    std::string out_name;
    
    // TBD add what you need
    double left_knee_angle; // NOTE example!
    
    bool is_valid;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle b;
        b.addString(out_name);
        b.addDouble(left_knee_angle);
        b.addInt(is_valid);
        return b;
    }
    
    void fromBottle(yarp::os::Bottle* b)
    {
        out_name = b->get(0).asString();
        left_knee_angle = (float) b->get(1).asDouble();
        is_valid = (bool) b->get(2).asInt();
    }
};


#endif // ROBOTRAN_PREDICTOR_MSG