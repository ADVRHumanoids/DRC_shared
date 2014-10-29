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
    double x;
    double y;
};

class region
{
public:
    point_2d start;
    point_2d end;
};

class fs_perception_msg
{
public:
    std::string command;
    
    double image_fps;
    
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
	    list.addDouble(image_fps);
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
	    image_fps = list->get(2).asDouble();
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

#endif // FS_PLANNER_MSG