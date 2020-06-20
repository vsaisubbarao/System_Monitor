#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid) : pid_(pid){}
  int Pid() const;                               
  std::string User() const;                      
  std::string Command();                   
  float CpuUtilization () const;                  
  long int Ram() const;                       
  double UpTime() ;                       
  bool operator<(Process const& a) const;  
 private:
  int pid_;
};

#endif