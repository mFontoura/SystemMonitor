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
    _hertz = sysconf(_SC_CLK_TCK);   

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
        _cpu = ((float)(total_time / _hertz) / (float)seconds);
        return _cpu;
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
    return LinuxParser::Ram(_pid) + " MB"; 
}

string Process::User() { return _user; }

// Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(_pid);  
}

bool Process::operator<(Process const& a) const { 
    return this->_cpu < a._cpu;
}

void Process::FetchUID(){
    _user_uid = LinuxParser::Uid(_pid);
}