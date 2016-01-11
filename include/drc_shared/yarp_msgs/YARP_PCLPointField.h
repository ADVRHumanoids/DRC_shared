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

#ifndef YARPMSG_TYPE_PCLPointField
#define YARPMSG_TYPE_PCLPointField

#include <string>
#include <vector>
#include <yarp/os/Portable.h>

#include <pcl/io/pcd_io.h>

class YARP_PCLPointField : public pcl::PCLPointField, public yarp::os::Portable {
public:
  YARP_PCLPointField(){
  };
  
  YARP_PCLPointField(const pcl::PCLPointField& pclpf): pcl::PCLPointField(pclpf){
  }
  
  bool read(yarp::os::ConnectionReader& connection) {
    // *** name ***
    int len = connection.expectInt();
    name.resize(len);
    if (!connection.expectBlock((char*)name.c_str(),len)) return false;
    
    // *** offset ***
    offset = connection.expectInt();

    // *** datatype ***
    datatype = connection.expectInt();

    // *** count ***
    count = connection.expectInt();
    
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    // *** name ***
    connection.appendInt(name.length());
    connection.appendExternalBlock((char*)name.c_str(),name.length());
    
    // *** offset ***
    connection.appendInt(offset);

    // *** datatype ***
    connection.appendInt(datatype);

    // *** count ***
    connection.appendInt(count);
    
    return !connection.isError();
  }
};

#endif