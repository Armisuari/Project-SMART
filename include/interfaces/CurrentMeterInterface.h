#pragma once

class CurrentMeter
{

public:
    virtual bool init() = 0;
    virtual float readCurrent() = 0;
};