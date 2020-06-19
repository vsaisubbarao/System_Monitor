#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Constructor 
System::System(){
    os_ = LinuxParser::OperatingSystem();
    kernel_ = LinuxParser::Kernel();
}
// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    std::vector<int> pids = LinuxParser::Pids();
    processes_ = {};
    for(auto pid : pids){
        Process tmp(pid);
        processes_.push_back(tmp);
    }
    std::sort(processes_.begin(), processes_.end());
    return processes_; }

// Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }

// Return the system's memory utilization in percentage
float System::MemoryUtilization() { 
    std::vector<unsigned long int> meminfo = LinuxParser::MemoryUtilization();
    return (float)(meminfo[0] - meminfo[1])/meminfo[0]; 
}

// Return the operating system name
std::string System::OperatingSystem() { return os_; }

// Return the number of processes actively running on the system
unsigned int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Return the total number of processes on the system
unsigned int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
double System::UpTime() { return LinuxParser::UpTime(); }