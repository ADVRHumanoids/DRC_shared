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

#define STATE_INPUT_NUM 11

namespace robotran_predictor {
    class state_input;
    class request;
    class prediction;
}


class robotran_predictor::state_input // NOTE single joint! TBD do an array
{
public:
      
    int joint_num = 0;
        
    yarp::sig::Vector        link_pos;           // rad         
    yarp::sig::Vector        motor_pos;          // rad
    yarp::sig::Vector        link_vel;           // rad TBD on the firmware
    yarp::sig::Vector        motor_vel;          // rad/s
    yarp::sig::Vector        torque;             // Nm
    yarp::sig::Vector        pos_ref;            // rad 
    yarp::sig::VectorOf<uint16_t>     max_temperature;    // C
    yarp::sig::VectorOf<uint16_t>     fault;
    yarp::sig::VectorOf<uint16_t>     rtt;                // us
    yarp::sig::VectorOf<uint16_t>     op_idx_ack;         // op [ack/nack] , idx
    yarp::sig::VectorOf<float>        aux; 
    
    state_input()
    {
    }
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle b;
        
        b.addInt(joint_num);
        
        for(int i = 0; i < joint_num; i++) {
            b.addDouble(link_pos[i]);
            b.addDouble(motor_pos[i]);
            b.addDouble(link_vel[i]);
            b.addInt(motor_vel[i]);
            b.addInt(torque[i]);
            b.addDouble(pos_ref[i]);
            b.addInt(max_temperature[i]);
            b.addInt(fault[i]);
            b.addInt(rtt[i]);
            b.addInt(op_idx_ack[i]);
            b.addDouble(aux[i]);
        }

        return b;
    }

    void fromBottle(yarp::os::Bottle* b)
    {
        joint_num = b->get(0).asInt();
        if(b->size() != (STATE_INPUT_NUM*joint_num + 1)){
            return;
        }
        
        link_pos.resize(joint_num, 0.0);
        motor_pos.resize(joint_num, 0.0);
        link_vel.resize(joint_num, 0.0);
        motor_vel.resize(joint_num, 0.0);
        torque.resize(joint_num, 0.0);
        pos_ref.resize(joint_num, 0.0);
        max_temperature.resize(joint_num, 0);
        fault.resize(joint_num, 0);
        rtt.resize(joint_num, 0);
        op_idx_ack.resize(joint_num, 0);
        aux.resize(joint_num, 0.0);
        
        for(int i = 1,j = 0; i < STATE_INPUT_NUM*joint_num + 1; j++) {
            link_pos[j] = (float) b->get(i++).asDouble();
            motor_pos[j] = (float) b->get(i++).asDouble();
            link_vel[j] = (float) b->get(i++).asDouble();
            motor_vel[j] = (int16_t) b->get(i++).asInt();
            torque[j] = (int16_t) b->get(i++).asInt();
            pos_ref[j] = (float) b->get(i++).asDouble();
            max_temperature[j] = (uint16_t) b->get(i++).asInt();
            fault[j] = (uint16_t) b->get(i++).asInt();
            rtt[j] = (uint16_t) b->get(i++).asInt();
            op_idx_ack[j] = (uint16_t) b->get(i++).asInt();
            aux[j] = (float) b->get(i++).asDouble();
        }
        
        return;
    }
    
    void print()
    {
        for(int i = 0; i < joint_num; i++) {
            yInfo("%d, %d, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d, %f", 
                joint_num, i, link_pos[i], motor_pos[i], link_vel[i], 
                motor_vel[i], torque[i], pos_ref[i], max_temperature[i], 
                fault[i], rtt[i], op_idx_ack[i], aux[i]);
        }
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
