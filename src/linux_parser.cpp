#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


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

string LinuxParser::Kernel() {
  string os, versionLabel, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> versionLabel >> kernel;
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

float LinuxParser::MemoryUtilization() { 
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  long MemTotal = std::stol(GetValueFromFile(stream, "MemTotal:"));
  long MemFree = std::stol(GetValueFromFile(stream, "MemFree:"));
  long MemUsed = MemTotal - MemFree;
  float percent = (MemUsed * 100) / MemTotal;
  return percent * .01;
 }

long LinuxParser::UpTime() {
  string line, uptime, idle;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idle; 
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


vector<string> LinuxParser::CpuUtilization() { 

    string label, usertime, nicetime, systemtime, idletime, iowait, irq, softirq, steal, guest, guestnice;
    string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> label >> usertime >> nicetime >> systemtime >> idletime >> iowait >> irq >> softirq >> steal >> guest >> guestnice;
    }
    
    return std::vector<string> {usertime, nicetime, systemtime, idletime, iowait, irq, softirq, steal, guest, guestnice};
}

vector<string> LinuxParser::ProcessUtilization(int pid){
    std::ifstream stream(kProcDirectory + to_string(pid) +  kStatFilename);
    string var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var18, var19, var20, var21, var22;
    vector<string> reader;
    string line;
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> var7 >> var8 >> var9 >> var10 >> var11 >> var12 >> var13 >> var14 >> var15 >> var16 >> var17 >> var18 >> var19 >> var20 >> var21 >> var22;
    }

    return std::vector<string>{var14, var15, var16, var17, var22};


  /*
  /proc/[PID]/stat
    #14 utime - CPU time spent in user code, measured in clock ticks
    #15 stime - CPU time spent in kernel code, measured in clock ticks
    #16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
    #17 cstime - Waited-for children's CPU time spent in kernel code (in clock ticks)
    #22 starttime - Time when the process started, measured in clock ticks

  */
}

int LinuxParser::TotalProcesses() { 
  std::ifstream stream(kProcDirectory + kStatFilename);
  return std::stoi(GetValueFromFile(stream, "processes")); 
 }

int LinuxParser::RunningProcesses() { 
  std::ifstream stream(kProcDirectory + kStatFilename);
  return std::stoi(GetValueFromFile(stream, "procs_running")); 
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  std::ifstream stream(kProcDirectory + to_string(pid) +  kCmdlineFilename);
  if(stream.is_open()){
    string line;
    std::getline(stream, line);
    return line;
  }
  return string(); 
}


string LinuxParser::Ram(int pid) { 
  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatusFilename);
  return GetValueFromFile(stream, "VmSize:");
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatusFilename);
  return GetValueFromFile(stream, "Uid:");
}


string LinuxParser::User(string uid_s) { 
  string line;
  string user;
  string value1;
  string value2;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user >> value1 >> value2) {
        if (value2 == uid_s) {
          return user;
        }
      }
    }
  }
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }

string LinuxParser::GetValueFromFile(std::ifstream &stream, string label){
  string lineLabel, value, line;

  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> lineLabel >> value;
      if(lineLabel == label){
        return value;
      }
    }    
  }

  return "";
}

