#include <avr/pgmspace.h> 
#include "Config.h"
#include "Palette.h"

uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

void SayPalette(uint32_t *pal)
{
  /*Serial.print("Pal = ");
  for(uint16_t i=0;i<8;i++)
  {
    Serial.print(pal[i]);
    Serial.print(" ");
  }
  Serial.println();*/
}

void CopyPalette(uint32_t *dst, uint32_t *src)
{
  for (int i=0;i<NUM_LEDS;i++)
    dst[i] = src[i];
}

void SetPalette16(uint32_t *pal, uint32_t *palsrc)
{
  float scaling = (float)16.0f/(float)NUM_LEDS;
//  Serial.print("Set pal16:");
  for (int i=0;i<NUM_LEDS;i++)
  {
    uint16_t offset = (float)i*(float)scaling;
    uint32_t rgb = palsrc[offset];
    pal[i] = rgb;
  //  Serial.print(rgb);
//    Serial.print(" ");
  }
//  Serial.println();
}


void rotPalette(uint32_t * palette)
{
  uint32_t last = palette[0];
  for(uint16_t i=0;i<NUM_LEDS;i++)
    palette[i] = palette[i+1];
  palette[NUM_LEDS-1] = last;
}

void PaletteGradient(uint32_t * palette)
{
  for (int i=0;i<NUM_LEDS;i++)
    palette[i] = LEDRGB(i,0,NUM_LEDS-1-i);
}

void PaletteSolid(uint32_t * palette, uint32_t rgb)
{
  for (int i=0;i<NUM_LEDS;i++)
    palette[i] = rgb;
}

void PaletteDouble(uint32_t * palette, uint32_t rgb1, uint32_t rgb2)
{
  for (int i=0;i<NUM_LEDS;i++)
  {
    if (((i /16) %2)==0)
      palette[i] = rgb1;
    else
      palette[i] = rgb2;
  }
}

void PaletteTriple(uint32_t * palette, uint32_t rgb1, uint32_t rgb2, uint32_t rgb3)
{
  for (int i=0;i<NUM_LEDS;i++)
  {
    if (((i /8) %3)==0)
      palette[i] = rgb1;
    else if (((i /8) %3)==1)
      palette[i] = rgb2;
    else
      palette[i] = rgb3;
  }
}
