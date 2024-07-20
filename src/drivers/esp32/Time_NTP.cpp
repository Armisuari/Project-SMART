#include "Time_NTP.h"

bool Time_NTP::init()
{
    configTime(0, 0, ntpServer);;
    return true;
}

// bool Time_NTP::setCurrentTime(uint32_t unixtime)
// {
//     _rtc.adjust(DateTime(unixtime));

//     return true;
// }

time_t Time_NTP::getCurrentTime() { return time(NULL); }
