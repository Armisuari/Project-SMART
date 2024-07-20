#include "Alarm_Telegram.h"

bool Alarm_Telegram::init(int pin, unsigned long interval)
{
    _client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    _bot.sendMessage(_CHAT_ID, "Device Online");
    _interval = interval;
    xTaskCreate(&Alarm_Telegram::staticTaskFunc, "loop task", 1024 * 6, this, 1, NULL);

    return true;
}

void Alarm_Telegram::handleNewMessages(int numNewMessages)
{
    for (int i = 0; i < numNewMessages; i++)
    {
        // Chat id of the requester
        String chat_id = String(_bot.messages[i].chat_id);
        if (chat_id != _CHAT_ID)
        {
            _bot.sendMessage(chat_id, "Unauthorized user", "");
            continue;
        }

        // Print the received message
        String text = _bot.messages[i].text;
        Serial.println(text);

        String from_name = _bot.messages[i].from_name;
    }
}

bool Alarm_Telegram::start()
{
    return _bot.sendMessage(_CHAT_ID, "Alarm Activated !");
}

bool Alarm_Telegram::stop()
{
    return _bot.sendMessage(_CHAT_ID, "Alarm Deactivated");
}

bool Alarm_Telegram::setEvent(bool state)
{
    ESP_LOGD(_tag, "setEvent = %d\n", state);
    _updateState = state;
    return _updateState;
}

bool Alarm_Telegram::getEvent()
{
    return _updateState;
}

/*static*/ void Alarm_Telegram::staticTaskFunc(void *pvParam)
{
    Alarm_Telegram *handler = reinterpret_cast<Alarm_Telegram *>(pvParam);
    handler->taskFunc();
}

void Alarm_Telegram::taskFunc()
{
    ESP_LOGD(_tag, "start taskFunc");
    vTaskDelay(2000);
    static bool wasActivated = false;
    while (1)
    {
        if (getEvent())
        {
            start();
            ESP_LOGI(_tag, "sending alarm to telegram app");
            wasActivated = true;
        }
        else
        {
            if (wasActivated)
            {
                ESP_LOGI(_tag, "stop sending alarm to telegram app");
                stop();
                wasActivated = false;
            }
        }
        vTaskDelay(1000);
    }
}