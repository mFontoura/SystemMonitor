#include <string>
#include <vector>
#include <iostream>

#include "processor.h"

using namespace std;


Processor::Processor(string usertime, string nicetime, string systemtime, string idletime, string iowait, string irq, string softirq, string steal, string guest, string guestnice){
    vUsertime = std::strtoll(usertime.c_str(), nullptr, 10);
    vNicetime = std::strtoll(nicetime.c_str(), nullptr, 10);
    vSystemtime = std::strtoll(systemtime.c_str(), nullptr, 10);
    vIdletime = std::strtoll(idletime.c_str(), nullptr, 10);
    vIowait = std::strtoll(iowait.c_str(), nullptr, 10);
    vIrq = std::strtoll(irq.c_str(), nullptr, 10);
    vSoftirq = std::strtoll(softirq.c_str(), nullptr, 10);
    vSteal = std::strtoll(steal.c_str(), nullptr, 10);
    vGuest = std::strtoll(guest.c_str(), nullptr, 10);
    vGuestnice = std::strtoll(guestnice.c_str(), nullptr, 10);
}

void Processor::UpdateStats(vector<string> labels){

    prevUsertime = vUsertime;
    prevNicetime = vNicetime;
    prevSystemtime = vSystemtime;
    prevIdletime = vIdletime;
    prevIowait = vIowait;
    prevIrq = vIrq;
    prevSoftirq = vSoftirq;
    prevSteal = vSteal;
    prevGuest = vGuest;
    prevGuestnice = vGuestnice;

    vUsertime = std::strtoll(labels.at(0).c_str(), nullptr, 10);
    vNicetime = std::strtoll(labels.at(1).c_str(), nullptr, 10);
    vSystemtime = std::strtoll(labels.at(2).c_str(), nullptr, 10);
    vIdletime = std::strtoll(labels.at(3).c_str(), nullptr, 10);
    vIowait = std::strtoll(labels.at(4).c_str(), nullptr, 10);
    vIrq = std::strtoll(labels.at(5).c_str(), nullptr, 10);
    vSoftirq = std::strtoll(labels.at(6).c_str(), nullptr, 10);
    vSteal = std::strtoll(labels.at(7).c_str(), nullptr, 10);
    vGuest = std::strtoll(labels.at(8).c_str(), nullptr, 10);
    vGuestnice = std::strtoll(labels.at(9).c_str(), nullptr, 10);

    vUsertime = vUsertime - vGuest;                     
    vNicetime = vNicetime - vGuestnice;
    idlealltime = vIdletime + vIowait;
    systemalltime = vSystemtime + vIrq + vSoftirq;
    virtalltime = vGuest + vGuestnice;
    totaltime = vUsertime + vNicetime + systemalltime + idlealltime + vSteal + virtalltime;
    
}

float Processor::Utilization() { 
    prevIdle = prevIdletime + prevIowait;
    Idle = vIdletime + vIowait;

    prevNonIdle = prevUsertime + prevNicetime + prevSystemtime + prevIrq + prevSoftirq + prevSteal;
    NonIdle = vUsertime + vNicetime + vSystemtime + vIrq + vSoftirq + vSteal;

    prevTotal = prevIdle + prevNonIdle;
    Total = Idle + NonIdle;

    totald = Total - prevTotal;
    idled = Idle - prevIdle;

    if(totald == 0){
        CPU_Percentage = 0;
    }else{
        CPU_Percentage = (float)(totald - idled)/(float)totald;
    }
    return CPU_Percentage;
}
