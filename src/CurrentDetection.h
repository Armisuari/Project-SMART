#pragma once
#include <Arduino.h>
#include <interfaces/AlarmInterface.h>
#include <interfaces/BTInterface.h>
#include <interfaces/CurrentMeterInterface.h>
#include <interfaces/DisplayInterface.h>
#include <interfaces/StorageInterface.h>
#include <interfaces/TimeInterface.h>

#include <systems/Configurator.h>
#include <systems/Formatter.h>
#include <systems/Settings.h>


#include "mdns.h"
#include "drivers/esp32/OTA/OTA_Handler.h"

class CurrentDetection
{

public:
    CurrentDetection(CurrentMeter &meter, TimeInterface &time, DisplayInterface &disp, Stream *stream, StorageInterface &stg,
                     AlarmInterface &buzzer, AlarmInterface &telegram);
    // CurrentDetection(CurrentMeter &meter, TimeInterface &time, DisplayInterface &disp, Stream *stream, StorageInterface &stg);

    bool init(float curThreshold = 0.05);
    bool updateMeterData();
    bool update_wifi_connection();
    bool setAlarmEvent(bool state0, bool state1);
    // void checkBTConfig();

private:
    CurrentMeter &_meter;
    DisplayInterface &_disp;
    StorageInterface &_stg;
    TimeInterface &_time;
    Stream *_stream;
    AlarmInterface &_buzzer;
    AlarmInterface &_telegram;
    float _curThreshold;
    const int relayPin = 4;

    char clientID[sizeof("SMART") + 6];
    void generateClientID(char *idBuff);
    void setupMDNSResponder(char *hostname);
    static void onOTAStarted();
    static void onOTAFinished();

public:
    Settings _cfg{_stg};
    Configurator _cfgr{_cfg, _time};
    const char* _tag = "CurrentDetection";
};