#include <string>

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

void Processor::UpdateStats(string usertime, string nicetime, string systemtime, string idletime, string iowait, string irq, string softirq, string steal, string guest, string guestnice){

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

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { return 0.0; }

