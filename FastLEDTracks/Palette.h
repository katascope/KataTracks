#if !defined FX_PALETTE_DEF
#define FX_PALETTE_DEF

uint32_t palette[NUM_LEDS];

static uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

static void sayPalette()
{
  Serial.print("Pal = ");
  for(uint16_t i=0;i<8;i++)
  {
    Serial.print(palette[i]);
    Serial.print(" ");
  }
  Serial.println();
}

static void rotPalette()
{
  uint32_t last = palette[0];
  for(uint16_t i=0;i<NUM_LEDS;i++)
    palette[i] = palette[i+1];
  palette[NUM_LEDS-1] = last;
}

static void PaletteGradient()
{
  for (int i=0;i<NUM_LEDS;i++)
    palette[i] = LEDRGB(i,0,NUM_LEDS-1-i);
}

static void PaletteSolid(byte r, byte g, byte b)
{
  for (int i=0;i<NUM_LEDS;i++)
    palette[i] = LEDRGB(r,g,b);
}

static void PaletteDouble(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2)
{
  for (int i=0;i<NUM_LEDS;i++)
  {
    if (((i /16) %2)==0)
      palette[i] = LEDRGB(r1,g1,b1);
    else
      palette[i] = LEDRGB(r2,g2,b2);
  }
}

static void PaletteTriple(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2, byte r3, byte g3, byte b3)
{
  for (int i=0;i<NUM_LEDS;i++)
  {
    if (((i /8) %3)==0)
      palette[i] = LEDRGB(r1,g1,b1);
    else if (((i /8) %3)==1)
      palette[i] = LEDRGB(r2,g2,b2);
    else
      palette[i] = LEDRGB(r3,g3,b3);
  }
}

#endif
