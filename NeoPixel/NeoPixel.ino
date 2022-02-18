// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).


#include <Adafruit_NeoPixel.h>
#define NUM_LEDS   128
#include "Palette.h"
#define LED_PIN    3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600); //serial communication at 9600 bauds
  delay( 3000 ); // power-up safety delay  
  strip.begin();
  strip.setBrightness(50);

  PaletteGradient();
  //PaletteSolid(255,127,0);
  //PaletteDouble(0,255,255, 255,0,255);
//  PaletteTriple(255,0,0, 0,255,0, 0,0,255);
}

void setPalette()
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {  
      strip.setPixelColor(i, palette[i]);
  }
  strip.show();
}

void loop() {  
  rotPalette();
  setPalette();
  delay(25);
}
