#include <Arduino.h>

#include <display.h>
#include <motionDetector.h>
#include <sensor.h>

#define greenLed 15
#define redLed 14

int moisture;
int previousMoisture;
int timeDisplayWasTurnedOn = 0;
int alfredFeelings;
bool turnedOn = true;
const char *soilCondition; // E.g. dry enough/too wet

void lightLed() {
  if (alfredFeelings == 0) {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  } else {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  }
}

void turnDevicesOff() {
  Display::displayOff();
  Sensor::sensorOff();
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  turnedOn = false;
}

void turnDevicesOn() {
  Display::displayOn();
  Sensor::sensorOn();
  lightLed();
  turnedOn = true;
}

void setup()
{
  Serial.begin(9600);
  Display::setup();
  Sensor::setup();

  turnDevicesOff(); // Initialize program with devices turned off

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void loop() {

  if (turnedOn) {
    previousMoisture = moisture;
    moisture = float(Sensor::readSensor()) / 10;
    // Approximate moisture level ranges:
    // < 35  = too wet
    // 35-60 = fine
    // > 60  = dry enough to be watered
    if (moisture < 35) {
      alfredFeelings = 0;
      soilCondition = "Jest zbyt mokro!";

    } else if (moisture >= 35 && moisture <= 60) {
      alfredFeelings = 1;
      soilCondition = "Jest idealnie!";

    } else {
      alfredFeelings = 0;
      soilCondition = "Jest zbyt sucho!";
    }

    lightLed();
    if (moisture !=
        previousMoisture) { // Reload LCD text only when the moisture changes
      Display::printText(alfredFeelings, moisture, soilCondition);
    }

    // Wait for n seconds and turn the devices off
    int currentTime = millis();
    if (timeDisplayWasTurnedOn != 0 &&
        currentTime - timeDisplayWasTurnedOn >= 30000) {
      timeDisplayWasTurnedOn = 0;
      turnDevicesOff();
    }

    delay(1000);

  } else {
    if (Detector::isMotionDetected()) {
      turnDevicesOn();
      timeDisplayWasTurnedOn = millis();
    }
    delay(1000);
  }
}
