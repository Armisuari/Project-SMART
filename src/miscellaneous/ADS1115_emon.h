#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

const float FACTOR = 30; //20A/1V from teh CT

const float multiplier = 0.00005;

float getcurrent();

void setup() {
  Serial.begin(115200);

//   ads.setGain(GAIN_FOUR);      // +/- 1.024V 1bit = 0.5mV
//   ads.setGain(GAIN_TWOTHIRDS);      // +/- 1.024V 1bit = 0.5mV
  ads.setGain(GAIN_ONE);      // +/- 1.024V 1bit = 0.5mV
//   ads.setGain(GAIN_EIGHT);      // +/- 1.024V 1bit = 0.5mV
//   ads.setGain(GAIN_SIXTEEN);      // +/- 1.024V 1bit = 0.5mV
  ads.begin();

}

void printMeasure(String prefix, float value, String postfix)
{
  Serial.print(prefix);
  Serial.print(value, 3);
  Serial.println(postfix);
}

void loop() {
  float currentRMS = getcurrent();

  printMeasure("Irms: ", currentRMS, "A");
  printMeasure("Power: ", currentRMS*223.0, "W");
  delay(1000);

}

float getcurrent()
{
  float voltage;
  float current;
  float sum = 0;
  long time_check = millis();
  int counter = 0;

  while (millis() - time_check < 1000)
  {
    voltage = ads.readADC_Differential_0_1() * multiplier;
    current = voltage * FACTOR;
    //current /= 1000.0;

    sum += sq(current);
    counter = counter + 1;
  }

  current = sqrt(sum / counter);
  return (current*10.0);
}