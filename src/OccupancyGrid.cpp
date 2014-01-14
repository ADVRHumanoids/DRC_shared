
#include <math.h>
#include <vector>
#include <stdio.h>
#include <yarp/os/all.h>
#include <assert.h>
#include <shared/yarp_msgs/YARP_Header.h>
#include <shared/utils/OccupancyGrid.h>

/*  Quick (re)implementation of an OccupancyGrid
 *                
 *                         y ^
 *               .           |
 *   v0*height   . . . . . . +---> x
 *               .           .
 *               ^           . 
 *               |           .
 *               +---> . . . . . ,
 *                       u0*width 
 * 
 *      
 *  email: v.varricchio@gmail.com
 * 
 */


OccupancyGrid::OccupancyGrid():width(0), height(0), u0(0), v0(0), cols(0), rows(0), resolution(0){
}

OccupancyGrid::OccupancyGrid(const double& _width, const double& _height, const double& _resolution,
			     const double& _u0, const double& _v0){
  init(_width, _height, _resolution, _u0, _v0);
}

OccupancyGrid::OccupancyGrid(const YARP_OccupancyGrid_msg& msg){
  header = msg.header;
  width = msg.width;
  height = msg.height;
  resolution = msg.resolution;
  u0 = msg.u0;
  v0 = msg.v0;
  init(false);
  //std::cout << "OccupancyGrid.h: Building obj from msg: " << msg.data.size() << std::endl;
  data = msg.data;
  origin = msg.origin;
}

void OccupancyGrid::fill_msg(YARP_OccupancyGrid_msg& msg){
  msg.header = header;
  msg.width = width;
  msg.height = height;
  msg.resolution = resolution;
  msg.u0 = u0;
  msg.v0 = v0;
  msg.data = data;
  msg.origin = origin;
}

void OccupancyGrid::init(const double& _width, const double& _height, const double& _resolution, 
			 const double& _u0, const double& _v0){
  width = _width;
  height = _height; 
  resolution = _resolution;
  u0 = _u0;
  v0 = _v0;
  init();
}

void OccupancyGrid::init(bool zero){
  cols = width/resolution;
  rows = height/resolution;
  
  // Make it ok with sensor frame (should be extracted?)
  
  origin.position.x = -width*u0;
  origin.position.y = 0;
  origin.position.z = -height*v0;
  
  double c45 = sqrt(2.0);
  origin.orientation.x = c45;
  origin.orientation.y = 0;
  origin.orientation.z = 0;
  origin.orientation.w = c45;
  
  if(!zero) return;

  data.resize(cols*rows);
  // set all zeros (free space)
  for(auto& d:data){
    d = 0;
  }
}

bool OccupancyGrid::set_value_rc(uint row, uint col, const double& value){
  if(is_in_rc(row, col)){
    //std::cout << "Writing "<< value << " at coords " << row << ", " << col << ", index:" << get_idx_rc(row, col) << " size: " << width*height << rows << " x " << cols <<std::endl;
    // 
    assert(get_idx_rc(row, col)<cols*rows);
    data[get_idx_rc(row, col)] = value;   
    return true;
  }
  return false;
}

bool OccupancyGrid::get_value_rc(uint row, uint col, double &value) const{
  if(is_in_rc(row, col)){
    value = data[get_idx_rc(row, col)];   
    return true;
  }
  return false;
}

double OccupancyGrid::value_rc(uint row, uint col) const{
  if(is_in_rc(row, col)){
    return data[get_idx_rc(row, col)];
  }
  return 0;
}
    
bool OccupancyGrid::set_value_xy(double x, double y, const double& value){
  return set_value_rc(get_row(y), get_col(x), value);
}

bool OccupancyGrid::get_value_xy(double x, double y, double& value) const{
  return get_value_rc(get_row(y), get_col(x), value);
}

double OccupancyGrid::value_xy(double x, double y) const{
  return value_rc(get_row(y), get_col(x));
}
    
bool OccupancyGrid::is_in_xy(double x, double y) const{
  return is_in_rc(get_row(y), get_col(x));
}
  
bool OccupancyGrid::is_in_rc(uint row, uint col) const{
  return row<rows && col<cols;
}
  
uint OccupancyGrid::get_col(double x) const{
  double xmin = -u0*width;
  int res =  round((x-xmin)/resolution);
  if(res < 0) res = 0;
  if(res > cols) res = cols;
  return res; 
}

uint OccupancyGrid::get_row(double y) const{
  double ymin = -v0*height;
  int res = round((y-ymin)/resolution);
  if(res < 0) res = 0;
  if(res > rows) res = rows;
  return res;
}

double OccupancyGrid::get_x(uint col) const{
  return col*resolution-u0*width;
}

double OccupancyGrid::get_y(uint row) const{
  return row*resolution-v0*height;
}


size_t OccupancyGrid::get_idx_rc(uint row, uint col) const{
  return row*cols+col;
}

uint OccupancyGrid::get_idx_xy(double x, double y) const{
  return get_idx_rc(get_row(y), get_col(x));
}

void OccupancyGrid::print(){
  std::cout << "Printing map: "<< width << " " << height << " " << resolution << std::flush;
  uint i=0;
  for(auto p: data){
    if(i%cols==0) std::cout << std::endl;
    std::cout << p << " ";
    i++;      
  }
  std::cout << std::endl;
}
