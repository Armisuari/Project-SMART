#include "CurrentMeter_ADS.h"

bool CurrentMeter_ADS::init()
{
    _ads.setGain(GAIN_ONE);
    if (!_ads.begin())
    {
        ESP_LOGE(_tag, "failed to initialize ads module");
        return false;
    }

    return true;
}

float CurrentMeter_ADS::readCurrent()
{
    float voltage;
    float current;
    float sum = 0;
    long time_check = millis();
    int counter = 0;

    while (millis() - time_check < 1000)
    {
        voltage = _ads.readADC_Differential_0_1() * multiplier;
        current = voltage * factor;
        // current /= 1000.0;

        sum += sq(current);
        counter = counter + 1;
    }

    current = sqrt(sum / counter);
    return (current * 10.0 - 0.01);
}