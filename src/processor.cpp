#include "processor.h"
#include "linux_parser.h"
#include <iostream>

#include <string>
#include <math.h> 

using namespace std;
using namespace LinuxParser;

float get_sys_active_cpu_time1(vector<string> values) {
  return (stof(values[kUser_]) + stof(values[kNice_]) + stof(values[kSystem_]) +
          stof(values[kIRQ_]) + stof(values[kSoftIRQ_]) +
          stof(values[kSteal_]) + stof(values[kGuest_]) +
          stof(values[kGuestNice_]));
}

float get_sys_idle_cpu_time1(vector<string> values) {
  return (stof(values[kIdle_]) + stof(values[kIOwait_]));
}

std::string printCpuStats(std::vector<std::string> values1,
                                    std::vector<std::string> values2) {
  /*
  Because CPU stats can be calculated only if you take measures in two different
  time, this function has two parameters: two vectors of relevant values. We use
  a formula to calculate overall activity of processor.
  */
  float result = 0;
  float activeTime =
      fabs(get_sys_active_cpu_time1(values2) - get_sys_active_cpu_time1(values1));
  float idleTime =
      fabs(get_sys_idle_cpu_time1(values2) - get_sys_idle_cpu_time1(values1));
  float totalTime = activeTime + idleTime;
  if(totalTime != 0)
  {
    result = 100.0 * (activeTime / totalTime);
  }



  return std::to_string(result);
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
    this->currentCpuStats = LinuxParser::CpuUtilization();
    this->cpuPercent = printCpuStats(this->lastCpuStats, this->currentCpuStats);
    this->lastCpuStats = this->currentCpuStats;
    //   std::cout << "activeTime " << activeTime << std::endl;
    // std::cout << "cpuPercent " << this->cpuPercent << std::endl;
    return std::stof(this->cpuPercent); 
}

Processor::Processor()
{
    this->lastCpuStats = LinuxParser::CpuUtilization();
}