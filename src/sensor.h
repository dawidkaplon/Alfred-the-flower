#ifndef SENSOR
#define SENSOR

#include <Arduino.h>

namespace Sensor {
void setup();
void sensorOn();
void sensorOff();
int readSensor();
} // namespace Sensor

#endif
