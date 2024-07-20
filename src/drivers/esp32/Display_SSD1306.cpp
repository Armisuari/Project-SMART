#include "Display_SSD1306.h"

bool Display_SSD1306::init()
{
  // My OLED I2C address is 0x3C
  if (!_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    return false;
  }

  _oled.setTextColor(SSD1306_WHITE);

  _oled.clearDisplay();
  _oled.setCursor(50, 1);
  _oled.println("SMART");
  _oled.setCursor(5, 10);
  _oled.println("Sistem Monitor Arus");
  _oled.setCursor(5, 20);
  _oled.println("RELE Tidak Seimbang");
  delay(2000);

  _oled.display();

  return true;
}

bool Display_SSD1306::setCurrentValue(float value0, float value1)
{
  _currentValue0 = value0;
  _currentValue1 = value1;
  refreshDisplay();
  return true;
}

bool Display_SSD1306::setConnectionStatus(bool connected)
{
  _connectionStatus = connected;
  refreshDisplay();
  return true;
}

bool Display_SSD1306::setDatetimeValue(std::string datetimeStr)
{
  _datetimeStr = datetimeStr;
  refreshDisplay();
  return true;
}

bool Display_SSD1306::setAlarmEvent(bool state)
{
  _alarmState = state;
  refreshDisplay();
  return true;
}

void Display_SSD1306::drawTimeIcon()
{
  // Draw clock face (circle)
  _oled.drawCircle(11, 4, 4, WHITE);

  // Draw hour hand
  _oled.drawLine(11, 4, 8, 8, WHITE);

  // // Draw minute hand
  _oled.drawLine(11, 4, 10, 6, WHITE);
}

void Display_SSD1306::refreshDisplay()
{
  _oled.clearDisplay();
  _oled.setCursor(23, 1);
  _oled.printf("%s\r\n", _datetimeStr.c_str());
  drawTimeIcon();

  // if (!_ctConnection)
  // {
  //   _oled.setCursor(20, 12);
  //   _oled.println("CT disconnected");
  // }
  // else
  // {
    _oled.setCursor(2, 12);
    _oled.printf("Irms: %.2f A | %.2f A\r\n", _currentValue0, _currentValue1);
  // }

  if (!_connectionStatus)
  {
    _oled.setCursor(8, 23);
    _oled.println("WiFi : disconnected");
  }
  else
  {
    _oled.setCursor(14, 23);
    _oled.println("WiFi : connected");
  }

  blinkText();
  _oled.display();
}

void Display_SSD1306::blinkText()
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  static bool visible = true;
  const unsigned long blinkInterval = 500; // Adjust blink interval (in milliseconds)

  if (_alarmState)
  {
    if (currentMillis - previousMillis >= blinkInterval)
    {
      previousMillis = currentMillis;
      visible = !visible; // Toggle visibility
      if (visible)
      {
        _oled.clearDisplay();
        _oled.setCursor(13, 23);
        _oled.println("Alarm: Activated !");
        // _oled.display(); // Display the text
      }
    }
  }
}

bool Display_SSD1306::setCTconnection(bool conn)
{
  _ctConnection = conn;
  refreshDisplay();
  return true;
}