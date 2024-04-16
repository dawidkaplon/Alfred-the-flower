#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

namespace Sensor {
void setup();
void sensorOn();
void sensorOff();
int readSensor();
} // namespace Sensor

#endif
