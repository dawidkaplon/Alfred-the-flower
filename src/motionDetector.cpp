#include <Arduino.h>

#define detectorPin 17

int pinStateCurrent = LOW;
int pinStatePrevious = LOW;

namespace Detector {
void setup() {
  Serial.begin(9600);
  pinMode(detectorPin, INPUT_PULLDOWN);
}

bool isMotionDetected() {
  pinStatePrevious = pinStateCurrent;         // store old state
  pinStateCurrent = digitalRead(detectorPin); // read new state

  if (pinStateCurrent == HIGH) {
    // Motion was detected
    return true;
  }
  return false;
}
} // namespace Detector
