#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>

// Remove Library from Program Files > Arduino
// Create directory LiquidCrystal_I2C in User > Documents > Arduino > libraries
// Download files https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9
#define NUMBER_OF_LEDS 150
#define PIN_BUTTON_SELECT 14
#define PIN_BUTTON_CONFIRM 15

#define EFFECT_STATIC_COLOR 1
#define EFFECT_STATIC_FADE 2
#define EFFECT_BLINKING 3
#define EFFECT_RUNNING 4
#define EFFECT_RAINBOW_STATIC 5
#define EFFECT_RAINBOW_FADING 6
#define EFFECT_THEATER 7

#define STEP_ACTIVE 1
#define STEP_EFFECT 2
#define STEP_R1 3
#define STEP_G1 4
#define STEP_B1 5
#define STEP_R2 6
#define STEP_G2 7
#define STEP_B2 8
#define STEP_SPEED 9

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// If not sure which address to use, check with File > Examples > Wire > i2c_scanner
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte colors[6]; // RGB 1 and 2
String colorLabels[6]; // R1, G1,...

int selectedEffect = EFFECT_RAINBOW_FADING;
int currentStep = STEP_ACTIVE;
int currentLoop = 0;
int animationSpeedPercent = 50;

ezButton btSelect(PIN_BUTTON_SELECT); 
ezButton btConfirm(PIN_BUTTON_CONFIRM); 

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  colors[0] = 255;  // R1
  colors[1] = 0;    // G1
  colors[2] = 0;    // B1
  colors[3] = 0;    // R2
  colors[4] = 0;    // G2
  colors[5] = 255;  // B2
  colorLabels[0] = "R1";
  colorLabels[1] = "G1";
  colorLabels[2] = "B1";
  colorLabels[3] = "R2";
  colorLabels[4] = "G2";
  colorLabels[5] = "B2";

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  lcd.begin();
  lcd.backlight();
  lcdShowActiveStepReset();

  btSelect.setDebounceTime(100);
  btConfirm.setDebounceTime(100);
}

void loop() {
  handleInputs();
  
  // Only do LED effect when in active mode and loop exceeds the defined animationSpeed
  if (currentStep == STEP_ACTIVE) {
    lcdShowActiveStep();

    // Animation speed range is depending on the selected effect
    int animationSpeed = 100 - animationSpeedPercent;
    if (selectedEffect == EFFECT_RAINBOW_FADING) {
      animationSpeed = ((animationSpeed * 1.0) / 10);
    }
    
    currentLoop++;
    if (currentLoop >= animationSpeed) {
      // Depending on the commandId, call the correct LED effect
      if (selectedEffect == EFFECT_STATIC_COLOR) {
        setStaticColor();
      } else if (selectedEffect == EFFECT_STATIC_FADE) {
        setStaticFade();
      } else if (selectedEffect == EFFECT_BLINKING) {
        setBlinking(); 
      } else if (selectedEffect == EFFECT_RUNNING) {
        setRunningLight(); 
      } else if (selectedEffect == EFFECT_RAINBOW_STATIC) {
        setStaticRainbow(); 
      } else if (selectedEffect == EFFECT_RAINBOW_FADING) {
        setFadingRainbow(); 
      } else if (selectedEffect == EFFECT_THEATER) {
        theaterChaseRainbow(animationSpeed);
      }
      currentLoop = 0;
    }

  }
  
  delay(10);
}
