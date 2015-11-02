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

#ifndef ROBOT_INTERFACE_STATUS_MSG
#define ROBOT_INTERFACE_STATUS_MSG
#include <string>
#include <vector>
#include <yarp/os/Bottle.h>

class robotInterfaceStatusMsg
{
public:
    std::vector<int> crashed_boards;
    std::vector<std::pair<int,std::string>> faulted_boards;
    std::vector<int> currents;
    int total_connected_boards;
    yarp::os::Bottle toBottle()
    {
        yarp::os::Bottle temp;
        yarp::os::Bottle& list= temp.addList();
        //temp.addInt(crashed_boards.size());
        list.addString("crashed_boards");
        for (int i=0;i<crashed_boards.size();i++)
        {
            list.addInt(crashed_boards[i]);
        }
        yarp::os::Bottle& list1= temp.addList();
        list1.addString("faulted_boards");        
        for (int i=0;i<faulted_boards.size();i++)
        {
            list1.addInt(faulted_boards[i].first);
            list1.addString(faulted_boards[i].second);
        }
//        temp.add(total_connected_boards);
        return temp;
    }
    void fromBottle(yarp::os::Bottle& temp)
    {
        yarp::os::Bottle* list=temp.get(0).asList();
        for (int i=1;i<list->size();i++)
            crashed_boards.push_back(list->get(i).asInt());
        yarp::os::Bottle* list1=temp.get(1).asList();
        for (int i=1;i<list1->size();i=i+2)
            faulted_boards.push_back(std::make_pair(list1->get(i).asInt(),list1->get(i+1).asString()));
  //      total_connected_boards=temp.get(num+2).asInt();
        return;
    }
};

#endif //ROBOT_INTERFACE_STATUS_MSG
