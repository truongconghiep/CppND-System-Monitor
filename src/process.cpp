#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include <iostream>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() 
{ 
    return std::stoi(this->pid);
    // return 0;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
    // return std::stof(this->cpu);
    return 0;
}

// TODO: Return the command that generated this process
string Process::Command() 
{ 
    // return this->cmd;
    return 0;
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
    // return this->mem; 
    return 0;
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{ 
    return this->user;
    // return 0;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{ 
    // return std::stoi(this->up_time);
    return 0;
}


// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::getProcess()
{
  //this->mem = LinuxParser::Ram(std::stoi(this->pid));
  //this->up_time = std::to_string(LinuxParser::UpTime(std::stoi(this->pid)));
//   std::cout << this->up_time << std::endl;
  this->user = LinuxParser::User(std::stoi(this->pid));
//   this->cmd = LinuxParser::Command(std::stoi(this->pid));
//    this->cpu = LinuxParser::ProcessCpu(std::stoi(this->pid));
// std::cout << "test" << std::endl;
}