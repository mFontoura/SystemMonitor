#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
    Processor();
    Processor(string usertime, string nicetime, string systemtime, string idletime, string iowait, string irq, string softirq, string steal, string guest, string guestnice);
    void UpdateStats(string usertime, string nicetime, string systemtime, string idletime, string iowait, string irq, string softirq, string steal, string guest, string guestnice);
    float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
    unsigned long long int vUsertime, vNicetime, vSystemtime, vIdletime, vIowait, vIrq, vSoftirq, vSteal, vGuest, vGuestnice;
    unsigned long long int prevUsertime, prevNicetime, prevSystemtime, prevIdletime, prevIowait, prevIrq, prevSoftirq, prevSteal, prevGuest, prevGuestnice;
    unsigned long long int idlealltime, systemalltime, virtalltime, totaltime;
};

#endif


/*
string label, usertime, nicetime, systemtime, idletime, iowait, irq, softirq, steal, guest, guestnice;
    unsigned long long int vUsertime, vNicetime, vSystemtime, vIdletime, vIowait, vIrq, vSoftirq, vSteal, vGuest, vGuestnice, idlealltime, systemalltime, virtalltime, totaltime;
    unsigned long long int prevIdle, previowait, prevNonIdle, prevuser, prevnice, prevsystem, previrq, prevsoftirq, prevsteal, prevTotal, Idle, NonIdle, Total, totald, idled;
    float CPU_Percentage;
    string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> label >> usertime >> nicetime >> systemtime >> idletime >> iowait >> irq >> softirq >> steal >> guest >> guestnice;

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

      vUsertime = vUsertime - vGuest;                     
      vNicetime = vNicetime - guestnice;
      idlealltime = vIdletime + vIowait;
      systemalltime = systemtime + vIrq + vSoftirq;
      virtalltime = vGuest + vGuestnice;
      totaltime = vUsertime + vNicetime + systemalltime + idlealltime + vSteal + virtalltime;
///////
      prevIdle = prevIdle + previowait;
      Idle = vIdletime + vIowait;

      prevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
      NonIdle = vUsertime + vNicetime + vSystemtime + vIrq + vSoftirq + vSteal;

      prevTotal = prevIdle + prevNonIdle;
      Total = Idle + NonIdle;

      totald = Total - prevTotal;
      idled = Idle - prevIdle;

      CPU_Percentage = (totald - idled)/totald;
    }*/