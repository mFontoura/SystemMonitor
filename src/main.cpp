#include <iostream>

#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  /*std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;
  std::cout<<system.Processes()[0].CpuUtilization() * 100<<std::endl;*/
  NCursesDisplay::Display(system);
}