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
  lcd.clear();

  char moistureText[20];
  snprintf(moistureText, sizeof(moistureText), "SUCHOSC GLEBY: %d%%", moisture);
  const char *textsArray[] = {"", "", soilCondition, moistureText};

  if (strcmp(textsArray[0], "") != 0 || strcmp(textsArray[1], "") != 0) {
    // If textsArray[0] and textsArray[1] are not empty,
    // the given texts are padded and printed on the LCD.
    // If they are empty, a basic schema for the 1st and 2nd line
    // is executed after an else{} statement.
    lcd.setCursor(0, 0);
    lcd.print(padText(textsArray[0]));

    lcd.setCursor(0, 1);
    lcd.print(padText(textsArray[1]));
  }

  else {

    // To ensure proper name padding:
    // - Enter the flowerName (with a blank space on both sides) for the 1st
    // line.
    // - Enter the numberOfEmotes desired for the 2nd line.
    // - No further modifications are necessary below.
    const char *flowerName = " ALFRED ";
    int numberOfEmotes = 6;

    int flowerNameLength = String(flowerName).length();
    int paddingLen = (20 - flowerNameLength) / 2 - 1;

    for (int i = 0; i <= paddingLen;
         ++i) { // Display straight lines around the flower name
      Display::lcd.setCursor(i, 0);
      Display::lcd.write(byte(3));
    };

    Display::lcd.print(flowerName);

    for (int i = paddingLen + flowerNameLength + 1; i <= 19;
         ++i) { // Display straight lines around the flower name
      Display::lcd.setCursor(i, 0);
      Display::lcd.write(byte(3));
    };

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

    // " -2 " is used to pad empty spaces
    // from both sides of custom chars
    int emotesPaddingLen = (20 - numberOfEmotes - 2) / 2;

    for (int i = 0; i <= emotesPaddingLen;
         ++i) { // Display straight lines around the custom characters
      Display::lcd.setCursor(i, 1);
      Display::lcd.write(byte(3));
    };

    Display::lcd.setCursor(emotesPaddingLen, 1);
    Display::lcd.print(" ");

    for (int i = 0; i < numberOfEmotes; ++i) {
      Display::lcd.write(emote);
    }
    Display::lcd.print(" ");

    for (int i = emotesPaddingLen + numberOfEmotes + 2; i <= 19;
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
