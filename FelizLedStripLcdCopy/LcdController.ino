#include <LiquidCrystal_I2C.h>

// Remove Library from Program Files > Arduino
// Create directory LiquidCrystal_I2C in User > Documents > Arduino > libraries
// Download files https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// If not sure which address to use, check with File > Examples > Wire > i2c_scanner
LiquidCrystal_I2C lcd(0x27, 16, 2);

String lines[2];
 
void initLcd() {
  lcd.begin();
  lcd.backlight();
}

void printLcdLine(int row, String text) {
  if (lines[row] == text) {
    return;
  }
  
  // Remember last line so we don't refresh the LCD when not needed
  lines[row] = text;

  // Clear the line so no leftovers from previous one stay when the text is not 16 chars
  lcd.setCursor(0, row);
  lcd.print("                ");

  // Show the given text
  lcd.setCursor(0, row);
  lcd.print(text);

  // Debug info
  /*Serial.print("row ");
  Serial.print(row);
  Serial.print(": ");
  Serial.println(text);*/
}
