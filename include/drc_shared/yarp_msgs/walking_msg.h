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

#ifndef ENCODERS_MSG
#define ENCODERS_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include <vector>
#include <map>
#include <boost/concept_check.hpp>

union floatToChar
{
    char chars[4];
    float value;
};

union intToChar
{
    char chars[4];
    int32_t value;
};

class CserializeBottle {
    char buffer[500];
    int m_size;
public: 
    CserializeBottle(){
        m_size = 0;
    }
    
    void addChar(char in) {
      buffer[m_size] = in;
      m_size++;
    }
    
    void addBool(bool in) {
      buffer[m_size] = (in == true ? 1 : 0);
      m_size++;
    }
    
    void addDouble(double in) {
        floatToChar a;
        a.value = (float) in;
        buffer[m_size]=a.chars[0];
        m_size++;
        buffer[m_size]=a.chars[1];
        m_size++;
        buffer[m_size]=a.chars[2];
        m_size++;
        buffer[m_size]=a.chars[3];
        m_size++;
    }
    
    void addInt32(int in) {
        intToChar a;
        a.value = (int32_t) in;
        buffer[m_size]=a.chars[0];
        m_size++;
        buffer[m_size]=a.chars[1];
        m_size++;
        buffer[m_size]=a.chars[2];
        m_size++;
        buffer[m_size]=a.chars[3];
        m_size++;
    }
    
    void addVector3d(Eigen::Vector3d in) {
        addDouble(in(0));
        addDouble(in(1));
        addDouble(in(2));
    }
    
    void addVector2d(Eigen::Vector2d in) {
        addDouble(in(0));
        addDouble(in(1));
    }
    
    yarp::os::Bottle getBottle(){
        yarp::os::Bottle tmpBottle;
        yarp::os::Value a(buffer,m_size);
        tmpBottle.add(a);
        return tmpBottle;
    };
    
    void clear(){
	m_size=0;
    }
};


class CdeSerializeBottle {
//     yarp::os::Bottle m_bottle;
    char m_buffer[500];
    int m_index;
    int m_size;
    bool isReady;
public: 
    CdeSerializeBottle(){
        m_index = 0;
        m_size = 0;
        isReady = false;
    }
    
    bool setBottle(yarp::os::Bottle *bottle) 
    {
        
       //Copy data from bottle to char buffer
        int getter=0;
        if (bottle->get(getter).isNull())
        {
            isReady = false;
            return isReady;
        }
        m_size = bottle->get(getter).asBlobLength();
        if (m_size == 0) {
            isReady = false;
            return isReady;
        }

        
        const char* source = bottle->get(getter).asBlob();getter++;
        for (int i=0;i<m_size;i++)
        {
            m_buffer[i]=source[i];
        }
        isReady = true;
        return isReady;
    }
    
    char getChar() {
      char tmp = m_buffer[m_index];
      m_index++;
      return tmp;
    }
    
    bool getBool() {
      bool out = (m_buffer[m_index] == 0 ? false : true);
      m_index++;
      return out;
    }
    
    double getDouble() {
        floatToChar a;
        a.chars[0] = m_buffer[m_index];
        m_index++;
        a.chars[1] = m_buffer[m_index];
        m_index++;
        a.chars[2] = m_buffer[m_index];
        m_index++;
        a.chars[3] = m_buffer[m_index];
        m_index++;
        return (double) a.value;
    }
    
    int getInt() {
        intToChar a;
        a.chars[0] = m_buffer[m_index];
        m_index++;
        a.chars[1] = m_buffer[m_index];
        m_index++;
        a.chars[2] = m_buffer[m_index];
        m_index++;
        a.chars[3] = m_buffer[m_index];
        m_index++;
        return (int) a.value;
    }   
    
    Eigen::Vector3d getVector3d() {
        Eigen::Vector3d tmp;
        tmp(0) =  getDouble();
        tmp(1) =  getDouble();
        tmp(2) =  getDouble();
        return tmp;        
    }   
    
    Eigen::Vector2d getVector2d() {
        Eigen::Vector2d tmp;
        tmp(0) =  getDouble();
        tmp(1) =  getDouble();
        return tmp;        
    }
    
  
};


class walking_msg
{
  CserializeBottle serialize;
  CdeSerializeBottle deserialize;
  
public:
  unsigned char command;
  std::map<std::string, int> number_param_map;
  
  walking_msg()
    {
      command = 0;

      number_param_map["stepZmpShiftL"]=2;
      number_param_map["stepZmpShiftR"]=3;
      number_param_map["firstStepZmpShiftL"]=4;
      number_param_map["firstStepZmpShiftR"]=5;
      number_param_map["lastStepZmpShiftL"]=6;
      number_param_map["lastStepZmpShiftR"]=7;
      number_param_map["maxFootDiffAngle"]=8;
      number_param_map["stepWidth"]=9;
      number_param_map["stepLength"]=10;
      number_param_map["stepTime"]=11;
      number_param_map["doubleSupportTime"]=12;
      number_param_map["comDownShift"]=13;
      number_param_map["comHeightFiltLpfSamples"]=14;
      number_param_map["earlyFootStopHeight"]=15;
      number_param_map["comCtrl_isEnabled"]=16;
      number_param_map["comOnlyCtrl_isEnabled"]=17;
      number_param_map["tCtrl_isEnabled"]=18;
      number_param_map["footFTCtrl_isEnabled"]=19;
      number_param_map["footZMPCtrl_isEnabled"]=20;
      number_param_map["footZMPCtrl_isPitchEnabled"]=21;
      number_param_map["footZMPCtrl_isRollEnabled"]=22;
      number_param_map["footReflex_isEnabled"]=23;
      number_param_map["earlyGCctrl_isEnabled"]=24;
    }
    
    
    //Task space references
    Eigen::VectorXd pelvis;
    Eigen::VectorXd lAnkle;
    Eigen::VectorXd rAnkle;
    
    //Estimates and references
    Eigen::Vector2d zmp_ref;
    Eigen::Vector2d zmp_meas;
    Eigen::Vector2d com_ref;
    Eigen::Vector2d com_meas;
    
    //ZMP shifts
    Eigen::Vector3d     stepZmpShiftL;
    Eigen::Vector3d     stepZmpShiftR;
    Eigen::Vector3d     firstStepZmpShiftL;
    Eigen::Vector3d     firstStepZmpShiftR;
    Eigen::Vector3d     lastStepZmpShiftL;
    Eigen::Vector3d     lastStepZmpShiftR;    
    
    //Internal walking parameters    
    double  maxFootDiffAngle;
    double  stepWidth;
    double  stepLength;
    double  stepTime;   
    double  doubleSupportTime;  
    double  comDownShift;
    int     comHeightFiltLpfSamples;
    double  earlyFootStopHeight;    
    
    //Bools
    bool  comCtrl_isEnabled;   
    bool  comOnlyCtrl_isEnabled;
    bool  tCtrl_isEnabled;
    bool  footFTCtrl_isEnabled;
    bool  footZMPCtrl_isEnabled;
    bool  footZMPCtrl_isPitchEnabled;
    bool  footZMPCtrl_isRollEnabled;
    bool  footReflex_isEnabled;
    bool  earlyGCctrl_isEnabled;
    
    yarp::os::Bottle toBottle()
    {
        serialize.clear();
        serialize.addChar(command);
        switch(command) {
          
          // ------------------------ task space references -------------------
        
          case 0: {//Last task space references
              serialize.addVector3d(pelvis.segment(0,3));
              serialize.addVector3d(pelvis.segment(3,3));
              serialize.addVector3d(lAnkle.segment(0,3));
              serialize.addVector3d(lAnkle.segment(3,3));
              serialize.addVector3d(rAnkle.segment(0,3));
              serialize.addVector3d(rAnkle.segment(3,3));
          
          } break;
          
          // ------------------------ estimates and references -------------------
          
          case 1: {//Estimates and last references
              serialize.addVector2d(zmp_ref );
              serialize.addVector2d(zmp_meas);
              serialize.addVector2d(com_ref );
              serialize.addVector2d(com_meas);
          } break;
          
          // ------------------------ ZMP shifts -------------------
                    
          case 2: {//stepZmpShiftL
              serialize.addVector3d(stepZmpShiftL);
          } break;
            
          case 3: {//stepZmpShiftR
              serialize.addVector3d(stepZmpShiftR);
          } break;
          
          case 4: {//firstStepZmpShiftL
              serialize.addVector3d(firstStepZmpShiftL);
          } break;
          
          case 5: {//firstStepZmpShiftR
              serialize.addVector3d(firstStepZmpShiftR);
          } break;
          
          case 6: {//lastStepZmpShiftL
              serialize.addVector3d(lastStepZmpShiftL);
          } break;
          
          case 7: {//lastStepZmpShiftR
              serialize.addVector3d(lastStepZmpShiftR);
          } break;
          
          
          // ------------------------ doubles and ints  -------------------
          
          case 8: {//maxFootDiffAngle
              serialize.addDouble(maxFootDiffAngle);
          } break;
          
          case 9: {//stepWidth
              serialize.addDouble(stepWidth);
          } break;
          
          case 10: {//stepLength
              serialize.addDouble(stepLength);
          } break;
          
          case 11: {//stepTime
              serialize.addDouble(stepTime);
          } break;
          
          case 12: {//doubleSupporcomDownShifttTime
              serialize.addDouble(doubleSupportTime);
          } break;
          
          case 13: {//comDownShift
              serialize.addDouble(comDownShift);
          } break;
          
          case 14: {//comHeightFiltLpfSamples
              serialize.addInt32(comHeightFiltLpfSamples);
          } break;
          
          case 15: {//earlyFootStopHeight
              serialize.addDouble(earlyFootStopHeight);
          } break;
          
          
          // ------------------------ bools -------------------
          
          case 16: {//comCtrl_isEnabled
              serialize.addBool(comCtrl_isEnabled);
          } break;
          
          case 17: {//comOnlyCtrl_isEnabled
              serialize.addBool(comOnlyCtrl_isEnabled);
          } break;
          
          case 18: {//tCtrl_isEnabled
              serialize.addBool(tCtrl_isEnabled);
          } break;
          
          case 19: {//footFTCtrl_isEnabled
              serialize.addBool(footFTCtrl_isEnabled);
          } break;
          
          case 20: {//footZMPCtrl_isEnabled
              serialize.addBool(footZMPCtrl_isEnabled);
          } break;
          
          case 21: {//footZMPCtrl_isPitchEnabled
              serialize.addBool(footZMPCtrl_isPitchEnabled);
          } break;
          
          case 22: {//footZMPCtrl_isRollEnabled
              serialize.addBool(footZMPCtrl_isRollEnabled);
          } break;
          
          case 23: {//footReflex_isEnabled
              serialize.addBool(footReflex_isEnabled);
          } break;
          
          case 24: {//earlyGCctrl_isEnabled
              serialize.addBool(earlyGCctrl_isEnabled);
          } break;
          
          case 200: {//sendAllParameters
              serialize.addVector3d(stepZmpShiftL);
              serialize.addVector3d(stepZmpShiftR);
              serialize.addVector3d(firstStepZmpShiftL);
              serialize.addVector3d(firstStepZmpShiftR);
              serialize.addVector3d(lastStepZmpShiftL);
              serialize.addVector3d(lastStepZmpShiftR);
              serialize.addDouble(maxFootDiffAngle);
              serialize.addDouble(stepWidth);
              serialize.addDouble(stepLength);
              serialize.addDouble(stepTime);
              serialize.addDouble(doubleSupportTime);
              serialize.addDouble(comDownShift);
              serialize.addInt32(comHeightFiltLpfSamples);
              serialize.addDouble(earlyFootStopHeight);
              serialize.addBool(comCtrl_isEnabled);
              serialize.addBool(comOnlyCtrl_isEnabled);
              serialize.addBool(tCtrl_isEnabled);
              serialize.addBool(footFTCtrl_isEnabled);
              serialize.addBool(footZMPCtrl_isEnabled);
              serialize.addBool(footZMPCtrl_isPitchEnabled);
              serialize.addBool(footZMPCtrl_isRollEnabled);
              serialize.addBool(footReflex_isEnabled);
              serialize.addBool(earlyGCctrl_isEnabled);
            } break;
        }
        return serialize.getBottle();
    }

    void fromBottle(yarp::os::Bottle* temp)
    {
        if (!deserialize.setBottle(temp)) {
            return;
        }
        command = deserialize.getChar();
        switch(command) {        
          
          // ------------------------ task space references -------------------
          
          case 0: {//Last task space references
              pelvis.segment(0,3) = deserialize.getVector3d();
              pelvis.segment(3,3) = deserialize.getVector3d();
              lAnkle.segment(0,3)  = deserialize.getVector3d();
              lAnkle.segment(3,3)  = deserialize.getVector3d();
              rAnkle.segment(0,3)  = deserialize.getVector3d();
              rAnkle.segment(3,3)  = deserialize.getVector3d();
          } break;
          
          // ------------------------ estimates and references -------------------
          
          case 1: {//Estimates and last references
              zmp_ref  = deserialize.getVector2d();
              zmp_meas = deserialize.getVector2d();
              com_ref  = deserialize.getVector2d();
              com_meas = deserialize.getVector2d();
          
          } break;
          
          
          // ------------------------ ZMP shifts -------------------
          
          case 2: {//stepZmpShiftL
              stepZmpShiftL = deserialize.getVector3d();
          } break;
            
          case 3: {//stepZmpShiftR
              stepZmpShiftR = deserialize.getVector3d();
          } break;
          
          case 4: {//firstStepZmpShiftL
              firstStepZmpShiftL = deserialize.getVector3d();
          } break;
          
          case 5: {//firstStepZmpShiftR
              firstStepZmpShiftR = deserialize.getVector3d();
          } break;
          
          case 6: {//lastStepZmpShiftL
              lastStepZmpShiftL = deserialize.getVector3d();
          } break;
          
          case 7: {//lastStepZmpShiftR
              lastStepZmpShiftR = deserialize.getVector3d();
          } break;
          
          
          // ------------------------ doubles and ints  -------------------
          
          case 8: {//maxFootDiffAngle
              maxFootDiffAngle = deserialize.getDouble();
          } break;
          
          case 9: {//stepWidth
              stepWidth = deserialize.getDouble();
          } break;
          
          case 10: {//stepLength
              stepLength = deserialize.getDouble();
          } break;
          
          case 11: {//stepTime
              stepTime = deserialize.getDouble();
          } break;
          
          case 12: {//doubleSupportTime
              doubleSupportTime = deserialize.getDouble();
          } break;
          
          case 13: {//comDownShift
              comDownShift = deserialize.getDouble();
          } break;
          
          case 14: {//comHeightFiltLpfSamples
              comHeightFiltLpfSamples = deserialize.getInt();
          } break;
          
          case 15: {//earlyFootStopHeight
              earlyFootStopHeight = deserialize.getDouble();
          } break;
         
          
          // ------------------------ bools -------------------
          
          case 16: {//comCtrl_isEnabled
              comCtrl_isEnabled = deserialize.getBool();
          } break;
          
          case 17: {//comOnlyCtrl_isEnabled
              comOnlyCtrl_isEnabled = deserialize.getBool();
          } break;
          
          case 18: {//tCtrl_isEnabled
              tCtrl_isEnabled = deserialize.getBool();
          } break;
          
          case 19: {//footFTCtrl_isEnabled
              footFTCtrl_isEnabled = deserialize.getBool();
          } break;
          
          case 20: {//footZMPCtrl_isEnabled
            footZMPCtrl_isEnabled = deserialize.getBool();
          } break;
          
          case 21: {//footZMPCtrl_isPitchEnabled
              footZMPCtrl_isPitchEnabled = deserialize.getBool();
          } break;
          
          case 22: {//footZMPCtrl_isRollEnabled
              footZMPCtrl_isRollEnabled = deserialize.getBool();
          } break;
          
          case 23: {//footReflex_isEnabled
              footReflex_isEnabled = deserialize.getBool();
          } break;
          
          case 24: {//earlyGCctrl_isEnabled
              earlyGCctrl_isEnabled = deserialize.getBool();
          } break;
          
          
          case 200: {//sendAllParameters
              stepZmpShiftL = deserialize.getVector3d();
              stepZmpShiftR = deserialize.getVector3d();
              firstStepZmpShiftL = deserialize.getVector3d();
              firstStepZmpShiftR = deserialize.getVector3d();
              lastStepZmpShiftL = deserialize.getVector3d();
              lastStepZmpShiftR = deserialize.getVector3d();
              maxFootDiffAngle = deserialize.getDouble();
              stepWidth = deserialize.getDouble();
              stepLength = deserialize.getDouble();
              stepTime = deserialize.getDouble();
              doubleSupportTime = deserialize.getDouble();
              comDownShift = deserialize.getDouble();
              comHeightFiltLpfSamples = deserialize.getInt();
              earlyFootStopHeight = deserialize.getDouble();
              comCtrl_isEnabled = deserialize.getBool();
              comOnlyCtrl_isEnabled = deserialize.getBool();
              tCtrl_isEnabled = deserialize.getBool();
              footFTCtrl_isEnabled = deserialize.getBool();
              footZMPCtrl_isEnabled = deserialize.getBool();
              footZMPCtrl_isPitchEnabled = deserialize.getBool();
              footZMPCtrl_isRollEnabled = deserialize.getBool();
              footReflex_isEnabled = deserialize.getBool();
              earlyGCctrl_isEnabled = deserialize.getBool();
           } break;

        }
        return;
    }

};

#endif // ENCODERS_MSG
