#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <characters.h>

namespace Display {
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char *padText(const char *text) {
  String result = text;
  int textLen = strlen(text);
  int paddingLen = (20 - textLen) / 2;

  for (int i = 0; i < paddingLen; i++) {
    result = " " + result;
  }

  return result.c_str();
}

void printText(const char *line0, const char *line1, const char *line2,
               const char *line3) {
  lcd.setCursor(0, 0);
  lcd.print(padText(line0));

  lcd.setCursor(0, 1);
  lcd.print(padText(line1));

  lcd.setCursor(0, 2);
  lcd.print(padText(line2));

  lcd.setCursor(0, 3);
  lcd.print(padText(line3));
}

void displayOn() { lcd.backlight(); }

void displayOff() { lcd.noBacklight(); }

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, sadFace);
  lcd.createChar(1, happyFace);
  lcd.createChar(2, heart);
}
} // namespace Display
