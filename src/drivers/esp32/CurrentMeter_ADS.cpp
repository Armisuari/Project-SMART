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

float CurrentMeter_ADS::readCurrent(int index)
{
    float voltage;
    float current;
    float sum = 0;
    long time_check = millis();
    int counter = 0;

    // int16_t Ads_SingleEnd[2];
    // for (size_t i = 0; i < sizeof(Ads_SingleEnd); ++i)
    // {
    //     Ads_SingleEnd[i] = _ads.readADC_SingleEnded(i);
    //     delay(10);
    // }
    // ESP_LOGD(_tag, "ads1115 A0 = %d | A1 = %d\n", Ads_SingleEnd[0], Ads_SingleEnd[1]);

    // if (A0Value <= 2500)
    // {
    //     ESP_LOGW(_tag, "Current Transformer disconnected");
    //     // _ctConnection = false;
    //     return NAN;
    // }
    // else
    // {
    //     _ctConnection = true;
    // }

    while (millis() - time_check < 1000)
    {
        if (index == 0)
        {
            voltage = _ads.readADC_Differential_0_1() * multiplier;
        }
        else if (index == 1)
        {
            voltage = _ads.readADC_Differential_2_3() * multiplier;
        }
        else
        {
            ESP_LOGW(_tag, "the meter index limited to 2 channels");
            return 0.0;
        }

        current = voltage * factor;
        // current /= 1000.0;

        sum += sq(current);
        counter = counter + 1;
    }

    current = sqrt(sum / counter) * 10.0;
    if (current <= 0.05)
        current = 0.0;

    return (current * 120.0); //times by 120 based on CT ratio of the panel 600/5;
}

bool CurrentMeter_ADS::getCTconnection()
{
    return _ctConnection;
}