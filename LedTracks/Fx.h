#if !defined FX_DEF
#define FX_DEF

/* 
 * 
 */
#include "Palette.h"

static uint8_t lerp(float mux, uint8_t a, uint8_t b) { return (uint8_t)(a * (1.0 - mux) + b * mux); }
static uint32_t LerpRGB(float t, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2) { return LEDRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2)); }
static uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2) { 
  byte r1 = (rgb1 >> 16) & 0xFF;
  byte g1 = (rgb1 >> 8) & 0xFF;
  byte b1 = (rgb1 >> 0) & 0xFF;
  byte r2 = (rgb2 >> 16) & 0xFF;
  byte g2 = (rgb2 >> 8) & 0xFF;
  byte b2 = (rgb2 >> 0) & 0xFF;
  return LEDRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2)); 
}

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

#define CRGB_DARK    LEDRGB(DARK)
#define CRGB_WHITE   LEDRGB(WHITE)
#define CRGB_RED     LEDRGB(RED)
#define CRGB_YELLOW  LEDRGB(YELLOW)
#define CRGB_GREEN   LEDRGB(GREEN)
#define CRGB_CYAN    LEDRGB(CYAN)
#define CRGB_BLUE    LEDRGB(BLUE)
#define CRGB_MAGENTA LEDRGB(MAGENTA)
#define CRGB_ORANGE  LEDRGB(ORANGE)
#define CRGB_HALF    LEDRGB(HALF)
#define CRGB_LOWHALF LEDRGB(LOWHALF)

static uint32_t ShortnameToCRGB(char shortName)
{  
  Serial.print(F("Short:"));
  Serial.println(shortName);
  switch (shortName)
  {
    case 'd': return CRGB_DARK; 
    case 'w': return CRGB_WHITE; 
    case 'r': return CRGB_RED; 
    case 'y': return CRGB_YELLOW; 
    case 'g': return CRGB_GREEN; 
    case 'c': return CRGB_CYAN; 
    case 'b': return CRGB_BLUE; 
    case 'm': return CRGB_MAGENTA; 
    case 'o': return CRGB_ORANGE; 
    case 'h': return CRGB_HALF; 
    case 'l': return CRGB_LOWHALF; 
  }
}

enum FxState
{
  FxState_Default       = 0,
  FxState_TestPattern   = 1,
  FxState_PlayingTrack  = 2,
};

String FxStateName(FxState s)
{
  switch (s)
  {
    case FxState_Default:      return F("Norm"); break;
    case FxState_TestPattern:  return F("Test"); break;
    case FxState_PlayingTrack: return F("Play"); break;
    default: return F("Unknown");
  }
}

//List of possible Fx events
enum FxEvent
{
  fx_speed_0  = 0,
  fx_speed_1  = 1,
  fx_speed_2  = 2,
  fx_speed_3  = 3,
  fx_speed_4  = 4,
  fx_speed_5  = 5,
  fx_speed_6  = 6,
  fx_speed_7  = 7,
  fx_speed_8  = 8,
  fx_speed_9  = 9,
  fx_speed_10 = 10,
  fx_speed_11 = 11,
  fx_speed_12 = 12,
  fx_speed_13 = 13,
  fx_speed_14 = 14,
  fx_speed_15 = 15,
  fx_speed_16 = 16,
  fx_speed_17 = 17,
  fx_speed_18 = 18,
  fx_speed_32 = 19,

  fx_speed_pos = 20,
  fx_speed_neg = 21,
  fx_speed_inc = 22,
  fx_speed_dec = 23,

  fx_transition_fast = 30,
  fx_transition_timed_fade = 31,
  fx_transition_timed_wipe_pos = 32,
  fx_transition_timed_wipe_neg = 33,

  fx_palette_lead,
  fx_palette_follow,

  fx_track_begin,
  fx_track_stop,

  fx_palette_lava,
  fx_palette_cloud,
  fx_palette_ocean,
  fx_palette_forest,
  fx_palette_rainbow,
  fx_palette_rainbowstripe,
  fx_palette_party,
  fx_palette_heat,

  fx_palette_dark,
  fx_palette_white,
  fx_palette_red,
  fx_palette_yellow,
  fx_palette_green,
  fx_palette_cyan,
  fx_palette_blue,
  fx_palette_magenta,
  fx_palette_orange,
  fx_palette_half,
  fx_palette_lowhalf,

  fx_palette_pulse_dark,
  fx_palette_pulse_white,
  fx_palette_pulse_red,
  fx_palette_pulse_yellow,
  fx_palette_pulse_green,
  fx_palette_pulse_cyan,
  fx_palette_pulse_blue,
  fx_palette_pulse_magenta,
  fx_palette_pulse_orange,
  fx_palette_pulse_half,
  fx_palette_pulse_lowhalf,
  
  fx_palette_dw,
  fx_palette_dr,
  fx_palette_dy,
  fx_palette_dg,
  fx_palette_dc,
  fx_palette_db,
  fx_palette_dm,
  fx_palette_wr,
  fx_palette_wy,
  fx_palette_wg,
  fx_palette_wc,
  fx_palette_wb,
  fx_palette_wm,
  fx_palette_ry,
  fx_palette_rg,
  fx_palette_rc,
  fx_palette_rb,
  fx_palette_rm,
  fx_palette_yg,
  fx_palette_yc,
  fx_palette_yb,
  fx_palette_ym,
  fx_palette_gc,
  fx_palette_gb,
  fx_palette_gm,
  fx_palette_cb,
  fx_palette_cm,
  fx_palette_bm,

  fx_palette_wry,
  fx_palette_wrg,
  fx_palette_wrc,
  fx_palette_wrb,
  fx_palette_wrm,
  fx_palette_wyg,
  fx_palette_wyc,
  fx_palette_wyb,
  fx_palette_wym,
  fx_palette_wgc,
  fx_palette_wgb,
  fx_palette_wgm,
  fx_palette_wcb,
  fx_palette_wcm,
  fx_palette_wbm,

  fx_palette_dry,
  fx_palette_drg,
  fx_palette_drc,
  fx_palette_drb,
  fx_palette_drm,
  fx_palette_dyg,
  fx_palette_dyc,
  fx_palette_dyb,
  fx_palette_dym,
  fx_palette_dgc,
  fx_palette_dgb,
  fx_palette_dgm,
  fx_palette_dcb,
  fx_palette_dcm,
  fx_palette_dbm,


  fx_nothing = 255
};

struct Fx { unsigned long timecode; unsigned long event;   };

static String FxEventName(int event)
{  
  switch(event)
  {
    case fx_speed_0: return F("x0");
    case fx_speed_1: return F("x1");
    case fx_speed_2: return F("x2");
    case fx_speed_3: return F("x3");
    case fx_speed_4: return F("x4");
    case fx_speed_5: return F("x5");
    case fx_speed_6: return F("x6");
    case fx_speed_7: return F("x7");
    case fx_speed_8: return F("x8");
    case fx_speed_9: return F("x9");
    case fx_speed_10: return F("x10");
    case fx_speed_11: return F("x11");
    case fx_speed_12: return F("x12");
    case fx_speed_13: return F("x13");
    case fx_speed_14: return F("x14");
    case fx_speed_15: return F("x15");
    case fx_speed_16: return F("x16");
    case fx_speed_17: return F("x17");
    case fx_speed_18: return F("x18");
    case fx_speed_32: return F("x32");

    case fx_speed_pos: return F("speed pos");
    case fx_speed_neg: return F("speed neg");
    case fx_speed_inc: return F("speed inc");
    case fx_speed_dec: return F("speed dec");
    
    case fx_transition_fast: return F("t-fast");
    case fx_transition_timed_fade:return F("t-timed-fade");
    case fx_transition_timed_wipe_pos:return F("t-timed-wipe-pos");
    case fx_transition_timed_wipe_neg:return F("t-timed-wipe-neg");
    
    case fx_palette_lead:    return F("lead");    
    case fx_palette_follow:  return F("follow");       

    case fx_palette_lava: return F("lava");
    case fx_palette_cloud: return F("cloud");
    case fx_palette_ocean: return F("ocean");
    case fx_palette_forest: return F("forest");
    case fx_palette_rainbow: return F("rainbow");
    case fx_palette_rainbowstripe: return F("rainbowstripe");
    case fx_palette_party: return F("party");
    case fx_palette_heat: return F("heat");

    case fx_palette_dark:    return F("dark");
    case fx_palette_white:   return F("white");
    case fx_palette_red:     return F("red");
    case fx_palette_yellow:  return F("yellow");
    case fx_palette_green:   return F("green");
    case fx_palette_cyan:    return F("cyan");
    case fx_palette_blue:    return F("blue");
    case fx_palette_magenta: return F("magenta");
    case fx_palette_orange:  return F("orange");
    case fx_palette_half:  return F("half");
    case fx_palette_lowhalf:  return F("lowhalf");

    case fx_palette_pulse_dark:    return F("pulse-dark");
    case fx_palette_pulse_white:   return F("pulse-white");
    case fx_palette_pulse_red:     return F("pulse-red");
    case fx_palette_pulse_yellow:  return F("pulse-yellow");
    case fx_palette_pulse_green:   return F("pulse-green");
    case fx_palette_pulse_cyan:    return F("pulse-cyan");
    case fx_palette_pulse_blue:    return F("pulse-blue");
    case fx_palette_pulse_magenta: return F("pulse-magenta");
    case fx_palette_pulse_orange:  return F("pulse-orange");
    case fx_palette_pulse_half:  return F("pulse-half");
    case fx_palette_pulse_lowhalf:  return F("pulse-lowhalf");
   
    case fx_palette_dw: return F("dark-white");
    case fx_palette_dr: return F("dark-red");
    case fx_palette_dy: return F("dark-yellow");
    case fx_palette_dg: return F("dark-green");
    case fx_palette_dc: return F("dark-cyan");
    case fx_palette_db: return F("dark-blue");
    case fx_palette_dm: return F("dark-magenta");
    case fx_palette_wr: return F("white-red");
    case fx_palette_wy: return F("white-yellow");
    case fx_palette_wg: return F("white-green");
    case fx_palette_wc: return F("white-cyan");
    case fx_palette_wb: return F("white-blue");
    case fx_palette_wm: return F("white-magenta");
    case fx_palette_ry: return F("red-yellow");
    case fx_palette_rg: return F("red-green");
    case fx_palette_rc: return F("red-cyan");
    case fx_palette_rb: return F("red-blue");
    case fx_palette_rm: return F("red-magenta");
    case fx_palette_yg: return F("yellow-green");
    case fx_palette_yc: return F("yellow-cyan");
    case fx_palette_yb: return F("yellow-blue");
    case fx_palette_ym: return F("yellow-magenta");
    case fx_palette_gc: return F("green-cyan");
    case fx_palette_gb: return F("green-blue");
    case fx_palette_gm: return F("green-magenta");
    case fx_palette_cb: return F("cyan-blue");
    case fx_palette_cm: return F("cyan-magenta");
    case fx_palette_bm: return F("blue-magenta");

    case fx_palette_wry:return F("wry");
    case fx_palette_wrg:return F("wrg");
    case fx_palette_wrc:return F("wrc");
    case fx_palette_wrb:return F("wrb");
    case fx_palette_wrm:return F("wrm");
    case fx_palette_wyg:return F("wyg");
    case fx_palette_wyc:return F("wyc");
    case fx_palette_wyb:return F("wyb");
    case fx_palette_wym:return F("wym");
    case fx_palette_wgc:return F("wgc");
    case fx_palette_wgb:return F("wgb");
    case fx_palette_wgm:return F("wgm");
    case fx_palette_wcb:return F("wcb");
    case fx_palette_wcm:return F("wcm");
    case fx_palette_wbm:return F("wbm");

    case fx_palette_dry:return F("dry");
    case fx_palette_drg:return F("drg");
    case fx_palette_drc:return F("drc");
    case fx_palette_drb:return F("drb");
    case fx_palette_drm:return F("drm");
    case fx_palette_dyg:return F("dyg");
    case fx_palette_dyc:return F("dyc");
    case fx_palette_dyb:return F("dyb");
    case fx_palette_dym:return F("dym");
    case fx_palette_dgc:return F("dgc");
    case fx_palette_dgb:return F("dgb");
    case fx_palette_dgm:return F("dgm");
    case fx_palette_dcb:return F("dcb");
    case fx_palette_dcm:return F("dcm");
    case fx_palette_dbm:return F("dbm");    
    
    case fx_nothing:return F("nothing");
  }
  return F("unk");
}

enum FxTransitionType
{
  Transition_Instant      = 0,
  Transition_TimedFade    = 1,
  Transition_TimedWipePos = 2,
  Transition_TimedWipeNeg = 3,
};

String FxTransitionName(FxTransitionType t)
{
  switch (t)
  {
    case Transition_Instant:      return F("Fast"); break;
    case Transition_TimedFade:    return F("Fade"); break;
    case Transition_TimedWipePos: return F("Wip-"); break;
    case Transition_TimedWipeNeg: return F("Wip+"); break;
    default: return F("Unknown");
  }
}

struct FxController
{
  //CRGBPalette16 currentPalette;
  //CRGBPalette16 initialPalette;
  //CRGBPalette16 nextPalette;
  FxTransitionType transitionType;
  uint32_t nextPalette[NUM_LEDS];
  uint32_t initialPalette[NUM_LEDS];
  int paletteSpeed = 0;
  int paletteDirection = 1;
  int paletteIndex = 0;
  bool animatePalette = false;
  float transitionMux = 0;
};
static FxController fxController;

void CreatePalette(uint32_t *pal16)
{
  Serial.print("CreatePalette");
  Serial.println();
  
    if (fxController.transitionType == Transition_Instant)
    {
      //fxController.currentPalette = palette;    
      SetPalette16(palette, pal16);
    }
    else if (fxController.transitionType == Transition_TimedFade)
    {
      CopyPalette(fxController.initialPalette, palette);
      SetPalette16(fxController.nextPalette, pal16);
      
      //fxController.nextPalette = palette;
      //fxController.initialPalette = fxController.currentPalette; 
    }
    else if (fxController.transitionType == Transition_TimedWipePos)
    {
      SayPalette(palette);
      SayPalette(fxController.initialPalette);
      SayPalette(fxController.nextPalette);
      CopyPalette(fxController.initialPalette, palette);
      SetPalette16(fxController.nextPalette, pal16);
      SayPalette(palette);
      SayPalette(fxController.initialPalette);
      SayPalette(fxController.nextPalette);
    }
    else if (fxController.transitionType == Transition_TimedWipeNeg)
    {
      CopyPalette(fxController.initialPalette, palette);
      SetPalette16(fxController.nextPalette, pal16);
    }
    
}

void CreatePaletteBands(uint32_t b0,uint32_t b1,uint32_t b2,uint32_t b3, uint32_t b4,uint32_t b5,uint32_t b6,uint32_t b7, 
                        uint32_t b8,uint32_t b9,uint32_t b10,uint32_t b11, uint32_t b12,uint32_t b13,uint32_t b14,uint32_t b15)
{
  //CreatePalette(CRGBPalette16(b0,b1,b2,b3, b4,b5,b6,b7, b8,b9,b10,b11, b12,b13,b14,b15));
  //PaletteSolid(b0);

  float scaling = (float)(NUM_LEDS)/16.0f;
  uint32_t palette16[16] = { b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15};
  CreatePalette(palette16);
}

void CreateQuadBand(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3, uint8_t r4, uint8_t g4, uint8_t b4)
{
  CreatePaletteBands(LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4));
}
void CreateTripleBand(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3)
{ 
  CreatePaletteBands(LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1),
                     LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),
                     LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1)
                     );
}
void CreateDoubleBand(uint8_t r1, uint8_t g1, uint8_t b1,uint8_t r2, uint8_t g2, uint8_t b2) { CreateQuadBand(r1,g1,b1, r2,g2,b2, r1,g1,b1, r2,g2,b2);}
void CreateSingleBand(uint8_t r, uint8_t g, uint8_t b) { CreateQuadBand(r,g,b,r,g,b,r,g,b,r,g,b); }
void CreateSinglePulseBand(uint8_t r, uint8_t g, uint8_t b) { 
  CreatePaletteBands( LEDRGB(r/2,g/2,b/2),LEDRGB(r,g,b),LEDRGB(r/2,g/2,b/2),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0));
}


void FxEventProcess(int event)
{  
  switch (event)
  {
    case fx_speed_0:
    case fx_speed_1:
    case fx_speed_2:
    case fx_speed_3:
    case fx_speed_4:
    case fx_speed_5:
    case fx_speed_6:
    case fx_speed_7:
    case fx_speed_8:
    case fx_speed_9:
    case fx_speed_10:
    case fx_speed_11:
    case fx_speed_12:
    case fx_speed_13:
    case fx_speed_14:
    case fx_speed_15:
    case fx_speed_16:
    case fx_speed_17:
    case fx_speed_18:
      fxController.paletteSpeed = event;
      break;
    case fx_speed_32:
      fxController.paletteSpeed = 32;
      break;

    case fx_speed_pos:fxController.paletteDirection = 1;break;
    case fx_speed_neg:fxController.paletteDirection = -1;break;

    case fx_speed_inc:
      fxController.paletteSpeed++;
      if (fxController.paletteSpeed >= 18)
        fxController.paletteSpeed = 18;
      break;
    case fx_speed_dec:
      fxController.paletteSpeed--;
      if (fxController.paletteSpeed < 0)
        fxController.paletteSpeed = 0;
      break;
    case fx_transition_fast:fxController.transitionType = Transition_Instant;break;
    case fx_transition_timed_fade:fxController.transitionType = Transition_TimedFade;break;
    case fx_transition_timed_wipe_pos:fxController.transitionType = Transition_TimedWipePos;fxController.paletteIndex = 0;fxController.animatePalette = false;break;
    case fx_transition_timed_wipe_neg:fxController.transitionType = Transition_TimedWipeNeg;fxController.paletteIndex = 15;fxController.animatePalette = false;break;

    case fx_palette_lead:CreateSingleBand(BLUE);break;
    case fx_palette_follow:CreateSingleBand(RED);break;    
   
    //case fx_palette_dark:break;//CreateDefaultBand(DARK);break;
/*    case fx_palette_lava:CreatePalette(LavaColors_p);break;
    case fx_palette_cloud:CreatePalette(CloudColors_p);break;
    case fx_palette_ocean:CreatePalette(OceanColors_p);break;
    case fx_palette_forest:CreatePalette(ForestColors_p);break;
    case fx_palette_rainbow:CreatePalette(RainbowColors_p);break;
    case fx_palette_rainbowstripe:CreatePalette(RainbowStripeColors_p);break;
    case fx_palette_party:CreatePalette(PartyColors_p);break;
    case fx_palette_heat:CreatePalette(HeatColors_p);break;
*/
    case fx_palette_dark:CreateSingleBand(DARK);break;
    case fx_palette_white:CreateSingleBand(WHITE);break;
    case fx_palette_red:CreateSingleBand(RED);break;
    case fx_palette_yellow:CreateSingleBand(YELLOW);break;
    case fx_palette_green:CreateSingleBand(GREEN);break;
    case fx_palette_cyan:CreateSingleBand(CYAN);break;
    case fx_palette_blue:CreateSingleBand(BLUE);break;
    case fx_palette_magenta:CreateSingleBand(MAGENTA);break;
    case fx_palette_orange:CreateSingleBand(ORANGE);break;
    case fx_palette_half:CreateSingleBand(HALF);break;
    case fx_palette_lowhalf:CreateSingleBand(LOWHALF);break;

    case fx_palette_pulse_dark:CreateSinglePulseBand(DARK);break;
    case fx_palette_pulse_white:CreateSinglePulseBand(WHITE);break;
    case fx_palette_pulse_red:CreateSinglePulseBand(RED);break;
    case fx_palette_pulse_yellow:CreateSinglePulseBand(YELLOW);break;
    case fx_palette_pulse_green:CreateSinglePulseBand(GREEN);break;
    case fx_palette_pulse_cyan:CreateSinglePulseBand(CYAN);break;
    case fx_palette_pulse_blue:CreateSinglePulseBand(BLUE);break;
    case fx_palette_pulse_magenta:CreateSinglePulseBand(MAGENTA);break;
    case fx_palette_pulse_orange:CreateSinglePulseBand(ORANGE);break;
    case fx_palette_pulse_half:CreateSinglePulseBand(HALF);break;
    case fx_palette_pulse_lowhalf:CreateSinglePulseBand(LOWHALF);break;
    
    case fx_palette_dr: CreateDoubleBand(DARK, RED); break;
    case fx_palette_dy: CreateDoubleBand(DARK, YELLOW); break;
    case fx_palette_dg: CreateDoubleBand(DARK, GREEN); break;
    case fx_palette_dc: CreateDoubleBand(DARK, CYAN); break;
    case fx_palette_db: CreateDoubleBand(DARK, BLUE); break;
    case fx_palette_dm: CreateDoubleBand(DARK, MAGENTA); break;
    case fx_palette_wr: CreateDoubleBand(WHITE, RED); break;
    case fx_palette_wy: CreateDoubleBand(WHITE, YELLOW); break;
    case fx_palette_wg: CreateDoubleBand(WHITE, GREEN); break;
    case fx_palette_wc: CreateDoubleBand(WHITE, CYAN); break;
    case fx_palette_wb: CreateDoubleBand(WHITE, BLUE); break;
    case fx_palette_wm: CreateDoubleBand(WHITE, MAGENTA); break;
    case fx_palette_ry: CreateDoubleBand(RED, YELLOW); break;
    case fx_palette_rg: CreateDoubleBand(RED, GREEN); break;
    case fx_palette_rc: CreateDoubleBand(RED, CYAN); break;
    case fx_palette_rb: CreateDoubleBand(RED, BLUE); break;
    case fx_palette_rm: CreateDoubleBand(RED, MAGENTA); break;
    case fx_palette_yg: CreateDoubleBand(YELLOW, GREEN); break;
    case fx_palette_yc: CreateDoubleBand(YELLOW, CYAN); break;
    case fx_palette_yb: CreateDoubleBand(YELLOW, BLUE); break;
    case fx_palette_ym: CreateDoubleBand(YELLOW, MAGENTA); break;
    case fx_palette_gc: CreateDoubleBand(GREEN, CYAN); break;
    case fx_palette_gb: CreateDoubleBand(GREEN, BLUE); break;
    case fx_palette_gm: CreateDoubleBand(GREEN, MAGENTA); break;
    case fx_palette_cb: CreateDoubleBand(CYAN, BLUE); break;
    case fx_palette_cm: CreateDoubleBand(CYAN, MAGENTA); break;
    case fx_palette_bm: CreateDoubleBand(BLUE, MAGENTA); break;

    case fx_palette_wry: CreateQuadBand(WHITE, RED,    WHITE, YELLOW); break;
    case fx_palette_wrg: CreateQuadBand(WHITE, RED,    WHITE, GREEN); break;
    case fx_palette_wrc: CreateQuadBand(WHITE, RED,    WHITE, CYAN); break;
    case fx_palette_wrb: CreateQuadBand(WHITE, RED,    WHITE, BLUE); break;
    case fx_palette_wrm: CreateQuadBand(WHITE, RED,    WHITE, MAGENTA); break;
    case fx_palette_wyg: CreateQuadBand(WHITE, YELLOW, WHITE, GREEN); break;
    case fx_palette_wyc: CreateQuadBand(WHITE, YELLOW, WHITE, CYAN); break;
    case fx_palette_wyb: CreateQuadBand(WHITE, YELLOW, WHITE, BLUE); break;
    case fx_palette_wym: CreateQuadBand(WHITE, YELLOW, WHITE, MAGENTA); break;
    case fx_palette_wgc: CreateQuadBand(WHITE, GREEN,  WHITE, CYAN); break;
    case fx_palette_wgb: CreateQuadBand(WHITE, GREEN,  WHITE, BLUE); break;
    case fx_palette_wgm: CreateQuadBand(WHITE, GREEN,  WHITE, MAGENTA); break;
    case fx_palette_wcb: CreateQuadBand(WHITE, CYAN,   WHITE, BLUE); break;
    case fx_palette_wcm: CreateQuadBand(WHITE, CYAN,   WHITE, MAGENTA); break;
    case fx_palette_wbm: CreateQuadBand(WHITE, BLUE,   WHITE, MAGENTA); break;

    case fx_palette_dry: CreateQuadBand(DARK, RED,    DARK, YELLOW); break;
    case fx_palette_drg: CreateQuadBand(DARK, RED,    DARK, GREEN); break;
    case fx_palette_drc: CreateQuadBand(DARK, RED,    DARK, CYAN); break;
    case fx_palette_drb: CreateQuadBand(DARK, RED,    DARK, BLUE); break;
    case fx_palette_drm: CreateQuadBand(DARK, RED,    DARK, MAGENTA); break;
    case fx_palette_dyg: CreateQuadBand(DARK, YELLOW, DARK, GREEN); break;
    case fx_palette_dyc: CreateQuadBand(DARK, YELLOW, DARK, CYAN); break;
    case fx_palette_dyb: CreateQuadBand(DARK, YELLOW, DARK, BLUE); break;
    case fx_palette_dym: CreateQuadBand(DARK, YELLOW, DARK, MAGENTA); break;
    case fx_palette_dgc: CreateQuadBand(DARK, GREEN,  DARK, CYAN); break;
    case fx_palette_dgb: CreateQuadBand(DARK, GREEN,  DARK, BLUE); break;
    case fx_palette_dgm: CreateQuadBand(DARK, GREEN,  DARK, MAGENTA); break;
    case fx_palette_dcb: CreateQuadBand(DARK, CYAN,   DARK, BLUE); break;
    case fx_palette_dcm: CreateQuadBand(DARK, CYAN,   DARK, MAGENTA); break;
    case fx_palette_dbm: CreateQuadBand(DARK, BLUE,   DARK, MAGENTA); break;

 }
}

#endif
