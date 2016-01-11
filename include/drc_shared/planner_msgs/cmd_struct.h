/* Copyright [2014,2015] [Alessio Rocchi, Mirko Ferrati, Alessandro Settimi, Valerio Varricchio]
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

class cmd_struct {
public:
  uint seq_num;
  double walk_meters;
  double side_meters;
  double turn_deg;
  
  cmd_struct(){}
  
  bool is_ok() const{
    int num0 = 0;
    if(walk_meters!=0) num0++;    
    if(side_meters!=0) num0++;
    if(turn_deg!=0) num0++;
    return num0<=1;
  }
};

