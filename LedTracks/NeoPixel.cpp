#include "Config.h"
#if ENABLE_NEOPIXEL
#include <Adafruit_NeoPixel.h>

static Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void neopixelSetup()
{
  strip.begin();
  strip.setBrightness(50);
}

void neopixelSetPalette(uint32_t *palette, int paletteIndex)
{  
  uint32_t offset = paletteIndex;
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    if (offset >= strip.numPixels())
     offset=0;    
    strip.setPixelColor(offset, palette[i]);
    offset++;    
  }
  strip.show();
}
#endif
