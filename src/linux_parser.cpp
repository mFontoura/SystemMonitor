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

// TODO: Update this to use std::filesystem
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

// Uptime of the system
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
    string key;
    vector<string> reader;
    string line;
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      int i = 0;
      while(linestream >> key) {
        if(i == 13 || i == 14 || i == 15 || i == 16 || i == 21) {          
          reader.push_back(key);
          if(i == 21) break;
        }
        i++;
      } 
    }

    return reader;
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
  auto ramInKb = std::stol(GetValueFromFile(stream, "VmSize:"));
  auto ramInMb = ramInKb / 1024.0; 

  string ramInMbStr = to_string(ramInMb);
  int pos = ramInMbStr.find(".");

  return ramInMbStr.substr(0, pos + 2);
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatusFilename);
  return GetValueFromFile(stream, "Uid:");
}


string LinuxParser::User(string uid_s) { 
  string line;
  string user;
  string dummy_value; // dummy_value is only used to parse the necessary values of a line.
  string lineUID;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user >> dummy_value >> lineUID) {
        if (lineUID == uid_s) {
          return user;
        }
      }
    }
  }

  return "";
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  auto hertz = sysconf(_SC_CLK_TCK);

  std::ifstream stream(kProcDirectory + to_string(pid) +  kStatFilename);
  string key, starttime;
  vector<string> reader;
  string line;
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    int i = 0;
    while(linestream >> key) {
      if(i == 21) {    
        starttime = key;
        break;
      }
      i++;
    } 
  }

  return UpTime() - std::stol(starttime)/hertz;   
}

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

