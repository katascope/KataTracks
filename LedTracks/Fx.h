#if !defined FX_DEF
#define FX_DEF
#include <avr/pgmspace.h> 

#include "Config.h"

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


enum FxState
{
  FxState_Default       = 0,
  FxState_TestPattern   = 1,
  FxState_PlayingTrack  = 2,
  FxState_IMU           = 3,
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

  fx_palette_accel,
  fx_palette_gyro,

  fx_nothing = 255
};

struct Fx { unsigned long timecode; unsigned long event;   };

enum FxTransitionType
{
  Transition_Instant      = 0,
  Transition_TimedFade    = 1,
  Transition_TimedWipePos = 2,
  Transition_TimedWipeNeg = 3,
};

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
  bool animatePalette = false;
  float transitionMux = 0;
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
