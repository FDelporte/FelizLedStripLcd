// Using some effects from the AdaFruit NeoPixel strandtest_wheel example
int currentAction = 0;

void initLeds() {
  strip.begin();
  strip.setBrightness(100);
  strip.clear();
  strip.show(); // Initialize all pixels to 'off'
}

void clearLeds() {
  Serial.println("Clearing strip");
  strip.clear(); 
  strip.show();
}

uint32_t getRGB1() {
  return strip.Color(colors[0], colors[1], colors[2]);
}

uint32_t getRGB2() {
  return strip.Color(colors[3], colors[4], colors[5]);
}

void setStaticColor() {
  setStaticColorByValue(getRGB1());
}

void setStaticColorByValue(uint32_t rgb) {
  Serial.print("Static color: ");
  Serial.println(rgb);
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, rgb);
  }
  strip.show();
}

void setStaticFade() {  
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, getGradientColor(i));
  }
  strip.show();
}

void setBlinking() {  
  for(uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, currentAction == 1 ? getRGB1() : getRGB2());
  }
  strip.show();
  currentAction++;
  if (currentAction > 2) {
    currentAction = 1;
  }
}

void setRunningLight() {  
  if (currentAction >= NUMBER_OF_LEDS) {    
    currentAction = 0;    
  }
  
  // Show color 1
  strip.setPixelColor(currentAction, getRGB1());
  strip.show(); 

  // Reset to color 2 for next loop
  strip.setPixelColor(currentAction, getRGB2());
  
  currentAction++;
}

void setFadingRainbow() {
  if (currentAction > 255) {
    currentAction = 0;
  }
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, getWheelColor((i * 1 + currentAction) & 255));
  }
  strip.show();
  currentAction++;
}

void setStaticRainbow() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, getWheelColor((255 / strip.numPixels()) * i));
  }
  strip.show();
  Serial.println("Static rainbow set");
}


// Theater effect
int theaterColorCounter = 0;
int theaterLedCounter = 0;
void theaterChaseRainbow(uint8_t wait) {
  // cycle all 256 colors in the wheel
  if (theaterColorCounter > 255) {
    theaterColorCounter = 0;
  }
  if (theaterLedCounter >= 3) {
    theaterLedCounter = 0;
  }
  strip.clear(); 
  for (uint16_t i=theaterLedCounter; i < strip.numPixels(); i=i+3) {
    // turn every third pixel on
    strip.setPixelColor(i, Wheel((i+theaterColorCounter) % 255));   
  }
  strip.show();
  theaterColorCounter++;
  theaterLedCounter++;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Calculate a gradient color between color 1 and 2, for the given position
uint32_t getGradientColor(uint16_t pos) {
  float factor = (pos * 1.0) / strip.numPixels();
  return strip.Color(
    (factor * colors[3]) + ((1 - factor) * colors[0]),
    (factor * colors[4]) + ((1 - factor) * colors[1]),
    (factor * colors[5]) + ((1 - factor) * colors[2])
   );
}

// Pos from 0 to 255 to get colors from full color wheel
// 0 - 85:    G - R
// 85 - 170:  R - B
// 170 - 255: B - G
uint32_t getWheelColor(byte pos) {
  if (pos < 85) {
    return strip.Color(pos * 3, 255 - pos * 3, 0);
  } else if (pos < 170) {
    pos -= 85;
    return strip.Color(255 - pos * 3, 0, pos * 3);
  } else {
    pos -= 170;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  }
}
