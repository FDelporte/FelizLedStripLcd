
#define DISPLAY_DURATION 3000

int activeStepLabelStep = 0;
int activeStepLabelLoop = 0;

void lcdShowActiveStep() {
  activeStepLabelLoop++;

  if (activeStepLabelLoop > DISPLAY_DURATION) {
    activeStepLabelStep++;
    
    if (activeStepLabelStep > 3) {
      activeStepLabelStep = 0;
    }
  
    if (activeStepLabelStep == 0) {
      printLcdLine(0, "Effect:         ");
      if (selectedEffect == EFFECT_STATIC_COLOR) {
        printLcdLine(0, " Vast kleur     ");
      } else if (selectedEffect == EFFECT_STATIC_FADE) {
        printLcdLine(1, " Dégradé        ");  
      } else if (selectedEffect == EFFECT_BLINKING) {
        printLcdLine(1, " Flashing      "); 
      } else if (selectedEffect == EFFECT_RUNNING) {
        printLcdLine(1, " Lopend licht  ");  
      } else if (selectedEffect == EFFECT_RAINBOW_STATIC) {
        printLcdLine(1, " Vast regenboog");  
      } else if (selectedEffect == EFFECT_RAINBOW_FADE) {
        printLcdLine(1, " Loop regenboog"); 
      }
    } else if (activeStepLabelStep == 1) {
      printLcdLine(0, "Kleur 1:        ");
      printLcdLine(1, "R" + String(colors[0]) + " G" + String(colors[1]) + " B" + String(colors[2]));
    } else if (activeStepLabelStep == 2) {
      printLcdLine(0, "Kleur 2:        ");
      printLcdLine(1, "R" + String(colors[3]) + " G" + String(colors[4]) + " B" + String(colors[5]));
    } else if (activeStepLabelStep == 3) {
      printLcdLine(0, "Snelheid:       ");
      printLcdLine(1, String(animationSpeedPercent) + "%");
    }
  }
}
