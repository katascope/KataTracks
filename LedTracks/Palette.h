#if !defined FX_PALETTE_DEF
#define FX_PALETTE_DEF
#include <avr/pgmspace.h> 

uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b);
void SayPalette(uint32_t *pal);
void CopyPalette(uint32_t *dst, uint32_t *src);
void SetPalette16(uint32_t *pal, uint32_t *pal16);
void rotPalette(uint32_t * palette);
void PaletteGradient(uint32_t * palette);
void PaletteSolid(uint32_t * palette, uint32_t rgb);
void PaletteDouble(uint32_t * palette, uint32_t rgb1, uint32_t rgb2);
void PaletteTriple(uint32_t * palette, uint32_t rgb1, uint32_t rgb2, uint32_t rgb3);

#endif
