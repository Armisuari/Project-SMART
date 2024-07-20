#pragma once

#include <stdint.h>
#include <string>

class DisplayInterface {

    public:
        virtual bool init() = 0;
        virtual bool setCurrentValue(float value0, float value1) = 0;
        virtual bool setConnectionStatus(bool connected) = 0;
        virtual bool setDatetimeValue(std::string datetimeStr) = 0;
        virtual bool setAlarmEvent(bool state) = 0;
        virtual bool setCTconnection(bool conn) = 0;
};