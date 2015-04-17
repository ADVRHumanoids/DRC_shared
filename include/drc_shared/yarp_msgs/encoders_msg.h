#ifndef ENCODERS_MSG
#define ENCODERS_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include <vector>
#include <boost/concept_check.hpp>

union encoder_to_int
{
    char chars[2];
    int16_t enc;
};


class encoder_msg
{
private:
public:
    std::vector<double> encoders;

    encoder_msg()
    {
    }

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
//         temp.addInt(encoders.size());
        char buffer[300];
        int size=0;
        for (int i=0;i<encoders.size();i++)
        {
            encoder_to_int a;
            a.enc=round(encoders[i]*50.0);
            buffer[size]=a.chars[0];
            size++;
            buffer[size]=a.chars[1];
            size++;
        }
        yarp::os::Value a(buffer,size);
        temp.add(a);
        return temp;
    }
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        int getter=0;
        if (temp->get(getter).isNull())
        {
            return;
        }
//         int size = temp->get(getter).asInt(); getter++;
//         assert(size*2==temp->get(getter).asBlobLength());
        int size = temp->get(getter).asBlobLength();
        if (size==0) return;
        char buffer[300];
        const char* source = temp->get(getter).asBlob();getter++;
        for (int i=0;i<size;i++)
        {
            buffer[i]=source[i];
        }
        int count = 0;
        for (int i=0;i<size;i=i+2)
        {
            encoder_to_int enc;
            enc.chars[0]=buffer[count];
            count++;
            enc.chars[1]=buffer[count];
            count++;
            encoders.push_back(enc.enc/50.0);
        }

        return;
    }

};

#endif // ENCODERS_MSG