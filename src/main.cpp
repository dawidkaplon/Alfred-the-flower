#include <Arduino.h>

#include <display.h>
#include <sensor.h>

int moisture;
bool turnedOn = true;

void turnDevicesOff() {
  Display::displayOff();
  Sensor::sensorOff();
  turnedOn = false;
}

void turnDevicesOn() {
  Display::displayOn();
  Sensor::sensorOn();
  turnedOn = true;
}

void setup()
{
  Serial.begin(9600);
  Display::setup();
  Sensor::setup();
}

void loop() {
  if (turnedOn) {
    moisture = Sensor::readSensor();

    Serial.print("Current soil moisture level: ");
    Serial.println(moisture);

    delay(5000);
  } else {
    Serial.println("Devices are turned off");
  }
}
