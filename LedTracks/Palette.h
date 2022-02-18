#if !defined FX_PALETTE_DEF
#define FX_PALETTE_DEF

#define NUM_LEDS   80

uint32_t palette[NUM_LEDS];

static uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

static void SayPalette(uint32_t *pal)
{
  Serial.print("Pal = ");
  for(uint16_t i=0;i<8;i++)
  {
    Serial.print(pal[i]);
    Serial.print(" ");
  }
  Serial.println();
}


void CopyPalette(uint32_t *dst, uint32_t *src)
{
  for (int i=0;i<NUM_LEDS;i++)
    dst[i] = src[i];  
}

void SetPalette16(uint32_t *pal, uint32_t *pal16)
{
  float scaling = (float)16.0f/(float)NUM_LEDS;
//  Serial.print("Set pal16:");
  for (int i=0;i<NUM_LEDS;i++)
  {
    uint16_t offset = (float)i*(float)scaling;
    uint32_t rgb = pal16[offset];
    pal[i] = rgb;
  //  Serial.print(rgb);
//    Serial.print(" ");
  }
//  Serial.println();
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

static void PaletteSolid(uint32_t rgb)
{
  for (int i=0;i<NUM_LEDS;i++)
    palette[i] = rgb;
}

static void PaletteDouble(uint32_t rgb1, uint32_t rgb2)
{
  for (int i=0;i<NUM_LEDS;i++)
  {
    if (((i /16) %2)==0)
      palette[i] = rgb1;
    else
      palette[i] = rgb2;
  }
}

static void PaletteTriple(uint32_t rgb1, uint32_t rgb2, uint32_t rgb3)
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

#endif
