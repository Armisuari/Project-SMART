// #include "miscellaneous/I2C_Scanner.h"
#include <Arduino.h>
#include <WiFi.h>

#include <interfaces/BTInterface.h>
#include <interfaces/AlarmInterface.h>
#include <interfaces/DisplayInterface.h>
#include <interfaces/StorageInterface.h>
#include <interfaces/CurrentMeterInterface.h>

class SettingsModule
{
    bool load(std::string settingFile);
    bool store(std::string settingFile);
    bool setInterval(uint32_t milliseconds);
    uint32_t getInterval();
    bool setTimezone(int8_t timezone);
    int8_t getTimezone();
};

class Formatter
{
    std::string formatTime(uint32_t unixtime, int8_t timezone);
};

void setup()
{
}

void loop()
{
}
