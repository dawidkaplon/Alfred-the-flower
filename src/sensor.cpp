#include <Arduino.h>

#define sensorPower 16
#define sensorPin 26

namespace Sensor {
void sensorOn() { digitalWrite(sensorPower, HIGH); }

void sensorOff() { digitalWrite(sensorPower, LOW); }

//  Return the analog soil moisture measurement
int readSensor() {
  sensorOn();
  delay(10);
  int val = analogRead(sensorPin);
  sensorOff();
  Serial.println("Sensor value: " + String(val));
  return val;
}

void setup() {
  pinMode(sensorPower, OUTPUT);
  sensorOff();
}
} // namespace Sensor
