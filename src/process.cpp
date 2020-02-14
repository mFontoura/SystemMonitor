#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

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

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    auto uptime = LinuxParser::UpTime();
    auto Hertz = sysconf(_SC_CLK_TCK); 

    auto procData = LinuxParser::ProcessUtilization(_pid);
    int utime = stoi(procData.at(0));
    int stime = stoi(procData.at(1));
    int cutime = stoi(procData.at(2));
    int cstime = stoi(procData.at(3));
    long starttime = stol(procData.at(4));

    

    auto total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    auto seconds = uptime - (starttime / Hertz);
    if(seconds != 0){
        return 100 * ((total_time / Hertz) / seconds);
    }else{
        return 0;
    }
}

// TODO: Return the command that generated this process
string Process::Command() {
    return LinuxParser::Command(_pid);    
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    return LinuxParser::Ram(_pid) + " KB"; 
}

string Process::User() { return _user; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::FetchUID(){
    _user_uid = LinuxParser::Uid(_pid);
}