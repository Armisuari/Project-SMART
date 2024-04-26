#include "CurrentDetection.h"

// CurrentDetection::CurrentDetection(AlarmInterface &alarm, BTInterface &bt, CurrentMeter &meter, DisplayInterface &disp, StorageInterface &stg,
//                                    TimeInterface &time, Stream* stream)
//     : _alarm(alarm), _bt(bt), _meter(meter), _disp(disp), _stg(stg), _time(time), _stream(stream) {}
CurrentDetection::CurrentDetection(CurrentMeter &meter, Stream *stream)
    : _meter(meter), _stream(stream) {}

bool CurrentDetection::init()
{
    // _alarm.init();
    // _bt.init();
    _meter.init();
    // _disp.init();
    // _stg.init();
    // _time.init();

    // _disp.setConnectionStatus(false);

    // _cfg.load();

    updateMeterData();

    return true;
}

bool CurrentDetection::updateMeterData()
{
    // std::string currentDatetime =
    //     Formatter::formatTime(_time.getCurrentTime(), _cfg.getTimezone());
    // _disp.setDatetimeValue(currentDatetime);
    // _disp.setHumidityValue(_sens.readHumidity());
    // _disp.setTemperatureValue(_sens.readTemperature());

    _stream->printf("Irms: %4.2f A\n", _meter.readCurrent());

    return true;
}

// void CurrentDetection::checkSerialConfig()
// {
//     std::string inputCmd;
//     std::string outputCmd;

//     inputCmd = _ser.read();
//     if (inputCmd.length() > 0)
//     {
//         outputCmd = _cfgr.processInput(inputCmd);
//         _ser.write(outputCmd);
//     }
// }
