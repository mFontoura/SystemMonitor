#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(){

    if(_cpu == nullptr){
        _cpu = new Processor(LinuxParser::CpuUtilization());
    }

    auto pids = LinuxParser::Pids();
    _processes = new vector<Process>;
    for (int i = 0; i < pids.size(); i++){
        Process* newProc = new Process(pids.at(i));
        _processes->push_back(*newProc);
    }    
}

Processor& System::Cpu() { 
    _cpu->UpdateStats(LinuxParser::CpuUtilization());
    return *_cpu;
 }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    return *_processes;
}

string System::Kernel() { 
    return LinuxParser::Kernel(); 
}

float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
}

string System::OperatingSystem() {     
    return LinuxParser::OperatingSystem();
}

int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
}

int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
}

long int System::UpTime() {
    return LinuxParser::UpTime();
}