#include <vector>
#include <numeric>
#include <unistd.h>

#include "processor.h"
#include "linux_parser.h"

#define SLEEP_TIME 10000

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<unsigned long int> prev_cpu_util = LinuxParser::CpuUtilization();
    usleep(SLEEP_TIME);
    std::vector<unsigned long int> cpu_util = LinuxParser::CpuUtilization();
    
    unsigned long int prev_idle = prev_cpu_util[3] + prev_cpu_util[4];
    unsigned long int idle = cpu_util[3] + cpu_util[4];
    
    unsigned long int prev_total = std::accumulate(prev_cpu_util.begin(), prev_cpu_util.end()-2, 0);
    unsigned long int total = std::accumulate(cpu_util.begin(), cpu_util.end()-2, 0);

    unsigned long int total_d = total - prev_total;
    unsigned long int idle_d = idle - prev_idle;

    return 100 * (total_d - idle_d)/total_d; 
}