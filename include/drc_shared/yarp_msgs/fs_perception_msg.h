#ifndef FS_PERCEPTION_MSG
#define FS_PERCEPTION_MSG

#include <string>
#include <yarp/os/Portable.h>

#include <yarp/os/Bottle.h>
#include <boost/concept_check.hpp>
#include <kdl/frames.hpp>

class point_2d
{
public:
    point_2d(double x_=0.0, double y_=0.0){x=x_;y=y_;}
  
    double x;
    double y;
};

class region
{
public:
    region():start(0.0,0.0),end(1.0,1.0){}
    
    point_2d start;
    point_2d end;
};


class generic_perception_msg
{
public:
    generic_perception_msg()
    {
	command="";
	image_quality=0.0;
	left_image=true;
	point_option="";
    }
  
    std::string command;
    
    double image_quality;
    
    std::string point_option;
    bool left_image;
    
    point_2d point;
    region rectangle;

    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();

	list.addString(command);

	if(command=="send_image")
	{
	    list.addInt(left_image);
	    list.addDouble(image_quality);
	}
	if(command=="focus_on_region")
	{
	    list.addDouble(rectangle.start.x);
	    list.addDouble(rectangle.start.y);
	    list.addDouble(rectangle.end.x);
	    list.addDouble(rectangle.end.y);
	}
	if(command=="focus_on_point")
	{
	    list.addDouble(point.x);
	    list.addDouble(point.y);
	    list.addString(point_option);
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

	if(command=="send_image")
	{
	    left_image = list->get(1).asInt();
	    image_quality = list->get(2).asDouble();
	}
	if(command=="focus_on_region")
	{    
	    rectangle.start.x = list->get(1).asDouble();
	    rectangle.start.y = list->get(2).asDouble();
	    rectangle.end.x = list->get(3).asDouble();
	    rectangle.end.y = list->get(4).asDouble();
	}
	if(command=="focus_on_point")
	{
	    point.x = list->get(1).asDouble();
	    point.y = list->get(2).asDouble();
	    point_option = list->get(3).asString();
	}
	return;
    }
  
};


class fs_perception_msg
{
public:
    fs_perception_msg()
    {
    }
    
    std::string command;
  
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
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

	return;
    }
  
};

#endif // FS_PLANNER_MSG