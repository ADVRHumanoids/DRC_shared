/* Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016-, Dimitrios Kanoulas
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

#ifndef COM_MSG
#define COM_MSG

#include <string>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <kdl/frames.hpp>
#include "drc_shared/yarp_msgs/KDL_frame_msg.h"

class com_msg
{
  /** \brief The Center-of-Mass message object represents an object's grasp
    * pose including the CoM pose (rotation, translation), along with its
    * legth and side limits.
    *
    * \author Dimitrios Kanoulas
    */
  public:
    /** \brief Constructor with the default values. */
    com_msg ()
    {
      command = "";
      frame = "";
      com_data.p.x (0.0);
      com_data.p.y (0.0);
      com_data.p.z (0.0);
      com_data.M = KDL::Rotation::Identity();
      handle_length = 0.0;
      left_dist_to_com = 0.0;
    }

    /** \brief YARP message exchange toBottle method. */
    yarp::os::Bottle toBottle ()
    {
      yarp::os::Bottle temp;
      yarp::os::Bottle& list= temp.addList ();

      list.addString (command);

      if (command == "comdatasent")
      {
        list.addString (frame);
        list.add (yarp_KDL::getBlob (com_data));
        list.addDouble (handle_length);
        list.addDouble (left_dist_to_com);
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
      if (command == "comdatasent")
      {
        frame = list->get(index++).asString();
        if (list->get(index).asBlobLength() != 0)
        {
          com_data = yarp_KDL::fromBlob (list->get(index++));
        }
        else
        {
          com_data.p.x (list->get(index++).asDouble());
          com_data.p.y (list->get(index++).asDouble());
          com_data.p.z (list->get(index++).asDouble());
          double qx,qy,qz,qw;
          qx = list->get(index++).asDouble();
          qy = list->get(index++).asDouble();
          qz = list->get(index++).asDouble();
          qw = list->get(index++).asDouble();
          com_data.M = KDL::Rotation::Quaternion (qx,qy,qz,qw);
        }

        handle_length = list->get(index++).asDouble();
        left_dist_to_com = list->get(index++).asDouble();
      }

      return;
    }

  public:
    /** \brief The command name. */
    std::string command;

    /** \brief The fixed frame of the data. */
    std::string frame;

    /** \brief The CoM data frame (translation, rotation). */
    KDL::Frame com_data;

    /** \brief The total length of the object (assuming a straight handle). */
    double handle_length;

    /** \brief Distance from the CoM to the left part of the object. */
    double left_dist_to_com;
};

#endif // COM_MSG
