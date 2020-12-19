boolean handling = false;
int currentStep = 0;
int maxStep = 10;

boolean button1pushed = false;
boolean button2pushed = false;
int potentioPercent = 0;

void handleInputs() {
  potentioPercent = ((1024 - analogRead(A1)) / 1024.0) * 100;

  if (button1pushed == false && digitalRead(PIN_BUTTON_SELECT) == 1) {
    button1pushed = true;
  }
  if (button2pushed == false && digitalRead(PIN_BUTTON_CONTROL) == 1) {
    button2pushed = true;
  }
  
  Serial.print("1: ");
  Serial.print(button1pushed);
  Serial.print(" - 2: ");
  Serial.print(button2pushed);
  Serial.print(" - A1: ");
  Serial.print(potentioPercent);
  Serial.println("");
  
  /*
  if (digitalRead(PIN_BUTTON_CONTROL) == LOW && handling == false) {
    handling = true;
    currentStep++;
    if (currentStep > maxStep) {
      currentStep = 1;
    }
    Serial.print("Step ");
    Serial.println(currentStep);
  } else if (digitalRead(PIN_BUTTON_CONTROL) == HIGH && handling == true) {
    handling = false;
  }

  if (currentStep == 1) {
    setCommand();
  }
  */
}

void setCommand() {
  printLcd(0, 0, "Kies effect:    ");  
  int value = analogRead(A0);
  
  if (value < 160) {
    commandId = 1;
  } else if (value >= 180 && value < 340) {
    commandId = 2;
  } else if (value >= 360 && value < 520) {
    commandId = 3;
  } else if (value >= 540 && value < 700) {
    commandId = 4;
  } else if (value >= 720 && value < 880) {
    commandId = 5;
  } else if (value >= 900) {
    commandId = 6;
  } 
  
  if (commandId == 1) {
    printLcd(0, 1, "1. Vast kleur   ");  
  } else if (commandId == 2) {
    printLcd(0, 1, "2. Dégradé      ");  
  } else if (commandId == 3) {
    printLcd(0, 1, "3. Flashing     ");  
  } else if (commandId == 4) {
    printLcd(0, 1, "4. Lopend licht ");  
  } else if (commandId == 5) {
    printLcd(0, 1, "5. Loopregenboog");  
  } else if (commandId == 6) {
    printLcd(0, 1, "6. Vastregenboog");  
  } 
}