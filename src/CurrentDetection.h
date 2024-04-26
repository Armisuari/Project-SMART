#pragma once
#include <Arduino.h>
#include <interfaces/AlarmInterface.h>
#include <interfaces/BTInterface.h>
#include <interfaces/CurrentMeterInterface.h>
#include <interfaces/DisplayInterface.h>
#include <interfaces/StorageInterface.h>
#include <interfaces/TimeInterface.h>

// #include <systems/Configurator.h>
// #include <systems/Formatter.h>
// #include <systems/Settings.h>

class CurrentDetection
{

public:
    // CurrentDetection(AlarmInterface &alarm, BTInterface &bt, CurrentMeter &meter, DisplayInterface &disp, StorageInterface &stg,
    //                  TimeInterface &time, Stream *stream);
    CurrentDetection(CurrentMeter &meter, Stream *stream);

    bool init();
    bool updateMeterData();
    // void checkBTConfig();

private:
    // AlarmInterface &_alarm;
    // BTInterface &_bt;
    CurrentMeter &_meter;
    // DisplayInterface &_disp;
    // StorageInterface &_stg;
    // TimeInterface &_time;
    Stream *_stream;

    // public:
    //     Settings _cfg{_stg};
    //     Configurator _cfgr{_cfg, _time};
};