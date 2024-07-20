#pragma once

class CurrentMeter
{

public:
    virtual bool init() = 0;
    virtual float readCurrent(int index) = 0;
    virtual bool getCTconnection() = 0;
};