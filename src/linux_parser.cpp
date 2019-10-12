#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"
// #include <iostream>

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

  string name = "Linux version ";
  while (std::getline(stream, line)) 
  {
    if (line.compare(0, name.size(), name) == 0) 
    {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      return values[2];
    }
  }
  return "";
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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  string line;
  string name1 = "MemAvailable:";
  string name2 = "MemFree:";
  string name3 = "Buffers:";

  string value;
  // int result;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  float total_mem = 0;
  float free_mem = 0;
  float buffers = 0;
  while (std::getline(stream, line))
  {
    if (total_mem != 0 && free_mem != 0) break;
    if (line.compare(0, name1.size(), name1) == 0) 
    {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      total_mem = stof(values[1]);
    }
    if (line.compare(0, name2.size(), name2) == 0) 
    {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      free_mem = stof(values[1]);
    }
    if (line.compare(0, name3.size(), name3) == 0) {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      buffers = stof(values[1]);
    }
  }
  // calculating usage:
  return float(100.0 * (1 - (free_mem / (total_mem - buffers))));
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  std::string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  getline(stream, line);
  std::istringstream buf(line);
  std::istream_iterator<std::string> beg(buf), end;
  std::vector<std::string> values(beg, end);
  return stoi(values[0]);
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

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{ 
  std::string line;
  std::string name = "cpu";
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (std::getline(stream, line)) 
  {
    if (line.compare(0, name.size(), name) == 0) 
    {
      std::istringstream buf(line);
      std::istream_iterator<string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      // set of cpu data active and idle times;
      return values;
    }
  }
  return (vector<string>());
}


// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  std::string line;
  int result = 0;
  std::string name = "processes";
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (std::getline(stream, line))
  {
    if (line.compare(0, name.size(), name) == 0) 
    {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      result += stoi(values[1]);
      break;
    }
  }
  return result;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{ 
  std::string line;
  int result = 0;
  std::string name = "procs_running";
  std::ifstream stream(kProcDirectory + kStatFilename);
  while (std::getline(stream, line)) 
  {
    if (line.compare(0, name.size(), name) == 0) 
    {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      result += stoi(values[1]);
      break;
    }
  }
  return result;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  std::string line;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  std::getline(stream, line);
  return line;
}

std::string LinuxParser::ProcessCpu(int pid)
{
  std::string line;
  std::string value;
  float result;
  // ifstream stream =
  //     Util::getStream((Path::basePath() + pid + "/" + Path::statPath()));
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::getline(stream, line);
  std::string str = line;
  std::istringstream buf(str);
  std::istream_iterator<std::string> beg(buf), end;
  std::vector<std::string> values(beg, end);  // done!
  // acquiring relevant times for calculation of active occupation of CPU for
  // selected process
  float utime = LinuxParser::UpTime(pid);
  // std::cout << "utime " << utime << "\r" << std::endl;
  float stime;
  float cutime;
  float cstime;
  float starttime;

  // if(values.size() > 21)
  {
    stime = stof(values[14]);
    cutime = stof(values[15]);
    cstime = stof(values[16]);
    starttime = stof(values[21]);
  }
  float uptime = LinuxParser::UpTime();
  float freq = sysconf(_SC_CLK_TCK);
  float total_time = utime + stime + cutime + cstime;
  float seconds = uptime - (starttime / freq);
  result = ((total_time / freq) / seconds);
  // std::cout << "result " << result << "\r" << std::endl; 
  return std::to_string(result);
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) 
{ 
  std::string line;
  // Declaring search attribute for file
  std::string name = "VmData";
  std::string value;
  float result;
  // Opening stream for specific file
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  while (std::getline(stream, line)) 
  {
    // Searching line by line
    if (line.compare(0, name.size(), name) == 0) {
      // slicing string line on ws for values using sstream
      std::istringstream buf(line);
      std::istream_iterator<string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      // conversion kB -> GB
      result = (stof(values[1]) / float(1024));
      break;
    }
  }
  return std::to_string(result);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) 
{ 
  std::string line;
  std::string name = "Uid:";
  std::string result = "";
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  // Getting UID for user
  while (std::getline(stream, line)) 
  {
    if (line.compare(0, name.size(), name) == 0) 
    {
      std::istringstream buf(line);
      std::istream_iterator<std::string> beg(buf), end;
      std::vector<std::string> values(beg, end);
      result = values[1];
      break;
    }
  }
  std::ifstream stream1("/etc/passwd");
  name = ("x:" + result);
  // Searching for name of the user with selected UID
  while (std::getline(stream1, line)) {
    if (line.find(name) != std::string::npos) {
      result = line.substr(0, line.find(":"));
      return result;
    }
  }
  return "";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
float LinuxParser::UpTime(int pid) 
{
  std::string line;
  std::string value;
  // float result;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::getline(stream, line);
  std::string str = line;
  std::istringstream buf(str);
  std::istream_iterator<std::string> beg(buf), end;
  std::vector<std::string> values(beg, end);  // done!
  // Using sysconf to get clock ticks of the host machine
  return (stof(values[21]) / sysconf(_SC_CLK_TCK));
}

float LinuxParser::StartTime(int pid) 
{
  std::string line;
  std::string value;
  // float result;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  std::getline(stream, line);
  std::string str = line;
  std::istringstream buf(str);
  std::istream_iterator<std::string> beg(buf), end;
  std::vector<std::string> values(beg, end);  // done!
  // Using sysconf to get clock ticks of the host machine
  return (stof(values[21]) / sysconf(_SC_CLK_TCK));
}