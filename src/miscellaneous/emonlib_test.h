// In this example we will use an ADS1115 breakout board instead of the Arduino's local analog inputs
// This is especially useful for nodemcu/esp8266 users who only have a single analog input
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

Adafruit_ADS1115 ads;                  // Create an instance of the ADS1115 object

// Make a callback method for reading the pin value from the ADS instance
int ads1115PinReader(int _pin){
  return ads.readADC_SingleEnded(_pin);
}


void setup()
{  
  Serial.begin(115200);
  
  emon1.inputPinReader = ads1115PinReader; // Replace the default pin reader with the customized ads pin reader
  emon1.current(1, 111.1);             // Current: input pin, calibration.
}

void loop()
{
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  
//   Serial.print(Irms*230.0);	       // Apparent power
//   Serial.print(" ");
//   Serial.println(Irms);		       // Irms
}
