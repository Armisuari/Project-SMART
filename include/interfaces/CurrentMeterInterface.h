#pragma once



class CurrentMeter
{
    virtual bool init() = 0;
    virtual float readCurrent() = 0;
};