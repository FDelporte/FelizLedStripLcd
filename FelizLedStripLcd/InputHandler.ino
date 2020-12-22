int maxStep = 10;

boolean editMode = false;
boolean confirmActivated = false;
int potentioPercent = 0;
int potentioValue = 0;

void handleInputs() {
  btSelect.loop(); // MUST call the loop() function first
  boolean stateBtPressed = btSelect.isPressed();
  btConfirm.loop();
  boolean stateBtConfirmed = btConfirm.isPressed();

  // Read potentio meter value but avoid toggling
  int newPercent = ((1024 - analogRead(A1)) / 1024.0) * 100;
  int newValue = ((1024 - analogRead(A1)) / 1024.0) * 255;

  if (newPercent == 0 
    || newPercent == 100 
    || newPercent > potentioPercent + 3
    || newPercent < potentioPercent - 3) {
      Serial.print("Changing potentio percent from ");
      Serial.print(potentioPercent);
      Serial.print(" to ");
      Serial.print(newPercent);
      Serial.println("%");
      potentioPercent = newPercent;
  }

  if (newValue == 0
    || newValue == 255
    || newValue > potentioValue + 5
    || newValue < potentioValue - 5) {
      Serial.print("Changing potentio percent from ");
      Serial.print(potentioValue);
      Serial.print(" to ");
      Serial.println(newValue);
      potentioValue = newValue;
  }
    
  if (stateBtPressed) {
    currentStep++;
    if (currentStep > STEP_SPEED) {
      currentStep = STEP_ACTIVE;
      lcdShowActiveStepReset();
    }
    confirmActivated = false;
    editMode = false;
    Serial.println("Back to ACTIVE MODE");
  }
  if (confirmActivated == false && stateBtConfirmed) {
    confirmActivated = true;
  }

  if (currentStep == STEP_EFFECT) {
    selectEffect();
  } else if (currentStep == STEP_R1) {
    selectColor(0);
  } else if (currentStep == STEP_G1) {
    selectColor(1);
  } else if (currentStep == STEP_B1) {
    selectColor(2);
  } else if (currentStep == STEP_R2) {
    selectColor(3);
  } else if (currentStep == STEP_G2) {
    selectColor(4);
  } else if (currentStep == STEP_B2) {
    selectColor(5);
  } else if (currentStep == STEP_SPEED) {
    selectSpeed();
  }
}

void selectEffect() {
  if (!editMode) {
    if (confirmActivated) {
      editMode = true;
      confirmActivated = false;
    } else {
      printLcdLine(0, " Effect kiezen? ");
      printLcdLine(1, "    Klik OK     ");
    }
  } else {
    printLcdLine(0, "  Kies effect   ");
    if (potentioPercent < 15) {
      if (confirmActivated) {
        setEffect(EFFECT_STATIC_COLOR);
      } else {
        printLcdLine(1, " Vast kleur 1   ");  
      }
    } else if (potentioPercent >= 15 && potentioPercent < 30) {
      if (confirmActivated) {
        setEffect(EFFECT_STATIC_FADE);
      } else {
        printLcdLine(1, " Kleur 1 naar 2 ");  
      }
    } else if (potentioPercent >= 30 && potentioPercent < 45) {
      if (confirmActivated) {
        setEffect(EFFECT_BLINKING);
      } else {
        printLcdLine(1, " Flashing 1-2   "); 
      } 
    } else if (potentioPercent >= 45 && potentioPercent < 60) {
      if (confirmActivated) {
        setEffect(EFFECT_RUNNING);
      } else {
        printLcdLine(1, " Looplicht 1-2  ");  
      }
    } else if (potentioPercent >= 60 && potentioPercent < 70) {
      if (confirmActivated) {
        setEffect(EFFECT_RAINBOW_STATIC);
      } else {
        printLcdLine(1, " Vaste regenboog");  
      }
    } else if (potentioPercent >= 70 && potentioPercent < 90) {
      if (confirmActivated) {
        setEffect(EFFECT_RAINBOW_FADING);
      } else {
        printLcdLine(1, " Loop regenboog ");  
      }
    } else if (potentioPercent >= 90) {
      if (confirmActivated) {
        setEffect(EFFECT_THEATER);
      } else {
        printLcdLine(1, " Theater chase  ");  
      }
    } 
  }
}

void setEffect(int effect) {
  selectedEffect = effect;
  confirmActivated = false;
  editMode = false;
  currentStep = STEP_ACTIVE;
  lcdShowActiveStepReset();
}

void selectColor(int index) {
  if (!editMode) {
    if (confirmActivated) {
      editMode = true;
      confirmActivated = false;
    } else {
      printLcdLine(0, "Kleur " + colorLabels[index] + " kiezen?");
      printLcdLine(1, "    Klik OK     ");
      if (index <= 2) {
        setStaticColorByValue(strip.Color(colors[0], colors[1], colors[2]));
      } else {
        setStaticColorByValue(strip.Color(colors[3], colors[4], colors[5]));
      }
    }
  } else {
    printLcdLine(0, "    Kies " + colorLabels[index] + "     ");
    if (confirmActivated) {
      colors[index] = potentioValue;
      confirmActivated = false;
      editMode = false;
    } else {
      printLcdLine(1, "0-255: " + String(potentioValue) + "|" + colors[index]);
      if (index == 0) {
        setStaticColorByValue(strip.Color(potentioValue, colors[1], colors[2]));
      } else if (index == 1) {
        setStaticColorByValue(strip.Color(colors[0], potentioValue, colors[2]));
      } else if (index == 2) {
        setStaticColorByValue(strip.Color(colors[0], colors[1], potentioValue));
      } else if (index == 3) {
        setStaticColorByValue(strip.Color(potentioValue, colors[4], colors[5]));
      } else if (index == 4) {
        setStaticColorByValue(strip.Color(colors[3], potentioValue, colors[5]));
      } else if (index == 5) {
        setStaticColorByValue(strip.Color(colors[3], colors[4], potentioValue));
      }
    }
  }
}

void selectSpeed() {
  if (!editMode) {
    if (confirmActivated) {
      editMode = true;
      confirmActivated = false;
    } else {
      printLcdLine(0, "Snelheid kiezen?");
      printLcdLine(1, "    Klik OK     ");
    }
  } else {
    printLcdLine(0, "Kies snelheid");
    if (confirmActivated) {
      animationSpeedPercent = potentioPercent;
      confirmActivated = false;
      editMode = false;
      currentStep = STEP_ACTIVE;
      lcdShowActiveStepReset();
    } else {
      printLcdLine(1, "0-100: " + String(potentioPercent) + "|" + animationSpeedPercent + "%");
    }
  }
}
