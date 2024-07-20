#pragma once

#include <Arduino.h>
#include <interfaces/TimeInterface.h>

class Time_NTP : public TimeInterface
{
public:
    bool init();
    // bool setCurrentTime(uint32_t unixtime);
    time_t getCurrentTime();

private:
    const char *ntpServer = "pool.ntp.org";
};