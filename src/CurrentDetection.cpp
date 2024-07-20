#include "CurrentDetection.h"

CurrentDetection::CurrentDetection(CurrentMeter &meter, TimeInterface &time, DisplayInterface &disp, Stream *stream,
                                   StorageInterface &stg, AlarmInterface &buzzer, AlarmInterface &telegram)
    : _meter(meter), _time(time), _disp(disp), _stream(stream), _stg(stg), _buzzer(buzzer), _telegram(telegram)
{
}

bool CurrentDetection::init(float curThreshold)
{
    generateClientID(clientID);
    setupMDNSResponder(clientID);

    _meter.init();
    _disp.init();
    _stg.init();
    _time.init();
    _buzzer.init(2, 500);

    _telegram.init(0, 1000);
    _curThreshold = curThreshold;
    pinMode(relayPin, OUTPUT);

    // --- ota ---
    otaHandler.setup(&onOTAStarted, &onOTAFinished);
    xTaskCreate(otaHandler.task, "OtaHandler::task", 1024 * 4, NULL, 15, NULL);

    // _cfg.load();

    updateMeterData();

    return true;
}

bool CurrentDetection::updateMeterData()
{
    // std::string currentDatetime = Formatter::formatTime(_time.getCurrentTime(), _cfg.getTimezone());
    std::string currentDatetime = Formatter::formatTime(_time.getCurrentTime());

    _disp.setDatetimeValue(currentDatetime);
    _disp.setCurrentValue(_meter.readCurrent(1), _meter.readCurrent(0));
    ESP_LOGD(_tag, "Irms: %4.2f A | %4.2f A | ThresHold: %.2f A\n", _meter.readCurrent(1), _meter.readCurrent(0), _curThreshold);
    // _disp.setCTconnection(_meter.getCTconnection());

    return true;
}

bool CurrentDetection::update_wifi_connection()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        _disp.setConnectionStatus(false);
    }
    else
    {
        _disp.setConnectionStatus(true);
    }

    return true;
}

// bool CurrentDetection::setAlarmEvent(bool state)
// {
//     if (state)
//     {
//         if ((_meter.readCurrent() > _curThreshold))
//         {
//             ESP_LOGI(_tag, "Event Triggered !");
//             _disp.setAlarmEvent(true);
//             _buzzer.setEvent(true);
//             _telegram.setEvent(true);
//             digitalWrite(relayPin, HIGH);
//         }
//         else
//         {
//             _disp.setAlarmEvent(false);
//             _buzzer.setEvent(false);
//             _telegram.setEvent(false);
//             digitalWrite(relayPin, LOW);
//         }
//     }
//     else
//     {
//         return false;
//     }

//     return true;
// }

bool CurrentDetection::setAlarmEvent(bool state0, bool state1)
{
    if (state0)
    {
        if ((_meter.readCurrent(1) > _curThreshold))
        {
            ESP_LOGI(_tag, "Event Triggered 0! current ThresHold = %.2f", _curThreshold);
            unsigned long startTime = millis(); // Record the start time
            while (millis() - startTime < 1500)
            {
                // Wait for 3 seconds before triggering the alarm
                // You can add additional tasks here if needed
                _disp.setAlarmEvent(false);
                _buzzer.setEvent(false);
                // _telegram.setEvent(false);
                digitalWrite(relayPin, LOW);
            }
            // else
            // {
            if (_meter.readCurrent(1) > _curThreshold)
            {
                ESP_LOGI(_tag, "After wait to trig");
                _disp.setAlarmEvent(true);
                _buzzer.setEvent(true);
                _telegram.setEvent(true);
                digitalWrite(relayPin, HIGH);
                ESP_LOGD(_tag, "Relay on");
            }
            // }
        }
        else
        {
            ESP_LOGI(_tag, "Event not Triggered 0!");
            _disp.setAlarmEvent(false);
            _buzzer.setEvent(false);
            _telegram.setEvent(false);
            digitalWrite(relayPin, LOW);
        }
    }


    // if (state1)
    // {
    //     if ((_meter.readCurrent(0) > _curThreshold))
    //     {
    //         ESP_LOGI(_tag, "Event Triggered 1!");
    //         unsigned long startTime = millis(); // Record the start time
    //         while (millis() - startTime < 1500)
    //         {
    //             // Wait for 3 seconds before triggering the alarm
    //             // You can add additional tasks here if needed
    //             _disp.setAlarmEvent(false);
    //             _buzzer.setEvent(false);
    //             // _telegram.setEvent(false);
    //             digitalWrite(relayPin, LOW);
    //         }
    //         // else
    //         // {
    //         if (_meter.readCurrent(0) > _curThreshold)
    //         {

    //             _disp.setAlarmEvent(true);
    //             _buzzer.setEvent(true);
    //             _telegram.setEvent(true);
    //             digitalWrite(relayPin, HIGH);
    //             ESP_LOGD(_tag, "Relay on");
    //         }
    //         // }
    //     }
    //     else
    //     {
    //         _disp.setAlarmEvent(false);
    //         _buzzer.setEvent(false);
    //         _telegram.setEvent(false);
    //         digitalWrite(relayPin, LOW);
    //     }
    // }

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

void CurrentDetection::generateClientID(char *idBuff)
{
    const char *clientIdPrefix = "SMART-";
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    sprintf(idBuff, "%s%02X%02X%02X", clientIdPrefix, mac[3], mac[4], mac[5]);
}

void CurrentDetection::setupMDNSResponder(char *hostname)
{
    // Serial.printf("hosname: %s\n", hostname);
    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_init());
    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_hostname_set(hostname));
    ESP_LOGI("MAIN", "MDNS hostname: %s", hostname);

    // OTA Service decription
    mdns_txt_item_t serviceTxtData[4] = {
        {"HW version", "v1"},
        {"FW version", "v1"},
        {"Device", "SMART"},
        {"path", "/"}};

    ESP_ERROR_CHECK_WITHOUT_ABORT(mdns_service_add(NULL, "_http", "_tcp", 80, serviceTxtData, 3));
}

void CurrentDetection::onOTAStarted()
{
}

void CurrentDetection::onOTAFinished()
{
}