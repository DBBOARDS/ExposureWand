/*-----------------------------------------------------------------------------------------------------------
  dbBoardsHiddenMessages.ino

  Summary:
    This program uses the a simple upper-case library of 5x4 pixel letters to draw out text for long 
    exposure shots. The text does not begin to fire until the user releases the button.
  
  Utilizing:
    Adafruit NeoPixel Library: https://github.com/adafruit/Adafruit_NeoPixel
    
  Programmer:
    Duncan Brandt @ DB Boards, LLC
    Created: Jan 19, 2018
  
  Development Environment Specifics:
    Arduino 1.6.11
  
  Hardware Specifications:
    DB Boards 5 pixel LED Strip, DB7000
    Arduino Drawing Board (UNO) DB1000
    Soft Push Button DB7004

  Beerware License:
    This program is free, open source, and public domain. The program is distributed as is and is not
    guaranteed. However, if you like the code and find it useful I would happily take a beer should you 
    ever catch me at the local.
*///---------------------------------------------------------------------------------------------------------
// Create the text strings you wish to use in your exposure here
const String exposureText = "abcdefghijklmnopqrstuvwxyz. -";
const String exposureText2 = "Come visit us at";
const String exposureText3 = "dbboards.com";

// This is the simple 5x4 pixel alphabet represented as hex recorded bianary values
// A-I
// J-R
// S-Z
// " ", ".", "-"
const PROGMEM  uint16_t alpha[]  = 
  {0x1E,0x05,0x05,0x1E,0x1F,0x15,0x17,0x1C,0x1F,0x11,0x11,0x11,0x1F,0x11,0x11,0x0E,0x1F,0x15,0x15,0x11,0x1F,0x05,0x05,0x01,0x1F,0x11,0x15,0x1D,0x1F,0x04,0x04,0x1F,0x11,0x1F,0x1F,0x11,
  0x19,0x11,0x1F,0x01,0x1F,0x04,0x0A,0x11,0x1F,0x10,0x10,0x10,0x1F,0x06,0x06,0x1F,0x1F,0x06,0x0C,0x1F,0x0E,0x11,0x11,0x0E,0x1F,0x05,0x05,0x07,0x0E,0x11,0x19,0x1E,0x1F,0x05,0x0D,0x17,
  0x17,0x15,0x15,0x1D,0x01,0x1F,0x1F,0x01,0x1F,0x10,0x10,0x1F,0x07,0x18,0x18,0x07,0x1F,0x0C,0x0C,0x1F,0x11,0x0E,0x0E,0x11,0x03,0x1E,0x1E,0x03,0x19,0x1D,0x17,0x13,
  0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x04,0x04,0x00};
  
const int wait = 15;                                // Length of one pixel in ms
const int r = 100, g = 100, b = 100;                // Pick the color of your text here
const int btn = 11;                                 // D11 will be our button pin
#include <Adafruit_NeoPixel.h>                      // https://github.com/adafruit/Adafruit_NeoPixel
#define PIN 1                                       // Pin 1 (tx) for serial communication with LED strip
// 5  Number of pixels in strip, NEO_GRB  Pixels are wired for GRB bitstream, NEO_KHZ800  800 KHz bitstream
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);
//-----------------------------------------------------------------------------------------------------------
void setup() {                                      // The setup program ones only once after power-up or reset
  strip.begin();                                    // Activate the LED strand
  strip.show();                                     // Initialize all pixels to 'off'
  strip.setBrightness(30);                          // Affects the brightness of the entire program (0-255)
  pinMode(btn, INPUT_PULLUP);                       // Setup pin for raw button
  pinMode(13, OUTPUT);                              // Use onboard LED as indicator for user
}
//-----------------------------------------------------------------------------------------------------------
void loop() {                                       // Loop lets the user button control their text exposures
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  digitalWrite(13, HIGH);                           // Show the user the exposure is running
  textConverter(exposureText);                      // Run the exposure of the selected text
  digitalWrite(13, LOW);                            // Show the user the exposure is complete
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  digitalWrite(13, HIGH);                           // Show the user the exposure is running
  textConverter(exposureText2);                     // Run the exposure of the selected text
  digitalWrite(13, LOW);                            // Show the user the exposure is complete
  while(digitalRead(btn)) delay(100);               // Wait while the button is inactive
  while(!digitalRead(btn)) delay(20);               // Don't start program until button is released
  digitalWrite(13, HIGH);                           // Show the user the exposure is running
  textConverter(exposureText3);                     // Run the exposure of the selected text
  digitalWrite(13, LOW);                            // Show the user the exposure is complete
}
//-----------------------------------------------------------------------------------------------------------
void textConverter(String inputText){               // Parses each letter into showLetter() for exposing
  for(int i = 0; i < inputText.length(); i++){      // Step through each letter in the current string
    int letter = int(inputText.charAt(i));          // Convert the ASCII value to an integer
    if(letter > 96 && letter < 123) letter -= 97;   // If the letter is lower case, make a = 0
    else if(letter>64 && letter<91) letter -= 65;   // If the letter is upper case, make A - 0
    else if(letter == 32) letter = 26;              // If the letter is a space use the alphabet character at 26
    else if(letter == 46) letter = 27;              // If the letter is a . use the alphabet character at 27
    else letter = 28;                               // If the letter is not in the alphabet we made, use "-"
    showLetter(letter);                             // Expose the current letter
  }
}
//-----------------------------------------------------------------------------------------------------------
void showLetter(int cha){                           // Expose the current letter on the hidden messages wand
  for(int b = 0; b < 4; b++){                       // Step through the four cols of the letter
    int stack = int(pgm_read_word_near(alpha + (cha*4 + b))); // Recall the col from memory
    if(stack > 15){                                 // If the number is large enough
      strip.setPixelColor(4, strip.Color(r,g,b));   // Turn on the first bianary digit
      stack -= 16;                                  // Delete it from the bianary total
    }
    else strip.setPixelColor(4, strip.Color(0,0,0));// If not, turn it off and continue
    if(stack > 7){                                  // If the number is large enough
      strip.setPixelColor(3, strip.Color(r,g,b));   // Turn on the second bianary digit
      stack -= 8;                                   // Delete it from the bianary total
    }
    else strip.setPixelColor(3, strip.Color(0,0,0));// If not, turn it off and continue
    if(stack > 3){                                  // If the number is larg enough
      strip.setPixelColor(2, strip.Color(r,g,b));   // Turn on the third bianary digit
      stack -= 4;                                   // Delete it from the bianary total
    }
    else strip.setPixelColor(2, strip.Color(0,0,0));// If not, turn it off and continue
    if(stack > 1){                                  // If the number is large enough
      strip.setPixelColor(1, strip.Color(r,g,b));   // Turn on the fourth bianary digit
      stack -= 2;                                   // Delete it from the bianary total
    }
    else strip.setPixelColor(1, strip.Color(0,0,0));// If not, turn it off and continue
    if(stack > 0) strip.setPixelColor(0, strip.Color(r,g,b)); // If valu is 1 turn last digit on
    else strip.setPixelColor(0, strip.Color(0,0,0));// If not, turn it off
    strip.show();                                   // Update and expose this col of the letter
    delay(wait);                                    // Leave it on for the length of one pixel
  }
  for(int a = 0; a < 5; a++){                       // Step through all 5 LEDs
    strip.setPixelColor(a, strip.Color(0,0,0));     // Turn them each off
  }
  strip.show();                                     // Update the strip
  delay(wait/2);                                    // Make a half pixel gap between letters
}
//-----------------------------------------------------------------------------------------------------------
