#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Add more buffers cached(for colors) like htop
std::vector<unsigned long int> LinuxParser::MemoryUtilization() {
  /*
  Reads the /proc/meminfo file and returns a vector containing
  [0] total memory 
  [1] free memory 
  */ 
  string line, key, value;
  std::vector<unsigned long int> meminfo;
  int counter = 0;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if(stream.is_open()){
    while(std::getline(stream, line)  && counter <2){
      std::istringstream lstream(line);
      lstream>>key>>value;
      meminfo.push_back(std::stoi(value));
      counter++;      
    }
  }
  return meminfo; 
  }

// Read and return the system uptime
long LinuxParser::UpTime() { 
  string line, uptime;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream lstream(line);
    lstream>>uptime;
  }
  return std::stol(uptime); 
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Modify for individual core utilization
vector<unsigned long int> LinuxParser::CpuUtilization() {
  /*
  Reads the /proc/meminfo file and returns a vector containing
  [0] user 
  [1] nice
  [2] system 
  [3] idle 
  [4] iowait 
  [5] irq
  [6] softirq
  [7] steal 
  [8] guest 
  [9] guest_nice  
  */ 
  string line, key, value;
  std::vector<unsigned long int> cpu_util;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    std::istringstream lstream(line);
    lstream >> key;
    while(lstream>>value){
      cpu_util.push_back(std::stol(value));
    }
  }
  return cpu_util; 
  }

// Read and return the total number of processes
unsigned int LinuxParser::TotalProcesses() { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()){
    while(std::getline(stream, line)){
      std::istringstream lstream(line);
      lstream >> key;
      if (key == "processes"){
        stream >> value;
        break;
      }
    }
  }
  return std::stoi(value); 
  }

// Read and return the number of running processes
unsigned int LinuxParser::RunningProcesses() { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()){
    while(std::getline(stream, line)){
      std::istringstream lstream(line);
      lstream >> key;
      if (key == "procs_running"){
        stream >> value;
        break;
      }
    }
  }
  return std::stoi(value);
  }

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()){
    std::getline(stream, line);
    return line; 
  }
  return string(); 
  }

// Read and return the memory used by a process
unsigned long int LinuxParser::Ram(int pid) { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()){
    while(std::getline(stream, line)){
      std::istringstream lstream(line);
      lstream >> key;
      if (key == "VmSize:"){
        lstream >> value;
        return stoi(value);
      }
    }
  }
  return 0; 
  }

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  string line, key, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()){
    while(std::getline(stream, line)){
      std::istringstream lstream(line);
      lstream >> key;
      if (key == "Uid:"){
        lstream >> value;
        return value;
      }

    }
  }
  return string(); }

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string line, key, val_x, value;
  string uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()){
    while(std::getline(stream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lstream(line);
      lstream >> key >> val_x >> value; 
      if (value == uid){ return key; }
    }
  }
  return string(); 
  }

// Read and return the uptime of a process
std::vector<unsigned long int> LinuxParser::CpuUtilization(int pid) {
  /*
  Reads the /proc/meminfo file and returns a vector containing
  [0] utime 
  [1] stime
  [2] cutime 
  [3] cstime 
  [4] starttime 
  */  
  string line, value;
  int counter = 0;
  std::vector<unsigned long int> cpu_util;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()){
    while(std::getline(stream, line)){
      std::istringstream lstream(line);
      counter++;
      if (counter == 14 || counter == 15 || counter == 16 || counter == 17 || counter == 22){
        lstream >> value;
        cpu_util.push_back(std::stoi(value));
      }
    }
  }
  return std::vector<unsigned long int>{}; 
}

unsigned long int LinuxParser::startTime(int pid){
  string line, value;
  int counter = 0;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()){
    while(std::getline(stream, line)){
      std::istringstream lstream(line);
      counter++;
      if (counter == 22){
        lstream >> value;
        return std::stoi(value);
      }
    }
  }
  return 0; 
}
