#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  System();
  Processor& Cpu();                   
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

  // TODO: Define any necessary private members
 private:
  Processor * _cpu = nullptr;
  std::vector<Process> * _processes;
};

#endif