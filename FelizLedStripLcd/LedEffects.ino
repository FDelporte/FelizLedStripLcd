int currentAction = 0;

void initLeds() {
  strip.begin();
  strip.setBrightness(100);
  strip.clear();
  strip.show(); // Initialize all pixels to 'off'
}

void clearLeds() {
  strip.clear(); 
  strip.show();
}

int getRGB1() {
  return strip.Color(colors[0], colors[1], colors[2]);
}

int getRGB2() {
  return strip.Color(colors[3], colors[4], colors[5]);
}

void setStaticColor() {
  setStaticColorByValue(getRGB1());
}

void setStaticColorByValue(int rgb) {
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
}

// Calculate a gradient color between color 1 and 2, for the given position
uint32_t getGradientColor(uint16_t pos) {
  float factor = ((float) pos / (float) (strip.numPixels() - 1));
  
  byte r1 = (colors[0] & 0xFF0000) >> 16;
  byte g1 = (colors[1] & 0x00FF00) >> 8;
  byte b1 = (colors[2] & 0x0000FF);

  byte r2 = (colors[3] & 0xFF0000) >> 16;
  byte g2 = (colors[4] & 0x00FF00) >> 8;
  byte b2 = (colors[5] & 0x0000FF);

  byte r = (factor * r2) + ((1 - factor) * r1);
  byte g = (factor * g2) + ((1 - factor) * g1);
  byte b = (factor * b2) + ((1 - factor) * b1);

  uint32_t rt = strip.Color(r, g, b);
  
  return rt;
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
