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
    float CpuUtilization();
    std::string Ram();
    long int UpTime();
    bool operator<(Process const& a) const; 

 private:
    int _pid;
    std::string _user_uid; 
    std::string _user;

    float _cpu;

    long _uptime;
    long _hertz;

    int _utime;
    int _stime;
    int _cutime;
    int _cstime;
    long _starttime;

    void FetchUID();
    void UpdateProcessStats();
};

#endif