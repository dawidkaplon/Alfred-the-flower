#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace Display {
extern LiquidCrystal_I2C lcd;

void setup();
void printText(bool alfredFeelings, int moisture, const char *soilCondition);
const char *padText(const char *text);
void displayOn();
void displayOff();
} // namespace Display

#endif
