#include <string>
#include <iostream>
#include "format.h"

using std::string;

std::string Format::pid(int pid){
    string s = std::to_string(pid);
    s.resize(pid_size, ' ');
    return s;
}

std::string Format::user(std::string user){
    user.resize(user_size, ' ');
    return user;
}

std::string Format::cpu(float percent){
    string s = std::to_string(percent);
    s.resize(cpu_size, ' ');
    return s;
}

std::string Format::ram(long int ram){
    string s = std::to_string(ram);
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

std::string Format::command(std::string cmd){
    std::string s = cmd.c_str();
    s.resize(cmd_size, ' ');
    return s;
}