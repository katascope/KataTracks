#ifndef FX_DEF
#define FX_DEF
#include <Arduino.h>
#include "Config.h"
#include "FxCore.h"

class FxStripController
{
public:  
  int numleds = 0;
  unsigned char brightness = BRIGHTNESS;
  FxTransitionType transitionType = Transition_Instant;  
  FxPaletteUpdateType fxPaletteUpdateType = FxPaletteUpdateType::Always;
  uint32_t *palette;
  uint32_t *nextPalette;
  uint32_t *initialPalette;
  unsigned int *sequence;
  //uint32_t palette[80];
  //uint32_t nextPalette[80];
  //uint32_t initialPalette[80];
  int paletteSpeed = 0;
  int paletteDirection = 1;
  int paletteIndex = 0;
public:
  FxStripController(int nl)
  { 
    numleds = nl;
    palette = (uint32_t *)malloc(sizeof(uint32_t) * numleds);
    nextPalette = (uint32_t *)malloc(sizeof(uint32_t) * numleds);
    initialPalette = (uint32_t *)malloc(sizeof(uint32_t) * numleds);
    sequence = (unsigned int *)malloc(sizeof(sequence) * numleds);
    for (int i=0;i<numleds;i++)
    {
      palette[i] = LEDRGB(0,0,0);
      nextPalette[i] = LEDRGB(0,0,0);
      initialPalette[i] = LEDRGB(0,0,0);
      sequence[i] = i;
    }
  } 
};

struct FxController
{
public:  
  float transitionMux = 0;
  FxState fxState = FxState_Default;
  FxTrackEndAction fxTrackEndAction;
  unsigned long lastTimeLedUpdate = 0;  
  unsigned char stripMask = 255;
  FxStripController *strip[NUM_STRIPS];
  public:
  FxController()
  {
    for (int i=0;i<NUM_STRIPS;i++)
    {
      strip[i] = NULL;
      switch (i)
      {
        case 0: strip[i] = new FxStripController(NUM_LEDS_0); break;
        case 1: strip[i] = new FxStripController(NUM_LEDS_1); break;
        case 2: strip[i] = new FxStripController(NUM_LEDS_2); break;
        case 3: strip[i] = new FxStripController(NUM_LEDS_3); break;
        case 4: strip[i] = new FxStripController(NUM_LEDS_4); break;
        case 5: strip[i] = new FxStripController(NUM_LEDS_5); break;
        case 6: strip[i] = new FxStripController(NUM_LEDS_6); break;
        case 7: strip[i] = new FxStripController(NUM_LEDS_7); break;
      }
    }
  }
};

void FxEventProcess(FxController &fxc,int event);
void FxDisplayStatus(FxController &fxc);
void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) ;

#endif
