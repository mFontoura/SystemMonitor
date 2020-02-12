#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using namespace std;

class Processor {
 public:
    Processor();
    Processor(string usertime, string nicetime, string systemtime, string idletime, string iowait, string irq, string softirq, string steal, string guest, string guestnice);
    Processor(vector<string> labels) : Processor(labels.at(0),labels.at(1),labels.at(2),labels.at(3),labels.at(4),labels.at(5),labels.at(6),labels.at(7),labels.at(8),labels.at(9)){}

    void UpdateStats(vector<string> labels);

    float Utilization();
    
 private:
    unsigned long long int vUsertime, vNicetime, vSystemtime, vIdletime, vIowait, vIrq, vSoftirq, vSteal, vGuest, vGuestnice;
    unsigned long long int prevUsertime, prevNicetime, prevSystemtime, prevIdletime, prevIowait, prevIrq, prevSoftirq, prevSteal, prevGuest, prevGuestnice;
    unsigned long long int prevIdle, Idle, prevNonIdle, NonIdle, prevTotal, Total, totald, idled;
    unsigned long long int idlealltime, systemalltime, virtalltime, totaltime;
    float CPU_Percentage;
};

#endif


