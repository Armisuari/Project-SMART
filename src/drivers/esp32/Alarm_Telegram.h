#pragma once

#include <Arduino.h>
#include <interfaces/AlarmInterface.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

class Alarm_Telegram : public AlarmInterface
{
public:
    bool init(int pin, unsigned long interval);
    bool setEvent(bool state);
    bool getEvent();

private:
    long _interval;
    const char* _tag = "Telegram";
    bool _updateState;

    // Initialize Telegram BOT
    const String _BOTtoken = "7075913206:AAFTQDWHRZZiLqHlsxpMVlx5nsH6axSKG_8";
    const String _CHAT_ID = "-4121636105";

    WiFiClientSecure _client;
    UniversalTelegramBot _bot{_BOTtoken, _client};

    void handleNewMessages(int numNewMessage);

    static void staticTaskFunc(void *pvParam);
    void taskFunc();
    bool start();
    bool stop();
};
