int maxStep = 10;

boolean editMode = false;
boolean button1activated = false;
boolean button2activated = false;
int potentioPercent = 0;
int potentioValue = 0;

void handleInputs() {
  potentioPercent = ((1024 - analogRead(A1)) / 1024.0) * 100;
  potentioValue = ((1024 - analogRead(A1)) / 1024.0) * 255;

  if (button1activated == false && digitalRead(PIN_BUTTON_SELECT) == 1) {
    button1activated = true;
  }
  if (button2activated == false && digitalRead(PIN_BUTTON_CONTROL) == 1) {
    button2activated = true;
  }

  /*
  Serial.print("1: ");
  Serial.print(button1activated);
  Serial.print(" - 2: ");
  Serial.print(button2activated);
  Serial.print(" - A1: ");
  Serial.print(potentioPercent);
  Serial.print("/");
  Serial.print(potentioValue);
  Serial.println("");
  */
  
  if (button1activated) {
    currentStep++;
    if (currentStep > STEP_SPEED) {
      currentStep == STEP_ACTIVE;
    }
    button1activated = false;
    button2activated = false;
    editMode = false;
    Serial.println("Back to ACTIVE MODE");
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
    if (button2activated) {
      editMode = true;
      button2activated = false;
    } else {
      printLcdLine(0, " Effect kiezen? ");
      printLcdLine(1, "    Klik OK     ");
    }
  } else {
    printLcdLine(0, "  Kies effect   ");
    if (potentioPercent < 15) {
      if (button2activated) {
        setEffect(EFFECT_STATIC_COLOR);
      } else {
        printLcdLine(1, "1. Vast kleur   ");  
      }
    } else if (potentioPercent >= 15 && potentioPercent < 30) {
      if (button2activated) {
        setEffect(EFFECT_STATIC_FADE);
      } else {
        printLcdLine(1, "2. Dégradé      ");  
      }
    } else if (potentioPercent >= 30 && potentioPercent < 45) {
      if (button2activated) {
        setEffect(EFFECT_BLINKING);
      } else {
        printLcdLine(1, "3. Flashing     "); 
      } 
    } else if (potentioPercent >= 45 && potentioPercent < 60) {
      if (button2activated) {
        setEffect(EFFECT_RUNNING);
      } else {
        printLcdLine(1, "4. Lopend licht ");  
      }
    } else if (potentioPercent >= 60 && potentioPercent < 75) {
      if (button2activated) {
        setEffect(EFFECT_RAINBOW_STATIC);
      } else {
        printLcdLine(1, "5. Vastregenboog");  
      }
    } else if (potentioPercent >= 75 && potentioPercent < 30) {
      if (button2activated) {
        setEffect(EFFECT_RAINBOW_FADE);
      } else {
        printLcdLine(1, "6. Loopregenboog");  
      }
    } 
  }
}

void setEffect(int effect) {
  selectedEffect = effect;
  button2activated = false;
  editMode = false;
  currentStep = STEP_ACTIVE;
}

void selectColor(int index) {
  if (!editMode) {
    if (button2activated) {
      editMode = true;
      button2activated = false;
    } else {
      printLcdLine(0, "Kleur " + colorLabels[index] + " kiezen?");
      printLcdLine(1, "    Klik OK     ");
    }
  } else {
    printLcdLine(0, "    Kies " + colorLabels[index] + "     ");
    if (button2activated) {
      colors[index] = potentioValue;
      button2activated = false;
      editMode = false;
    } else {
      printLcdLine(1, "0-255: " + String(potentioValue));
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
    if (button2activated) {
      editMode = true;
      button2activated = false;
    } else {
      printLcdLine(0, "Snelheid kiezen?");
      printLcdLine(1, "    Klik OK     ");
    }
  } else {
    printLcdLine(0, "Kies snelheid");
    if (button2activated) {
      animationSpeedPercent = potentioPercent;
      button2activated = false;
      editMode = false;
    } else {
      printLcdLine(1, "0-100: " + String(potentioPercent) + "%");
    }
  }
}
