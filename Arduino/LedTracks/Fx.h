#ifndef FX_DEF
#define FX_DEF
#include <Arduino.h>
#include "Config.h"
#include "FxCore.h"

#define NUM_SIDEFX 4
#define NUM_PARTICLES 4

class FxStripController
{
public:  
  int numleds = 0;
  unsigned char brightness = BRIGHTNESS;
  FxTransitionType transitionType = Transition_Instant;  
  FxPaletteUpdateType fxPaletteUpdateType = FxPaletteUpdateType::None;
  uint32_t *palette;
  uint32_t *nextPalette;
  uint32_t *initialPalette;
  unsigned int *sequence;
  int paletteSpeed = 0;
  int paletteDirection = 1;
  int paletteIndex = 0;

  bool sideFx[NUM_SIDEFX];
  FxParticle particles[NUM_PARTICLES];
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
    for (int s=0;s<NUM_SIDEFX;s++)
      sideFx[s] = false;

    for (int p=0;p<NUM_PARTICLES;p++)
    {
      particles[p].pos = rand() & (numleds-1);
      //particles[p].vel = 0.25f + (float)(rand()%10) / 10.0f;      
      //if (rand()%2==0)
        particles[p].vel = 0.5f + (float)(rand()%40) / 40.0f;
      //else
        //particles[p].vel = -0.5f - (float)(rand()%40) / 40.0f;      
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
  bool IsAnimating()
  {
    for (int i=0;i<NUM_STRIPS;i++)
        if (strip[i]->paletteSpeed > 0)
          return true;
    return false;
  }
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

void FxProcessSideFX(FxController &fxc);
void FxEventProcess(FxController &fxc,int event);
void FxDisplayStatus(FxController &fxc);
void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) ;

#endif
