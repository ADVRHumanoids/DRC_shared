<<<<<<< HEAD
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
=======
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
>>>>>>> b86ea05e2133f68d1939ee72c14a74e7ab8b2cde

#ifndef COM_PERCEPTION_MSG
#define COM_PERCEPTION_MSG

#include <string>
#include <vector>
#include <yarp/os/Portable.h>
#include <yarp/os/Bottle.h>
#include <boost/concept_check.hpp>
#include <kdl/frames.hpp>

class com_perception_msg
{
  public:
    /** \brief Default constructor. */
    com_perception_msg ()
    {
    }

    /** \brief YARP message exchange toBottle method. */
    yarp::os::Bottle toBottle ()
    {
      yarp::os::Bottle temp;
      yarp::os::Bottle& list= temp.addList();
      list.addString(command);

      return temp;
    }

    /** \brief YARP message exchange fromBottle method. */
    void fromBottle (yarp::os::Bottle* temp)
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

  public:
    /** \brief The command name. */
    std::string command;
};

#endif