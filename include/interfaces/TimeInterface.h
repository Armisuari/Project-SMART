#pragma once

#include <string>
#include <stdint.h>

class TimeInterface
{
public:
    virtual bool init() = 0;
    // virtual bool setCurrentTime(uint32_t unixtime) = 0;
    virtual time_t getCurrentTime() = 0;
};