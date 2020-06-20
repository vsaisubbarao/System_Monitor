#include <vector>
#include <numeric>
#include <unistd.h>

#include "processor.h"
#include "linux_parser.h"

#define SLEEP_TIME 10000

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<unsigned long int> cpu_util = LinuxParser::CpuUtilization();

    if (prev_cpu_util.size() == 0){
        prev_cpu_util = cpu_util;
        prev_idle_ = idle_calc(prev_cpu_util);
        prev_total_ = total_calc(prev_cpu_util);

        return (float)(prev_total_ - prev_idle_)/prev_total_;
    }

    unsigned long int idle = idle_calc(cpu_util);
    
    unsigned long int total = total_calc(cpu_util);

    unsigned long int total_d = total - prev_total_;
    unsigned long int idle_d = idle - prev_idle_;

    prev_cpu_util = cpu_util;
    prev_idle_ = idle;
    prev_total_ = total;

    return (float)(total_d - idle_d)/total_d; 
}

// Return the total idle time of the cpu 
unsigned long int Processor::idle_calc(std::vector<unsigned long int> v) const{
    return v[LinuxParser::CPUStates::kIdle_] + v[LinuxParser::CPUStates::kIOwait_];
}

// Return the total time of the cpu was running 
unsigned long int Processor::total_calc(std::vector<unsigned long int> v) const{
    return std::accumulate(v.begin(), v.end()-2, 0);
}