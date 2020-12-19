#include <LiquidCrystal_I2C.h>

// Remove Library from Program Files > Arduino
// Create directory LiquidCrystal_I2C in User > Documents > Arduino > libraries
// Download files https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void initLcd() {
  // set up the LCD's number of columns and rows:
  Serial.println("init");
  lcd.begin();
  lcd.backlight();
  lcd.print("test");
  Serial.println("init done");
}

void printLcd(int col, int row, String text) {
  lcd.setCursor(col, row);
  lcd.print(text);
  Serial.print("row/col ");
  Serial.print(row);
  Serial.print("/");
  Serial.print(col);
  Serial.print(": ");
  Serial.println(text);
}
