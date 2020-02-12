#include "ncurses_display.h"
#include "system.h"
#include <iostream>

int main() {
  System system;
  //std::cout<< "using: " << system.Cpu().Utilization() << "\n";
  //std::cout<< "using: " << system.Cpu().Utilization() << "\n";
  //std::cout<< "using: " << system.Cpu().Utilization() << "\n";
  NCursesDisplay::Display(system);
}