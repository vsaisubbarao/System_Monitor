#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() const { return pid_; }

// Return this process's CPU utilization
long Process::CpuUtilization() const { 
    std::vector<unsigned long int> proc_cpu_data = LinuxParser::CpuUtilization(pid_);
    long uptime = LinuxParser::UpTime();
    auto Hertz = sysconf(_SC_CLK_TCK);
    // Time spent on the root process itself
    long total_time = proc_cpu_data[0] + proc_cpu_data[1];
    // Time spent on the children processes
    total_time += proc_cpu_data[2] + proc_cpu_data[3];
    // Time elapsed since the start of the process
    long seconds = uptime - (proc_cpu_data[4]/Hertz);
    return 100*(total_time/Hertz)/seconds ; 
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
string Process::Ram() const { 
    unsigned long mem = (long) LinuxParser::Ram(pid_)/1024.0f;   
    return to_string(mem); 
}

// Return the user (name) that generated this process
string Process::User() const { return LinuxParser::User(pid_); }

// Return the age of this process (in seconds)
long Process::UpTime() const { 
    long sys_uptime = LinuxParser::UpTime();
    long proc_starttime = LinuxParser::startTime(pid_);
    long Hertz = sysconf(_SC_CLK_TCK);
    return sys_uptime - (proc_starttime/Hertz); 
}

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
    return (a.CpuUtilization() < CpuUtilization());
}