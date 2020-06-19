#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

class Processor {
 public:
  float Utilization();  

 private:
  std::vector<unsigned long int> prev_cpu_util{};
  unsigned long int prev_idle_;
  unsigned long int prev_total_;

  unsigned long int idle_calc(std::vector<unsigned long int> v) const;
  unsigned long int total_calc(std::vector<unsigned long int> v) const; 
};

#endif