/*-----------------------------------------------------------------------------------------------------------
  dbBoardsStrandTestMod.ino

  Summary:
    This program uses examples from the neopixel library as paintbrushes for the exposure wand. By clicking
    the button the user can control when each example starts for well timed long exposure shots.
  
  Utilizing:
    Adafruit NeoPixel Library: https://github.com/adafruit/Adafruit_NeoPixel
    
  Programmer:
    Duncan Brandt @ DB Boards, LLC
    Created: Jan 19, 2018
  
  Development Environment Specifics:
    Arduino 1.6.11
  
  Hardware Specifications:
    DB Boards 50 pixel LED Strip, DB7003
    Arduino Drawing Board (UNO) DB1000
    Soft Push Button DB7004

  Beerware License:
    This program is free, open source, and public domain. The program is distributed as is and is not
    guaranteed. However, if you like the code and find it useful I would happily take a beer should you 
    ever catch me at the local.
*///---------------------------------------------------------------------------------------------------------

#include <Adafruit_NeoPixel.h>                      // https://github.com/adafruit/Adafruit_NeoPixel
#define PIN 1                                       // Pin 1 (tx) for serial communication with LED strip
// 50  Number of pixels in strip, NEO_GRB  Pixels are wired for GRB bitstream, NEO_KHZ800  800 KHz bitstream
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_GRB + NEO_KHZ800);
int btn = 6;                                        // Button pin is D6
//-----------------------------------------------------------------------------------------------------------
void setup() {                                      // The setup program ones only once after power-up or reset
  strip.begin();                                    // Activate the LED strand
  strip.show();                                     // Initialize all pixels to 'off'
  strip.setBrightness(30);                          // Affects the brightness of the entire program (0-255)
  pinMode(btn, INPUT_PULLUP);                       // Setup pin for raw button
}
//-----------------------------------------------------------------------------------------------------------
void loop() {                                       // Loop runs several examples on button release
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  colorWipe(strip.Color(255, 0, 0), 50);            // Red
  colorWipe(strip.Color(0, 255, 0), 50);            // Green
  colorWipe(strip.Color(0, 0, 255), 50);            // Blue
  clearStrip();                                     // Turn all LEDs off
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  theaterChase(strip.Color(127, 127, 127), 50);     // White
  theaterChase(strip.Color(127, 0, 0), 50);         // Red
  theaterChase(strip.Color(0, 0, 127), 50);         // Blue
  clearStrip();                                     // Turn all LEDs off
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  rainbow(20);                                      // Rolls through entire spectrum slowly
  clearStrip();                                     // Turn all LEDs off
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  rainbowCycle(20);                                 // Rolls entire spectrum on strip
  clearStrip();                                     // Turn all LEDs off
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  theaterChaseRainbow(50);                          // Theater chase with all the colors
  clearStrip();                                     // Turn all LEDs off
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  blueGreen();                                      // Draws a long blue green striped ribbon
}
//-----------------------------------------------------------------------------------------------------------
void clearStrip(){                                  // Clear entire strip
  for(int i = 0; i < 50; i++){                      // Step through every LED
    strip.setPixelColor(i, strip.Color(0,0,0));     // Turn each LED off
  }
  strip.show();                                     // Update strip
}
//-----------------------------------------------------------------------------------------------------------

// Examples from the library example sketch
// Switch all LEDS between blue and green and ribbon the ends
void blueGreen(){
  for(int a = 0; a < 25; a++){
    strip.setPixelColor(a, strip.Color(0,255,0));
    strip.setPixelColor(50-a, strip.Color(0,255,0));
    strip.show();
    delay(4);
  }
  for(int b = 0; b < 80; b++){
    for(int c = 0; c < 50; c++){
      strip.setPixelColor(c, strip.Color(0,0,255));
    }
    strip.show();
    delay(100);
    for(int d = 0; d < 50; d++){
      strip.setPixelColor(d, strip.Color(0,255,0));
    }
    strip.show();
    delay(100);
  }
  for(int e = 0; e < 50; e++){
      strip.setPixelColor(e, strip.Color(0,0,255));
    }
  for(int f = 25; f >= 0; f--){
    strip.setPixelColor(f, strip.Color(0,0,0));
    strip.setPixelColor(50-f, strip.Color(0,0,0));
    strip.show();
    delay(4);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
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
