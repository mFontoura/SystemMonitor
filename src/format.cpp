#include <string>
#include <iomanip>


#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
    int extra;
    int hour, minutes;
    hour = seconds / 3600;
    extra = seconds % 3600;
    minutes = extra / 60;
    seconds = extra % 60;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    return ss.str();
 }