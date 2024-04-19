#pragma once

#include <stdint.h>
#include <string>

class AlarmInterface
{
public:
    virtual bool init();
    virtual bool start(uint8_t pin);
    virtual bool stop(uint8_t pin);
};