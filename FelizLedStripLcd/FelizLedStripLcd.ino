#include <SPI.h>
#include <Adafruit_NeoPixel.h>

// Install Arduino librariy: Adafruit NeoPixel

// Define the number of LEDS in your strip here
#define PIN_LED 9
#define PIN_BUTTON_SELECT 14
#define PIN_BUTTON_CONTROL 15
#define NUMBER_OF_LEDS 150

#define EFFECT_STATIC_COLOR 1
#define EFFECT_STATIC_FADE 2
#define EFFECT_BLINKING 3
#define EFFECT_RUNNING 4
#define EFFECT_RAINBOW_STATIC 5
#define EFFECT_RAINBOW_FADE 6

#define STEP_ACTIVE 1
#define STEP_EFFECT 2
#define STEP_R1 3
#define STEP_G1 4
#define STEP_B1 5
#define STEP_R2 6
#define STEP_G2 7
#define STEP_B2 8
#define STEP_SPEED 9

// Variables used by the code to handle the incoming LED commands
char input[50];
int incomingByte = 0;

// Variables defined by the incoming LED commands
int selectedEffect = EFFECT_RAINBOW_STATIC;
int animationSpeedPercent = 50;
int colors[6]; // RGB 1 and 2
String colorLabels[6]; // R1, G1,...

int currentStep = STEP_ACTIVE;
int currentLoop = 0;

// LED strip initialization
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_OF_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

// Code executed at startup of the Arduino board
void setup() {
  // Configure serial speed and wait till it is available
  // This is used to output logging info and can receive LED commands
  Serial.begin(9600); 
  
  // Initialize button
  pinMode(PIN_BUTTON_CONTROL, INPUT);
  pinMode(PIN_BUTTON_SELECT, INPUT);
  
  // Initialize the LCD display
  Serial.println("lcd start");
  initLcd();
  printLcdLine(0, " Feliz  Navidad ");
  printLcdLine(1, "  Hallo Feliz!  ");
  Serial.println("lcd end");
  
  // Initialize the LED strip
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
}

void loop() {  
  handleInputs();
  
  // Only do LED effect when in active mode and loop exceeds the defined animationSpeed
  currentLoop++;
  if (currentStep == STEP_ACTIVE) {
    lcdShowActiveStep();

    // Animation speed range is depending on the selected effect
    int animationSpeed = animationSpeedPercent;
    // TODO
  
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
        setFadingRainbow(); 
      } else if (selectedEffect == EFFECT_RAINBOW_FADE) {
        setStaticRainbow(); 
      }
    }

    currentLoop = 0;
  }
  
  delay(10);
}
