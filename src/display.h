#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace Display {
extern LiquidCrystal_I2C lcd;

void setup();
void printText(const char *line0, const char *line1, const char *line2,
               const char *line3);
const char *padText(const char *text);
void displayOn();
void displayOff();
} // namespace Display

#endif
