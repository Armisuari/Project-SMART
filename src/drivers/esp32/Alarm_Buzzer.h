#pragma once

#include <Arduino.h>
#include <interfaces/AlarmInterface.h>

class Alarm_Buzzer : public AlarmInterface
{
    public :
        bool init(int pin, unsigned long interval);
        bool setEvent(bool state);
        bool getEvent();

    private:
        int _pin;
        long _interval;
        const String _tag = "Buzzer";
        bool _updateState;

        static void staticTaskFunc(void *pvParam);
        void taskFunc();
        bool start();
        bool stop();
};


