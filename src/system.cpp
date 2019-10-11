#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu()
{ 
    return cpu_;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes()
{
    this->refreshList();
    for (unsigned int i = 0; i < 10; i++)
    {
        this->processes_[i].getProcess();
    }
    return processes_;
    // return 0;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel()
{ 
    return this->kernelVer;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() 
{
    return LinuxParser::MemoryUtilization();
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { return this->osName;}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() 
{ 
  return LinuxParser::RunningProcesses();  
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() 
{ 
    return LinuxParser::TotalProcesses(); 
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime()
{
    return LinuxParser::UpTime();
}

System::System() 
{
  /*
  Getting initial info about system
  Initial data for individual cores is set
  System data is set
  */
  this->osName = LinuxParser::OperatingSystem();
  this->kernelVer = LinuxParser::Kernel();
  this->refreshList();
}

void System::refreshList() 
{
  vector<int> pids = LinuxParser::Pids();
  this->processes_.clear();
  for (unsigned int i = pids.size() - 10; i < pids.size(); i++) 
  {
    Process proc(std::to_string(pids[i]));
    this->processes_.push_back(proc);
  }
}
