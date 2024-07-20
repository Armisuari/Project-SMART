#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>
#include <interfaces/DisplayInterface.h>

class Display_SSD1306 : public DisplayInterface
{

public:
  bool init();
  bool setCurrentValue(float value0, float value1);
  bool setConnectionStatus(bool connected);
  bool setDatetimeValue(std::string datetimeStr);
  bool setAlarmEvent(bool state);
  bool setCTconnection(bool conn);

private:
  Adafruit_SSD1306 _oled{128, 32, &Wire, -1};
  float _currentValue0 = 0;
  float _currentValue1 = 0;
  bool _connectionStatus = false;
  std::string _datetimeStr;
  bool _alarmState = false;
  bool _ctConnection;

  void refreshDisplay();
  void drawTimeIcon();
  void blinkText();
};