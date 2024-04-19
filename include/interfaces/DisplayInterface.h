#pragma once

#include <stdint.h>
#include <string>

class DisplayInterface
{

public:
    virtual bool init() = 0;
    virtual bool setCurrentValue(float f) = 0;
    virtual bool setDateTimeValue(std::string s) = 0;
};