#if !defined NEOPIXEL_DEF
#define NEOPIXEL_DEF

void neopixelSetup();
void neopixelSetBrightness(unsigned char brightness);
void neopixelSetPalette(uint32_t *palette, int paletteIndex);

#endif
