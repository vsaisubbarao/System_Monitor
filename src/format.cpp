#include <string>
#include <iostream>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int ss = seconds % 60;
    seconds /= 60;
    int mm = seconds % 60;
    int hh = seconds / 60;
    string htime = std::to_string(hh) + ":" + std::to_string(mm) + ":" + std::to_string(ss);
    return htime; 
}