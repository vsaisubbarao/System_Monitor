#ifndef FORMAT_H
#define FORMAT_H

#include <string>

namespace Format {
const int pid_size = 7;
const int user_size = 7;
const int cpu_size = 10;
const int ram_size = 9;
const int elapsed_time_size = 11;
const int cmd_size = 200;

std::string pid(int pid);
std::string user(std::string user);
std::string cpu(float percent);
std::string ram(long int ram);
std::string ElapsedTime(long times);  
std::string command(std::string cmd);
};                                    

#endif