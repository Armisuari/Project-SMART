
// #define TEST

#ifdef TEST
// #include "miscellaneous/I2C_Scanner.h"
// #include "miscellaneous/emonlib_test.h"
// #include "miscellaneous/ADS1115_emon.h"
// #include "miscellaneous/ADS_test.h"
// #include "miscellaneous/St7789_test.h"
#include "miscellaneous/ssd1306_test.h"
// #include "miscellaneous/buzzer_test.h"
// #include "miscellaneous/telegram_test.h"

#else
#include <Arduino.h>
#include <WifiHandler.h>

#include <CurrentDetection.h>
#include <drivers/esp32/CurrentMeter_ADS.h>
#include <drivers/esp32/Display_SSD1306.h>
#include <drivers/esp32/Time_NTP.h>
#include <drivers/esp32/Storage_LittleFS.h>
#include <drivers/esp32/Alarm_Buzzer.h>
#include <drivers/esp32/Alarm_Telegram.h>

CurrentMeter_ADS currentMeter;
Display_SSD1306 ssd1306;
Time_NTP ntp;
Storage_LittleFS lfs;
Alarm_Buzzer buzzer;
Alarm_Telegram telegram;

WifiHandler wifi{"GI.TALISE", "12345678"}; //Merubah setting wifi

CurrentDetection cd(currentMeter, ntp, ssd1306, &Serial, lfs, buzzer, telegram);

uint32_t meterLastUpdated = 0;

float thresHold = 30; //A | Merubah nilai batas arus

void setup()
{
  Serial.begin(115200);
  wifi.init();
  cd.init(thresHold);
  Serial.println("Current Detection Initialized.");
  vTaskDelay(1000);
  meterLastUpdated = millis();
}

void loop()
{
  if (millis() - meterLastUpdated >= cd._cfg.getInterval())
  {
    meterLastUpdated = millis();
    cd.updateMeterData();
    cd.update_wifi_connection();
    cd.setAlarmEvent(true, true);
  }

  // cd.checkSerialConfig();
}

#endif
