// #include "miscellaneous/I2C_Scanner.h"
// #include "miscellaneous/emonlib_test.h"
// #include "miscellaneous/ADS1115_emon.h"

#include <Arduino.h>
#include <WiFi.h>

#include <CurrentDetection.h>
#include <drivers/esp32/CurrentMeter_ADS.h>

// TODO: Add autoformatter for a consistent coding style.
// Feature proposal:
// * Settings store to the storage including timezone info.
// and create timeFormatter(uint32_t unixtime) to follow timezone, for unit
// testing purpose. Edge cases: +- UTC, UTC+24 +36,
// * Download OpenWeather JSON and parse, for unit testing.
// * Settings in JSON, for unit testing.
// * Configuration via UART (or via WebUI for paid content), can be unit tested
// *
CurrentMeter_ADS currentMeter;

CurrentDetection cd(currentMeter, &Serial);

uint32_t meterLastUpdated = 0;

void setup() {
  Serial.begin(115200);

  cd.init();

  Serial.println("Current Detection Initialized.");

  meterLastUpdated = millis();
}

void loop() {
//   if (millis() - meterLastUpdated >= ws._cfg.getInterval()) {
  if (millis() - meterLastUpdated >= 500U) {
    meterLastUpdated = millis();
    cd.updateMeterData();
  }

//   ws.checkSerialConfig();
}
