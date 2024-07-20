#pragma once

#include <stdint.h>
#include <string>

class AlarmInterface
{
public:
    virtual bool init(int pin, unsigned long interval) = 0;
    virtual bool start() = 0;
    virtual bool stop() = 0;
    virtual bool setEvent(bool state) = 0;
    virtual bool getEvent() = 0;
};