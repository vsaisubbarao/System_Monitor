#include <string>
#include <iostream>
#include "format.h"

/* Size of PID string made maximum with spaces so that 
the characters from previous instant will not be left*/ 
std::string Format::pid(int pid){
    std::string s = std::to_string(pid);
    s.resize(pid_size, ' ');
    return s;
}

/* Size of user string made maximum with spaces so that 
the characters from previous instant will not be left*/ 
std::string Format::user(std::string user){
    user.resize(user_size, ' ');
    return user;
}

/* Size of cpu% string made maximum with spaces so that 
the characters from previous instant will not be left*/ 
std::string Format::cpu(float percent){
    std::string s = std::to_string(percent);
    s.resize(cpu_size, ' ');
    return s;
}

/* Size of Ram string made maximum with spaces so that 
the characters from previous instant will not be left*/ 
std::string Format::ram(long int ram){
    std::string s = std::to_string(ram);
    s.resize(ram_size, ' ');
    return s;
}

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
std::string Format::ElapsedTime(long seconds) { 
    int ss = seconds % 60;
    seconds /= 60;
    int mm = seconds % 60;
    int hh = seconds / 60;
    std::string htime = std::to_string(hh) + ":" + std::to_string(mm) + ":" + std::to_string(ss);
    htime.resize(elapsed_time_size, ' ');
    return htime; 
}

/* Size of command string made maximum with spaces so that 
the characters from previous instant will not be left*/ 
std::string Format::command(std::string cmd){
    std::string s = cmd.c_str(); // Terminating the string at "\0" 
    s.resize(cmd_size, ' ');
    return s;
}