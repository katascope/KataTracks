#if !defined FX_DEF
#define FX_DEF

/* 
 * 
 */
#include <FastLED.h>

static uint8_t lerp(float mux, uint8_t a, uint8_t b) { return (uint8_t)(a * (1.0 - mux) + b * mux); }
static CRGB LerpRGB(float t, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2) { return CRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2)); }

#define DARK    0x00,0x00,0x00
#define WHITE   0xFF,0xFF,0xFF
#define RED     0xFF,0x00,0x00
#define YELLOW  0xFF,0xFF,0x00
#define GREEN   0x00,0xFF,0x00
#define CYAN    0x00,0xFF,0xFF
#define BLUE    0x00,0x00,0xFF
#define MAGENTA 0xFF,0x00,0xFF
#define ORANGE  0xFF,0x7F,0x00

#define CRGB_DARK    CRGB(DARK)
#define CRGB_WHITE   CRGB(WHITE)
#define CRGB_RED     CRGB(RED)
#define CRGB_YELLOW  CRGB(YELLOW)
#define CRGB_GREEN   CRGB(GREEN)
#define CRGB_CYAN    CRGB(CYAN)
#define CRGB_BLUE    CRGB(BLUE)
#define CRGB_MAGENTA CRGB(MAGENTA)
#define CRGB_ORANGE  CRGB(ORANGE)

static CRGB ShortnameToCRGB(char shortName)
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
  }
}

enum FxState
{
  FxState_Default       = 0,
  FxState_TestPattern   = 1,
  FxState_PlayingTrack  = 2,
};

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

  fx_palette_lead = 40,
  fx_palette_follow = 41,

  fx_track_begin = 50,
  fx_track_stop = 51,

  fx_palette_lava = 91,
  fx_palette_cloud = 92,
  fx_palette_ocean = 93,
  fx_palette_forest = 94,
  fx_palette_rainbow = 95,
  fx_palette_rainbowstripe = 96,
  fx_palette_party = 97,
  fx_palette_heat = 98,

  fx_palette_dark = 101,
  fx_palette_white = 102,
  fx_palette_red = 103,
  fx_palette_yellow = 104,
  fx_palette_green = 105,
  fx_palette_cyan = 106,
  fx_palette_blue = 107,
  fx_palette_magenta = 108,
  fx_palette_orange = 109,  
  
  fx_palette_dw = 119,  
  fx_palette_dr = 120,
  fx_palette_dy = 121,
  fx_palette_dg = 122,
  fx_palette_dc = 123,
  fx_palette_db = 124,
  fx_palette_dm = 125,
  fx_palette_wr = 130,
  fx_palette_wy = 131,
  fx_palette_wg = 132,
  fx_palette_wc = 133,
  fx_palette_wb = 134,
  fx_palette_wm = 135,
  fx_palette_ry = 141,
  fx_palette_rg = 142,
  fx_palette_rc = 143,
  fx_palette_rb = 144,
  fx_palette_rm = 145,
  fx_palette_yg = 152,
  fx_palette_yc = 153,
  fx_palette_yb = 154,
  fx_palette_ym = 155,
  fx_palette_gc = 163,
  fx_palette_gb = 164,
  fx_palette_gm = 165,
  fx_palette_cb = 174,
  fx_palette_cm = 175,
  fx_palette_bm = 185,

  fx_palette_wry = 201,
  fx_palette_wrg = 202,
  fx_palette_wrc = 203,
  fx_palette_wrb = 204,
  fx_palette_wrm = 205,
  fx_palette_wyg = 206,
  fx_palette_wyc = 207,
  fx_palette_wyb = 208,
  fx_palette_wym = 209,
  fx_palette_wgc = 210,
  fx_palette_wgb = 211,
  fx_palette_wgm = 212,
  fx_palette_wcb = 213,
  fx_palette_wcm = 214,
  fx_palette_wbm = 215,

  fx_palette_dry = 221,
  fx_palette_drg = 222,
  fx_palette_drc = 223,
  fx_palette_drb = 224,
  fx_palette_drm = 225,
  fx_palette_dyg = 226,
  fx_palette_dyc = 227,
  fx_palette_dyb = 228,
  fx_palette_dym = 229,
  fx_palette_dgc = 230,
  fx_palette_dgb = 231,
  fx_palette_dgm = 232,
  fx_palette_dcb = 233,
  fx_palette_dcm = 234,
  fx_palette_dbm = 235,

  fx_palette_rgb = 240,
  fx_palette_cmy = 241,

  fx_nothing = 255
};

struct Fx { unsigned long timecode; unsigned long event;   };

static String FxEventName(int event)
{  
  switch(event)
  {
    case fx_speed_0: return F("x0");break;
    case fx_speed_1: return F("x1");break;
    case fx_speed_2: return F("x2");break;
    case fx_speed_3: return F("x3");break;
    case fx_speed_4: return F("x4");break;
    case fx_speed_5: return F("x5");break;
    case fx_speed_6: return F("x6");break;
    case fx_speed_7: return F("x7");break;
    case fx_speed_8: return F("x8");break;
    case fx_speed_9: return F("x9");break;
    case fx_speed_10: return F("x10");break;
    case fx_speed_11: return F("x11");break;
    case fx_speed_12: return F("x12");break;
    case fx_speed_13: return F("x13");break;
    case fx_speed_14: return F("x14");break;
    case fx_speed_15: return F("x15");break;
    case fx_speed_16: return F("x16");break;
    case fx_speed_17: return F("x17");break;
    case fx_speed_18: return F("x18");break;
    case fx_speed_32: return F("x32");break;

    case fx_speed_pos: return F("speed pos");break;
    case fx_speed_neg: return F("speed neg");break;
    case fx_speed_inc: return F("speed inc");break;
    case fx_speed_dec: return F("speed dec");break;
    
    case fx_transition_fast: return F("t-fast");break;
    case fx_transition_timed_fade:return F("t-timed-fade");break;
    case fx_transition_timed_wipe_pos:return F("t-timed-wipe-pos");break;
    case fx_transition_timed_wipe_neg:return F("t-timed-wipe-neg");break;
    
    case fx_palette_lead:    return F("lead");break;    
    case fx_palette_follow:  return F("follow");break;       

    case fx_palette_lava: return F("lava");break;
    case fx_palette_cloud: return F("cloud");break;
    case fx_palette_ocean: return F("ocean");break;
    case fx_palette_forest: return F("forest");break;
    case fx_palette_rainbow: return F("rainbow");break;
    case fx_palette_rainbowstripe: return F("rainbowstripe");break;
    case fx_palette_party: return F("party");break;
    case fx_palette_heat: return F("heat");break;

    case fx_palette_dark:    return F("dark");break;
    case fx_palette_white:   return F("white");break;
    case fx_palette_red:     return F("red");break;
    case fx_palette_yellow:  return F("yellow");break;
    case fx_palette_green:   return F("green");break;
    case fx_palette_cyan:    return F("cyan");break;
    case fx_palette_blue:    return F("blue");break;
    case fx_palette_magenta: return F("magenta");break;
    case fx_palette_orange:  return F("orange");break;
   
    case fx_palette_dw: return F("dark-white");break;
    case fx_palette_dr: return F("dark-red");break;
    case fx_palette_dy: return F("dark-yellow");break;
    case fx_palette_dg: return F("dark-green");break;
    case fx_palette_dc: return F("dark-cyan");break;
    case fx_palette_db: return F("dark-blue");break;
    case fx_palette_dm: return F("dark-magenta");break;
    case fx_palette_wr: return F("white-red");break;
    case fx_palette_wy: return F("white-yellow");break;
    case fx_palette_wg: return F("white-green");break;
    case fx_palette_wc: return F("white-cyan");break;
    case fx_palette_wb: return F("white-blue");break;
    case fx_palette_wm: return F("white-magenta");break;
    case fx_palette_ry: return F("red-yellow");break;
    case fx_palette_rg: return F("red-green");break;
    case fx_palette_rc: return F("red-cyan");break;
    case fx_palette_rb: return F("red-blue");break;
    case fx_palette_rm: return F("red-magenta");break;
    case fx_palette_yg: return F("yellow-green");break;
    case fx_palette_yc: return F("yellow-cyan");break;
    case fx_palette_yb: return F("yellow-blue");break;
    case fx_palette_ym: return F("yellow-magenta");break;
    case fx_palette_gc: return F("green-cyan");break;
    case fx_palette_gb: return F("green-blue");break;
    case fx_palette_gm: return F("green-magenta");break;
    case fx_palette_cb: return F("cyan-blue");break;
    case fx_palette_cm: return F("cyan-magenta");break;
    case fx_palette_bm: return F("blue-magenta");break;

    case fx_palette_wry:return F("wry");break;
    case fx_palette_wrg:return F("wrg");break;
    case fx_palette_wrc:return F("wrc");break;
    case fx_palette_wrb:return F("wrb");break;
    case fx_palette_wrm:return F("wrm");break;
    case fx_palette_wyg:return F("wyg");break;
    case fx_palette_wyc:return F("wyc");break;
    case fx_palette_wyb:return F("wyb");break;
    case fx_palette_wym:return F("wym");break;
    case fx_palette_wgc:return F("wgc");break;
    case fx_palette_wgb:return F("wgb");break;
    case fx_palette_wgm:return F("wgm");break;
    case fx_palette_wcb:return F("wcb");break;
    case fx_palette_wcm:return F("wcm");break;
    case fx_palette_wbm:return F("wbm");break;

    case fx_palette_dry:return F("dry");break;
    case fx_palette_drg:return F("drg");break;
    case fx_palette_drc:return F("drc");break;
    case fx_palette_drb:return F("drb");break;
    case fx_palette_drm:return F("drm");break;
    case fx_palette_dyg:return F("dyg");break;
    case fx_palette_dyc:return F("dyc");break;
    case fx_palette_dyb:return F("dyb");break;
    case fx_palette_dym:return F("dym");break;
    case fx_palette_dgc:return F("dgc");break;
    case fx_palette_dgb:return F("dgb");break;
    case fx_palette_dgm:return F("dgm");break;
    case fx_palette_dcb:return F("dcb");break;
    case fx_palette_dcm:return F("dcm");break;
    case fx_palette_dbm:return F("dbm");break;    
    
    case fx_palette_rgb:return F("dgb");break;
    case fx_palette_cmy:return F("cmy");break;

    case fx_nothing:return F("nothing");break;
  }
}

enum FxTransitionType
{
  Transition_Instant      = 0,
  Transition_TimedFade    = 1,
  Transition_TimedWipePos = 2,
  Transition_TimedWipeNeg = 3,
};

struct FxController
{
  CRGBPalette16 currentPalette;
  CRGBPalette16 initialPalette;
  CRGBPalette16 nextPalette;
  FxTransitionType transitionType;
  int paletteSpeed = 0;
  int paletteDirection = 1;
  int paletteIndex = 0;
  bool animatePalette = false;
  float transitionMux = 0;
};
static FxController fxController;

void CreatePalette(CRGBPalette16 palette)
{
    if (fxController.transitionType == Transition_Instant)
    {
      fxController.currentPalette = palette;    
    }
    else if (fxController.transitionType == Transition_TimedFade)
    {
      fxController.nextPalette = palette;
      fxController.initialPalette = fxController.currentPalette; 
    }
    else if (fxController.transitionType == Transition_TimedWipePos)
    {
      fxController.nextPalette = palette;
      fxController.initialPalette = fxController.currentPalette; 
    }
    else if (fxController.transitionType == Transition_TimedWipeNeg)
    {
      fxController.nextPalette = palette;
      fxController.initialPalette = fxController.currentPalette; 
    }
    
}

void CreatePaletteBands(CRGB b0,CRGB b1,CRGB b2,CRGB b3, CRGB b4,CRGB b5,CRGB b6,CRGB b7, CRGB b8,CRGB b9,CRGB b10,CRGB b11, CRGB b12,CRGB b13,CRGB b14,CRGB b15)
{
  CreatePalette(CRGBPalette16(b0,b1,b2,b3, b4,b5,b6,b7, b8,b9,b10,b11, b12,b13,b14,b15));
  /*if (fxController.timedTransition)
    {
      fxController.nextPalette = CreatePalette(CRGBPalette16(b0,b1,b2,b3, b4,b5,b6,b7, b8,b9,b10,b11, b12,b13,b14,b15));
      CreateTimedTransition();
    }
    else fxController.currentPalette = CreatePalette(CRGBPalette16(b0,b1,b2,b3, b4,b5,b6,b7, b8,b9,b10,b11, b12,b13,b14,b15));*/
}

void CreateQuadBand(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3, uint8_t r4, uint8_t g4, uint8_t b4)
{
  CreatePaletteBands(CRGB(r1,g1,b1),CRGB(r2,g2,b2), CRGB(r3,g3,b3),CRGB(r4,g4,b4),
                     CRGB(r1,g1,b1),CRGB(r2,g2,b2), CRGB(r3,g3,b3),CRGB(r4,g4,b4),
                     CRGB(r1,g1,b1),CRGB(r2,g2,b2), CRGB(r3,g3,b3),CRGB(r4,g4,b4),
                     CRGB(r1,g1,b1),CRGB(r2,g2,b2), CRGB(r3,g3,b3),CRGB(r4,g4,b4));
}
void CreateTripleBand(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3)
{ 
  CreatePaletteBands(CRGB(r1,g1,b1),CRGB(r2,g2,b2),CRGB(r3,g3,b3),CRGB(r1,g1,b1),
                     CRGB(r2,g2,b2),CRGB(r3,g3,b3),CRGB(r1,g1,b1),CRGB(r2,g2,b2),
                     CRGB(r3,g3,b3),CRGB(r1,g1,b1),CRGB(r2,g2,b2),CRGB(r3,g3,b3),
                     CRGB(r1,g1,b1),CRGB(r2,g2,b2),CRGB(r3,g3,b3),CRGB(r1,g1,b1)
                     );
}
void CreateDoubleBand(uint8_t r1, uint8_t g1, uint8_t b1,uint8_t r2, uint8_t g2, uint8_t b2) { CreateQuadBand(r1,g1,b1,r2,g2,b2,r1,g1,b1,r2,g2,b2); }
void CreateSingleBand(uint8_t r, uint8_t g, uint8_t b) { CreateQuadBand(r,g,b,r,g,b,r,g,b,r,g,b); }


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
    case fx_palette_lava:CreatePalette(LavaColors_p);break;
    case fx_palette_cloud:CreatePalette(CloudColors_p);break;
    case fx_palette_ocean:CreatePalette(OceanColors_p);break;
    case fx_palette_forest:CreatePalette(ForestColors_p);break;
    case fx_palette_rainbow:CreatePalette(RainbowColors_p);break;
    case fx_palette_rainbowstripe:CreatePalette(RainbowStripeColors_p);break;
    case fx_palette_party:CreatePalette(PartyColors_p);break;
    case fx_palette_heat:CreatePalette(HeatColors_p);break;

    case fx_palette_dark:CreateSingleBand(DARK);break;
    case fx_palette_white:CreateSingleBand(WHITE);break;
    case fx_palette_red:CreateSingleBand(RED);break;
    case fx_palette_yellow:CreateSingleBand(YELLOW);break;
    case fx_palette_green:CreateSingleBand(GREEN);break;
    case fx_palette_cyan:CreateSingleBand(CYAN);break;
    case fx_palette_blue:CreateSingleBand(BLUE);break;
    case fx_palette_magenta:CreateSingleBand(MAGENTA);break;
    case fx_palette_orange:CreateSingleBand(ORANGE);break;
    
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

    case fx_palette_rgb: CreateTripleBand(RED, GREEN, BLUE);break;
    case fx_palette_cmy: CreateTripleBand(CYAN, MAGENTA, YELLOW);break;
  }
}

#endif
