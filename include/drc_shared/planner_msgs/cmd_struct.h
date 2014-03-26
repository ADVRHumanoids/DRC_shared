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

