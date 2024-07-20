#include "Alarm_Buzzer.h"

bool Alarm_Buzzer::init(int pin, unsigned long interval = 500)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    _interval = interval;

    xTaskCreate(&Alarm_Buzzer::staticTaskFunc, "loop task", 1024 * 2, this, 1, NULL);

    return true;
}

bool Alarm_Buzzer::start()
{
    ESP_LOGD(_tag, "Buzzer beep");

    digitalWrite(_pin, HIGH);
    vTaskDelay(_interval);
    digitalWrite(_pin, LOW);
    vTaskDelay(_interval);

    return true;
}

bool Alarm_Buzzer::stop()
{
    digitalWrite(_pin, LOW);
    return true;
}

bool Alarm_Buzzer::setEvent(bool state)
{
    // ESP_LOGD(_tag, "set Event = %d\n", state);
    _updateState = state;
    return _updateState;
}

bool Alarm_Buzzer::getEvent()
{
    return _updateState;
}

/*static*/ void Alarm_Buzzer::staticTaskFunc(void *pvParam)
{
    Alarm_Buzzer* handler = reinterpret_cast<Alarm_Buzzer*>(pvParam);
    handler->taskFunc();
}

void Alarm_Buzzer::taskFunc()
{
    vTaskDelay(2000);
    while (1)
    {
        if (!getEvent())
        {
            stop();
        }
        else
        {
            start();
        }

    vTaskDelay(100);
    }
    vTaskDelete(NULL);
}