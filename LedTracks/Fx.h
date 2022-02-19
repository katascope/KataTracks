#if !defined FX_DEF
#define FX_DEF
#include <avr/pgmspace.h> 

#include "Config.h"
#include "FxTypes.h"

struct FxController
{
  FxState fxState = FxState_Default;
  FxTransitionType transitionType = Transition_Instant;  
  uint32_t palette[NUM_LEDS];
  uint32_t nextPalette[NUM_LEDS];
  uint32_t initialPalette[NUM_LEDS];
  int paletteSpeed = 0;
  int paletteDirection = 1;
  int paletteIndex = 0;
  bool updatePalette = false;
  float transitionMux = 0;
  FxTrackEndAction trackEndAction;
  unsigned char brightness = 50;
};

uint8_t lerp(float mux, uint8_t a, uint8_t b);
uint32_t LerpRGB(float t, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2);
uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2);

uint32_t ShortnameToCRGB(char shortName);

void PrintFxStateName(FxState s);
void PrintFxEventName(int event);
void PrintFxTransitionName(FxTransitionType t);

void CreatePalette(FxController &fxController, uint32_t *pal16);
void CreatePaletteBands(FxController &fxc, uint32_t b0,uint32_t b1,uint32_t b2,uint32_t b3, uint32_t b4,uint32_t b5,uint32_t b6,uint32_t b7, 
                        uint32_t b8,uint32_t b9,uint32_t b10,uint32_t b11, uint32_t b12,uint32_t b13,uint32_t b14,uint32_t b15);

void CreateQuadBand(FxController &fxc, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3, uint8_t r4, uint8_t g4, uint8_t b4);
void CreateTripleBand(FxController &fxc, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3);
void CreateDoubleBand(FxController &fxc, uint8_t r1, uint8_t g1, uint8_t b1,uint8_t r2, uint8_t g2, uint8_t b2);
void CreateSingleBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b);
void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b);

void FxEventProcess(FxController &fxc,int event);

#endif
