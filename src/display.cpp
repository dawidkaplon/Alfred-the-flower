#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

namespace Display {
LiquidCrystal_I2C lcd(0x27, 20, 4);

void printText(const char *line0, const char *line1, const char *line2,
               const char *line3) {
  lcd.print(line0); // Cursor is set at (0,0) i.e. row0 col0 at the beginning

  lcd.setCursor(0, 1);
  lcd.print(line1);

  lcd.setCursor(0, 2);
  lcd.print(line2);

  lcd.setCursor(0, 3);
  lcd.print(line3);
}

void displayOn() { lcd.noDisplay(); }

void displayOff() { lcd.display(); }

void setup() {
  lcd.init();
  lcd.backlight();
  printText("Alfred", "", "", "");
}
} // namespace Display
