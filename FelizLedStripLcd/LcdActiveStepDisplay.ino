#define DISPLAY_DURATION 300

int activeStepLabelStep = 0;
int activeStepLabelLoop = 0;

String lines[2];

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
}

void lcdShowActiveStepReset() {
  activeStepLabelStep = 0;
  activeStepLabelLoop = DISPLAY_DURATION; // Immediately show first screen
}

void lcdShowActiveStep() {
  activeStepLabelLoop++;

  if (activeStepLabelLoop >= DISPLAY_DURATION) {
    activeStepLabelLoop = 0;
    
    if (activeStepLabelStep > 4) {
      activeStepLabelStep = 0;
    }
  
    if (activeStepLabelStep == 0) {
      printLcdLine(0, " Feliz  Navidad ");
      printLcdLine(1, "  Hallo Feliz!  ");
    } else if (activeStepLabelStep == 1) {
      printLcdLine(0, "Effect:         ");
      if (selectedEffect == EFFECT_STATIC_COLOR) {
        printLcdLine(1, " Vast kleur 1   ");
      } else if (selectedEffect == EFFECT_STATIC_FADE) {
        printLcdLine(1, " Kleur 1 naar 2 ");  
      } else if (selectedEffect == EFFECT_BLINKING) {
        printLcdLine(1, " Flashing 1-2   "); 
      } else if (selectedEffect == EFFECT_RUNNING) {
        printLcdLine(1, " Looplicht 1-2  ");  
      } else if (selectedEffect == EFFECT_RAINBOW_STATIC) {
        printLcdLine(1, " Vaste regenboog");  
      } else if (selectedEffect == EFFECT_RAINBOW_FADING) {
        printLcdLine(1, " Fadingregenboog"); 
      } else if (selectedEffect == EFFECT_THEATER) {
        printLcdLine(1, " Theater chase  "); 
      }
    } else if (activeStepLabelStep == 2) {
      printLcdLine(0, "Kleur 1:        ");
      printLcdLine(1, "R" + String(colors[0]) + " G" + String(colors[1]) + " B" + String(colors[2]));
    } else if (activeStepLabelStep == 3) {
      printLcdLine(0, "Kleur 2:        ");
      printLcdLine(1, "R" + String(colors[3]) + " G" + String(colors[4]) + " B" + String(colors[5]));
    } else if (activeStepLabelStep == 4) {
      printLcdLine(0, "Snelheid: " + String(animationSpeedPercent) + "%");
      printLcdLine(1, "                ");
    }

    activeStepLabelStep++;
  }
}
