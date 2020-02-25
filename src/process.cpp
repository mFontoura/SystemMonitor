#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"
#include "format.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
    _pid = pid;
    FetchUID();
    _user = LinuxParser::User(_user_uid);
    CpuUtilization();
}

int Process::Pid() { return _pid; }

void Process::UpdateProcessStats(){
    _uptime = LinuxParser::UpTime();
    _hertz = sysconf(_SC_CLK_TCK); //TODO: cache var    

    auto procData = LinuxParser::ProcessUtilization(_pid);
    _utime = stoi(procData.at(0));
    _stime = stoi(procData.at(1));
    _cutime = stoi(procData.at(2));
    _cstime = stoi(procData.at(3));
    _starttime = stol(procData.at(4));
}

float Process::CpuUtilization() { 
    UpdateProcessStats();
    

    auto total_time = _utime + _stime;
    total_time = total_time + _cutime + _cstime;
    auto seconds = _uptime - (_starttime / _hertz);
    if(seconds != 0){
        return ((float)(total_time / _hertz) / (float)seconds);
    }else{
        return 0;
    }
}

// Return the command that generated this process
string Process::Command() {
    return LinuxParser::Command(_pid);    
}

// Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(_pid) + " KB"; 
}

string Process::User() { return _user; }

// Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(_pid);  
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::FetchUID(){
    _user_uid = LinuxParser::Uid(_pid);
}