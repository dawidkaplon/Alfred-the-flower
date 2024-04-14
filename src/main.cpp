#include <Arduino.h>

#include <display.h>
#include <sensor.h>

#define greenLed 15
#define redLed 14

int moisture;
bool turnedOn = true;
bool alfredFeelings;
const char *soilCondition; // e.g. dry enough/too wet

void turnDevicesOff() {
  Display::displayOff();
  Sensor::sensorOff();
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
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

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void loop() {
  if (turnedOn) {
    moisture = float(Sensor::readSensor()) / 10;
    // Approximate moisture level ranges:
    // < 35 = too wet
    // 35-60 = fine
    // > 60 = dry enough to be watered

    Serial.print("Current soil moisture level: ");
    Serial.println(moisture);

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

    Display::printText("***** ALFRED *****", "", soilCondition,
                       ("Poziom suchosci: " + String(moisture) + "%").c_str());

    Display::lcd.setCursor(8, 1);

    switch (alfredFeelings) {
    case 0: // Sad Alfred
      Display::lcd.write(byte(0));
      Display::lcd.print("  ");
      Display::lcd.write(byte(0));

      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, HIGH);
      break;

    case 1: // Happy Alfred
      Display::lcd.write(byte(2));
      Display::lcd.print("  ");
      Display::lcd.write(byte(2));

      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      break;
    }

    delay(20000);
  } else {
    Serial.println("Devices are turned off");
  }
}
