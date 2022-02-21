#include <iostream>
#include <iomanip>
#include <string>

#define DARK    0x00,0x00,0x00
#define WHITE   0xFF,0xFF,0xFF
#define RED     0xFF,0x00,0x00
#define YELLOW  0xFF,0xFF,0x00
#define GREEN   0x00,0xFF,0x00
#define CYAN    0x00,0xFF,0xFF
#define BLUE    0x00,0x00,0xFF
#define MAGENTA 0x7F,0x00,0xFF
#define ORANGE  0xFF,0x7F,0x00
#define HALF    0x7F,0x7F,0x7F
#define LOWHALF 0x4F,0x4F,0x4F
#define MAKERGB(r,g,b) ((unsigned int)((((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

unsigned char lerp(float mux, unsigned char a, unsigned char b) { return (unsigned char)(a * (1.0 - mux) + b * mux); }
uint32_t LerpRGB(float t, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2) { return MAKERGB(lerp(t, r1, r2), lerp(t, g1, g2), lerp(t, b1, b2)); }
uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2) {
    unsigned char r1 = (rgb1 >> 16) & 0xFF;
    unsigned char g1 = (rgb1 >> 8) & 0xFF;
    unsigned char b1 = (rgb1 >> 0) & 0xFF;
    unsigned char r2 = (rgb2 >> 16) & 0xFF;
    unsigned char g2 = (rgb2 >> 8) & 0xFF;
    unsigned char b2 = (rgb2 >> 0) & 0xFF;
    return MAKERGB(lerp(t, r1, r2), lerp(t, g1, g2), lerp(t, b1, b2));
}

void LerpPaletteFromMicroPalette(unsigned int *palette, unsigned int paletteSize, unsigned int* microPalette, unsigned int microPaletteSize)
{
    if (microPaletteSize == 0) //Nothing TO do..
        return;

    float stepSize = (float)paletteSize / (float)microPaletteSize;
    for (unsigned int phase = 0; phase < microPaletteSize; phase++)
    {
        unsigned long to = 0;
        unsigned int offset = (unsigned int)((float)(phase) * (float)stepSize);
        unsigned int offsetNext = (unsigned int)((float)(phase+1) * (float)stepSize) ;

        if (phase == microPaletteSize-1) //last phase, so loop back to 0 
            to = microPalette[0]; 
        else
            to = microPalette[phase + 1];

        unsigned int len = offsetNext - offset;
        for (unsigned int i = 0; i < len; i++)
        {
            float mux = (float)i / (float)(len-1);
            unsigned int palIndex = offset + i;
            unsigned long val = LerpRGB(mux, microPalette[phase], to);
            palette[palIndex] = val;
        }
    }
}

int main()
{
#define PAL_SIZE 255
    unsigned int palette[PAL_SIZE];

    for (int i=0;i<PAL_SIZE;i++)
        palette[i] = 0;

    unsigned int microPalette[16] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
    unsigned int microPaletteActive = 0;

    microPalette[0] = MAKERGB(0xFF, 0xFF, 0xFF);
    microPalette[1] = MAKERGB(0xFF, 0x00, 0x00);
    microPalette[2] = MAKERGB(0x00, 0x00, 0x00);
    microPalette[3] = MAKERGB(0x00, 0xFF, 0x00);
    microPalette[4] = MAKERGB(0x00, 0x00, 0x00);
    microPalette[5] = MAKERGB(0x00, 0x00, 0xFF);
    microPaletteActive = 2;

    std::cout << "MicroPalette:" << std::endl;
    for (unsigned int i = 0; i < microPaletteActive; i++)
    {
        std::cout << " " << std::to_string(i) << " " << std::hex << microPalette[i] << std::endl;
    }

    LerpPaletteFromMicroPalette(palette, PAL_SIZE, microPalette, microPaletteActive);
    std::cout << std::endl;

    std::cout << "Palette:" << std::endl;
    for (unsigned int i = 0; i < PAL_SIZE; i++)
    {
        unsigned long u = palette[i];
        std::cout << " " << std::to_string(i) << " " << std::hex << palette[i] << std::endl;
    }
    return 0;
}

 