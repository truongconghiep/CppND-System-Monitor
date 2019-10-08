#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using namespace std;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor();

  // TODO: Declare any necessary private members
 private:
  std::vector<std::string> lastCpuStats;
  std::vector<std::string> currentCpuStats;
  std::string cpuPercent;
};

#endif