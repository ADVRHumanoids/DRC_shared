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

#ifndef KDL_FRAME_MSG
#define KDL_FRAME_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>

namespace yarp_KDL
{
    struct float_frame
    {
        float px,py,pz;
        float rx,ry,rz,rw;
    };

    //IF YOU HAVE A PC WHERE FLOATS ARE NOT 32 BITS, GO **** YOURSELF
    union frame_as_char
    {
        float_frame frame; 
        char chars[28];
    };

    static yarp::os::Value getBlob(KDL::Frame input)
    {
        frame_as_char buffer;
        buffer.frame.px=(float)input.p.x();
        buffer.frame.py=(float)input.p.y();
        buffer.frame.pz=(float)input.p.z();
        double rx,ry,rz,rw;
        input.M.GetQuaternion(rx,ry,rz,rw);
        buffer.frame.rx=(float)rx;
        buffer.frame.ry=(float)ry;
        buffer.frame.rz=(float)rz;
        buffer.frame.rw=(float)rw;
        yarp::os::Value a(buffer.chars,28);
        return a;
    }

    static KDL::Frame fromBlob(const yarp::os::Value& input)
    {
        int size = input.asBlobLength();
        if (size!=28) 
        {
            std::cout<<"AAAAAAAAAAAAAAAAAAAAAAA bad blob (kdl_frame_msg)!!"<<std::endl;
            return KDL::Frame();
        }
        frame_as_char buffer;
        const char* source = input.asBlob();
        for (int i=0;i<size;i++)
        {
            buffer.chars[i]=source[i];
        }
        KDL::Frame output;
        output.p.x(buffer.frame.px);
        output.p.y(buffer.frame.py);
        output.p.z(buffer.frame.pz);
        double rx,ry,rz,rw;
        rx=buffer.frame.rx;
        ry=buffer.frame.ry;
        rz=buffer.frame.rz;
        rw=buffer.frame.rw;
        output.M=KDL::Rotation::Quaternion(rx,ry,rz,rw);
        
        return output;
    }
}


class kdl_frame_msg
{
public:
    kdl_frame_msg(KDL::Frame frame)
    {
        this->frame=frame;
    }

    KDL::Frame frame;
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        temp.add(yarp_KDL::getBlob(frame));
        return temp;
    }

    void fromBottle(yarp::os::Bottle* temp)
    {
        int getter=0;
        if (temp->get(getter).isNull())
        {
            return;
        }
        if (temp->get(getter).asBlobLength()==0) return;
        frame = yarp_KDL::fromBlob(temp->get(getter));
        return;
    }
};

#endif // KDL_FRAME_MSG