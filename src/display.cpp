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

void printText(bool alfredFeelings, int moisture, const char *soilCondition) {

  char moistureText[20];
  snprintf(moistureText, sizeof(moistureText), "SUCHOSC GLEBY: %d%%", moisture);
  const char *textsArray[] = {"", "", soilCondition, moistureText};

  if (strcmp(textsArray[0], "") != 0 ||
      strcmp(textsArray[1], "") != // Check if the user wants to
          0) {                     // customize the first two lines themselves
    lcd.setCursor(0, 0);
    lcd.print(padText(textsArray[0]));

    lcd.setCursor(0, 1);
    lcd.print(padText(textsArray[1]));
  }

  else {
    for (int i = 0; i <= 5;
         ++i) { // Display first line as decorated flower name
      Display::lcd.setCursor(i, 0);
      Display::lcd.write(byte(3));
    };
    Display::lcd.print(" ALFRED ");
    for (int i = 14; i <= 19; ++i) {
      Display::lcd.setCursor(i, 0);
      Display::lcd.write(byte(3));
    }

    uint8_t emote;

    switch (alfredFeelings) {
      // In addition to basic text, display appropriate custom characters.
      // Depends on moisture level

    case 0: // Sad Alfred
      emote = byte(0);
      break;

    case 1: // Happy Alfred
      emote = byte(2);
      break;
    }
    for (int i = 0; i <= 7;
         ++i) { // Display straight lines around the custom characters
      Display::lcd.setCursor(i, 1);
      Display::lcd.write(byte(3));
    };

    Display::lcd.setCursor(8, 1);
    Display::lcd.print(" ");
    Display::lcd.setCursor(9, 1);
    Display::lcd.write(emote);
    Display::lcd.setCursor(10, 1);
    Display::lcd.write(emote);
    Display::lcd.setCursor(11, 1);
    Display::lcd.print(" ");

    for (int i = 12; i <= 19;
         ++i) { // Display straight lines around the custom characters
      Display::lcd.setCursor(i, 1);
      Display::lcd.write(byte(3));
    };
  }

  lcd.setCursor(0, 2);
  lcd.print(padText(textsArray[2]));

  lcd.setCursor(0, 3);
  lcd.print(padText(textsArray[3]));
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
  lcd.createChar(3, straightLine);
}
} // namespace Display
