#include <Adafruit_NeoPixel.h>
#include "NeoPixel.h"
//#include "Fx.h"
#include "Palette.h"
//#if NEOPIXEL_ENABLE
#define NUM_LEDS   80
#define LED_PIN    5


static Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void neopixelSetup()
{
  strip.begin();
  strip.setBrightness(50);
}

void neopixelSetPalette(FxController &fxc)
{  
  uint32_t offset = fxc.paletteIndex;
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    if (offset >= strip.numPixels())
     offset=0;    
    strip.setPixelColor(offset, fxc.palette[i]);
    offset++;    
  }
  strip.show();
}

//#endif
