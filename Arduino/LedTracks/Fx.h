#ifndef FX_DEF
#define FX_DEF
#include <Arduino.h>
#include "Config.h"
#include "FxCore.h"

struct FxStripController
{
  unsigned char brightness = BRIGHTNESS;
  FxTransitionType transitionType = Transition_Instant;  
  FxPaletteUpdateType fxPaletteUpdateType = FxPaletteUpdateType::None;
  uint32_t palette[NUM_LEDS];
  uint32_t nextPalette[NUM_LEDS];
  uint32_t initialPalette[NUM_LEDS];
  int paletteSpeed = 0;
  int paletteDirection = 1;
  int paletteIndex = 0;
  //uint32_t microPalette[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
  //unsigned int microPaletteSize = 1;  
};

struct FxController
{
  float transitionMux = 0;
 //Universal
  FxState fxState = FxState_Default;
  FxTrackEndAction fxTrackEndAction;
  unsigned long lastTimeLedUpdate = 0;  
  unsigned char stripMask = 255;
  FxStripController strip[8];
};

void FxEventProcess(FxController &fxc,int event);
void FxDisplayStatus(FxController &fxc);

/*void FxCreatePalette(FxController &fxController, uint32_t *pal16, unsigned int palSize);
void SetMicroPaletteSlot(FxController &fxc, int slot, uint32_t rgb);
void SetMicroPalette(FxController &fxc, byte r, byte g, byte b);
void SetMicroPalette2(FxController &fxc, byte r1, byte g1, byte b1, byte r2, byte g2, byte b2);
void SetMicroPalette4(FxController &fxc, 
  byte r1, byte g1, byte b1, 
  byte r2, byte g2, byte b2,
  byte r3, byte g3, byte b3,
  byte r4, byte g4, byte b4);
void SetMicroPalette16(FxController &fxc, uint32_t b0,uint32_t b1,uint32_t b2,uint32_t b3, uint32_t b4,uint32_t b5,uint32_t b6,uint32_t b7,
                        uint32_t b8,uint32_t b9,uint32_t b10,uint32_t b11, uint32_t b12,uint32_t b13,uint32_t b14,uint32_t b15);
                        */
void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) ;

#endif
