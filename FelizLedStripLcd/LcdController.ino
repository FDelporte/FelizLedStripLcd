#include <LiquidCrystal_I2C.h>

// Remove Library from Program Files > Arduino
// Create directory LiquidCrystal_I2C in User > Documents > Arduino > libraries
// Download files https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

String lines[2];
 
void initLcd() {
  // set up the LCD's number of columns and rows:
  Serial.println("init");
  lcd.begin();
  lcd.backlight();
  lcd.print("test");
  Serial.println("init done");
}

void printLcdLine(int row, String text) {
  if (lines[row] == text) {
    return;
  }
  
  // Remember last line so we don't refresh the LCD when not needed
  lines[row] = text;
  
  lcd.setCursor(0, row);
  lcd.print(text);
  
  Serial.print("row ");
  Serial.print(row);
  Serial.print(": ");
  Serial.println(text);
}
