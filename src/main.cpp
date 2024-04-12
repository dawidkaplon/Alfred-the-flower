#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char array1[] = "     RASPBERRY     ";
char array2[] = "      PI PICO      ";
char array3[] = "      TESTING      ";
char array4[] = "        :-)        ";    

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  lcd.print(array1);                // BY DEFAULT CURSOR IS SET AT 0,0, i.e. 0th ROW AND 0th COLUMN
  
  lcd.setCursor(0,1);
  lcd.print(array2);
  
  lcd.setCursor(0,2);
  lcd.print(array3);
  
  lcd.setCursor(0,3);
  lcd.print(array4);
}

void loop(){
  
}
