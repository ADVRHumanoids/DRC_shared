#ifndef __DATA_LOGGER_HPP
#define __DATA_LOGGER_HPP

#include <fstream>

namespace walkman {
  namespace log_utils {
    class data_logger {
    private:
      std::fstream fs;
    public:
      data_logger(){};
      
      void start(std::string file_name) {
	fs.open(file_name.c_str(),std::fstream::out);
      }
      
      ~data_logger() {
	fs.close();
      }
      
      void logYarpVector(yarp::sig::Vector &data)
      {
	for(int i=0;i<data.length()-1;i++)
	  fs << std::to_string(data[i]) << ",";
	fs << std::to_string(data[data.length()-1]);
	fs << std::endl;
      }
    };
  }
}
#endif