#ifndef TRJ_GENERATOR_MSG
#define TRJ_GENERATOR_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <kdl_parser/kdl_parser.hpp>
class trj_generator_input_msg
{
public:
    std::string command;
    double time;
    KDL::Frame start;
    KDL::Frame displacement;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	if(command=="line")
	{
	    list.addDouble(time);
	    list.addDouble(start.p.x());
	    list.addDouble(start.p.y());
	    list.addDouble(start.p.z());
	    double ro,pi,ya;
	    start.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	    
	    list.addDouble(displacement.p.x());
	    list.addDouble(displacement.p.y());
	    list.addDouble(displacement.p.z());
	    displacement.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	}
	if (command=="circle")
        {
            list.addString("TODO");
        }
        return temp;
    }
    
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            command="";
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            command="";
            return;
        }
        if (list->get(0).isNull())
        {
            command="";
            return;
        }
        
	command = list->get(0).asString();

	if(command=="line")
	{
	    time = list->get(1).asDouble();
	  
	    start.p.x(list->get(2).asDouble());
	    start.p.y(list->get(3).asDouble());
	    start.p.z(list->get(4).asDouble());
	    double ro,pi,ya;
	    ro = list->get(5).asDouble();
	    pi = list->get(6).asDouble();
	    ya = list->get(7).asDouble();
	    start.M.RPY(ro,pi,ya);
	    
	    displacement.p.x(list->get(8).asDouble());
	    displacement.p.y(list->get(9).asDouble());
	    displacement.p.z(list->get(10).asDouble());
	    ro = list->get(11).asDouble();
	    pi = list->get(12).asDouble();
	    ya = list->get(13).asDouble();
	    displacement.M.RPY(ro,pi,ya);
	}
	
	if(command=="circle")
	{
	    //TODO
	    time = 1;
	  
	    start.p.Zero();
	    start.M.Identity();
	    
	    displacement.p.Zero();
	    displacement.M.Identity();
	}
	
	return;
    }
  
};


class trj_generator_output_msg
{
public:
    std::string command;
    std::map<double,KDL::Frame> trj;
    
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);
	if(command=="result_trj")
	{
	    for (std::map<double,KDL::Frame>::iterator it=trj.begin(); it!=trj.end(); ++it)
	    {
	    list.addDouble(it->first);
	    list.addDouble(it->second.p.x());
	    list.addDouble(it->second.p.y());
	    list.addDouble(it->second.p.z());
	    double ro,pi,ya;
	    it->second.M.GetRPY(ro,pi,ya);
	    list.addDouble(ro);
	    list.addDouble(pi);
	    list.addDouble(ya);
	    }
	}

        return temp;
    }
    
    
    void fromBottle(yarp::os::Bottle* temp)
    {
        if (temp->get(0).isNull())
        {
            command="";
            return;
        }
        yarp::os::Bottle* list = temp->get(0).asList();
        if (list==NULL)
        {
            command="";
            return;
        }
        if (list->get(0).isNull())
        {
            command="";
            return;
        }
        
	command = list->get(0).asString();

	if(command=="result_trj")
	{
	    int i=1;
	    while(!list->get(i).isNull())
	    {
		double time = list->get(i++).asDouble();
	      
		KDL::Frame frame;
		
		frame.p.x(list->get(i++).asDouble());
		frame.p.y(list->get(i++).asDouble());
		frame.p.z(list->get(i++).asDouble());
		double ro,pi,ya;
		ro = list->get(i++).asDouble();
		pi = list->get(i++).asDouble();
		ya = list->get(i++).asDouble();
		frame.M.RPY(ro,pi,ya);
		
		trj[time]=frame;
	    }
	}
	
	return;
    }
  
};

#endif // TRJ_GENERATOR_MSG