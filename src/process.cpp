#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() const { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const { 
    std::vector<unsigned long int> proc_cpu_data = LinuxParser::CpuUtilization(pid_);
    double uptime = LinuxParser::UpTime();
    auto Hertz = sysconf(_SC_CLK_TCK);
    // Time spent on the root process itself
    unsigned long int total_time = proc_cpu_data[0] + proc_cpu_data[1];
    // Time spent on the children processes
    total_time += proc_cpu_data[2] + proc_cpu_data[3];
    // Time elapsed since the start of the process
    double seconds = uptime - (proc_cpu_data[4]/Hertz);
    return (float)(total_time/Hertz)/seconds ; 
}

// Return the command that generated this process
string Process::Command() { 
    string cmd = LinuxParser::Command(pid_); 
    if(cmd.size() > 46) {
        cmd.resize(43);
        cmd = cmd + "..."; 
    }
    return cmd;
}

// Return this process's memory utilization
long int Process::Ram() const {
    return LinuxParser::Ram(pid_)/1024.0;
    // return std::ceil(memutil*100.0)/100.0;    
}

// Return the user (name) that generated this process
string Process::User() const { return LinuxParser::User(pid_); }

// Return the age of this process (in seconds)
double Process::UpTime() { 
    double sys_uptime = LinuxParser::UpTime();
    long proc_starttime = LinuxParser::startTime(pid_);
    long Hertz = sysconf(_SC_CLK_TCK);
    return (double)(sys_uptime - (proc_starttime/Hertz)); 
}

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    if (LinuxParser::sort_order == 'c') {
        return (a.CpuUtilization() < CpuUtilization());
        }
    else if (LinuxParser::sort_order == 'm'){
        return (a.Ram() < Ram());
    }
}
