#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
    Process(int pid);
    int Pid();                               
    std::string User();                      
    std::string Command();                   
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       
    long int UpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
    int _pid;
    std::string _user_uid; 
    std::string _user;

    void FetchUID();
};

#endif