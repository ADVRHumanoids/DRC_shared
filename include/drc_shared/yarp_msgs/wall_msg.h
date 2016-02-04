/* Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015-2016, Dimitrios Kanoulas
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the copyright holder(s) nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WALL_MSG
#define WALL_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class wall_msg
{
  /** \brief The wall message object represents the pose of a wall surface
    * (rotation, translation).
    *
    * \author Dimitrios Kanoulas
    */
  public:
    /** \brief Constructor with the default values. */
    wall_msg ()
    {
      command = "";
      frame = "";
      wall_data.p.x (0.0);
      wall_data.p.y (0.0);
      wall_data.p.z (0.0);
      wall_data.M = KDL::Rotation::Identity();
    }

    /** \brief YARP message exchange toBottle method. */
    yarp::os::Bottle toBottle ()
    {
      yarp::os::Bottle temp;
      yarp::os::Bottle& list= temp.addList ();

      list.addString (command);

      if (command == "walldatasent")
      {
        list.addString (frame);
        list.add (yarp_KDL::getBlob (wall_data));
      }

      return temp;
    }

    /** \brief YARP message exchange fromBottle method. */
    void fromBottle (yarp::os::Bottle* temp)
    {
      if (temp->get(0).isNull())
      {
        command = "";
        return;
      }

      yarp::os::Bottle* list = temp->get(0).asList();
      if (list==NULL)
      {
        command = "";
        return;
      }
      if (list->get(0).isNull())
      {
        command = "";
        return;
      }

      command = list->get(0).asString();

      int index = 1;
      if (command == "walldatasent")
      {
        frame = list->get(index++).asString();
        if (list->get(index).asBlobLength() != 0)
        {
          wall_data = yarp_KDL::fromBlob (list->get(index++));
        }
        else
        {
          wall_data.p.x (list->get(index++).asDouble());
          wall_data.p.y (list->get(index++).asDouble());
          wall_data.p.z (list->get(index++).asDouble());
          double qx,qy,qz,qw;
          qx = list->get(index++).asDouble();
          qy = list->get(index++).asDouble();
          qz = list->get(index++).asDouble();
          qw = list->get(index++).asDouble();
          wall_data.M = KDL::Rotation::Quaternion (qx,qy,qz,qw);
        }
      }

      return;
    }

  public:
    /** \brief The command name. */
    std::string command;

    /** \brief The fixed frame of the data. */
    std::string frame;

    /** \brief The Wall data frame (translation, rotation). */
    KDL::Frame wall_data;
};

#endif // WALL_MSG
