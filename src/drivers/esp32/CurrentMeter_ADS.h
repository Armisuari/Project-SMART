#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <EmonLib.h>
#include <interfaces/CurrentMeterInterface.h>

class CurrentMeter_ADS : public CurrentMeter
{
public:
    bool init();
    float readCurrent();

private:
    const String _tag = "CurrentMeter";
    Adafruit_ADS1115 _ads;
    const float factor = 30;
    const float multiplier = 0.00005;
};