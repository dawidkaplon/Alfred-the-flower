#include <Arduino.h>

#include <display.h>
#include <motionDetector.h>
#include <sensor.h>

#define greenLed 15
#define redLed 14
#define buzzerPin 28

int moisture;
int previousMoisture;
int timeDisplayWasTurnedOn = 0;
int alfredFeelings;
bool running = true;
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

void beepBuzzer() { tone(buzzerPin, 2000, 10); }

void turnDevicesOff() {
  Display::displayOff();
  Sensor::sensorOff();
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  running = false;
}

void turnDevicesOn() {
  Display::displayOn();
  Sensor::sensorOn();
  lightLed();
  running = true;
}

void setup()
{
  Serial.begin(9600);
  Display::setup();
  Sensor::setup();

  turnDevicesOff(); // Initialize program with devices turned off

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  if (running) {
    previousMoisture = moisture;
    moisture = float(Sensor::readSensor()) / 10;
    // Approximate moisture level ranges:
    // < 35  = too wet
    // 35-60 = fine
    // > 60  = dry enough to be watered
    if (moisture < 35) {
      alfredFeelings = 0;
      soilCondition = "Jest zbyt mokro!";
      beepBuzzer();

    } else if (moisture >= 35 && moisture <= 60) {
      alfredFeelings = 1;
      soilCondition = "Jest idealnie!";

    } else {
      alfredFeelings = 0;
      soilCondition = "Jest zbyt sucho!";
      beepBuzzer();
    }

    lightLed();

    // Reload LCD text only when the moisture changes
    if (moisture != previousMoisture) {
      Display::printText(alfredFeelings, moisture, soilCondition);
      timeDisplayWasTurnedOn = millis();
    }

    if (Detector::isMotionDetected()) {  // Do not turn off devices as long as
      timeDisplayWasTurnedOn = millis(); // there is the motion around the LCD
    }

    // Wait for n seconds and turn the devices off
    int currentTime = millis();
    if (timeDisplayWasTurnedOn != 0 &&
        currentTime - timeDisplayWasTurnedOn >= 10000) {
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
