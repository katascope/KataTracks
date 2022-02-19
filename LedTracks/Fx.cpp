#include "Fx.h"
#include <Arduino.h> 
//#include "Palette.h"
#define NUM_LEDS   80
uint8_t lerp(float mux, uint8_t a, uint8_t b) { return (uint8_t)(a * (1.0 - mux) + b * mux); }
uint32_t LerpRGB(float t, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2) { return LEDRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2)); }
uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2) {
  byte r1 = (rgb1 >> 16) & 0xFF;
  byte g1 = (rgb1 >> 8) & 0xFF;
  byte b1 = (rgb1 >> 0) & 0xFF;
  byte r2 = (rgb2 >> 16) & 0xFF;
  byte g2 = (rgb2 >> 8) & 0xFF;
  byte b2 = (rgb2 >> 0) & 0xFF;
  return LEDRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2));
}

uint32_t ShortnameToCRGB(char shortName)
{
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

String FxStateName(FxState s)
{
  switch (s)
  {
    case FxState_Default:       return F("Norm"); break;
    case FxState_TestPattern:   return F("Test"); break;
    case FxState_PlayingTrack:  return F("Play"); break;
    case FxState_IMU:           return F("IMU"); break;
    default: return F("Unknown");
  }
}

String FxEventName(int event)
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

    case fx_palette_accel:return F("accel");
    case fx_palette_gyro:return F("gyro");

    case fx_nothing:return F("nothing");
  }
  return F("unk");
}

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


void CreatePalette(FxController &fxController, uint32_t *pal16)
{
    if (fxController.transitionType == Transition_Instant)
    {
      SetPalette16(fxController.palette, pal16);
    }
    else if (fxController.transitionType == Transition_TimedFade)
    {
      CopyPalette(fxController.initialPalette, fxController.palette);
      SetPalette16(fxController.nextPalette, pal16);
    }
    else if (fxController.transitionType == Transition_TimedWipePos)
    {
      SayPalette(fxController.palette);
      SayPalette(fxController.initialPalette);
      SayPalette(fxController.nextPalette);
      CopyPalette(fxController.initialPalette, fxController.palette);
      SetPalette16(fxController.nextPalette, pal16);
      SayPalette(fxController.palette);
      SayPalette(fxController.initialPalette);
      SayPalette(fxController.nextPalette);
    }
    else if (fxController.transitionType == Transition_TimedWipeNeg)
    {
      CopyPalette(fxController.initialPalette, fxController.palette);
      SetPalette16(fxController.nextPalette, pal16);
    }
}

void CreatePaletteBands(FxController &fxc, uint32_t b0,uint32_t b1,uint32_t b2,uint32_t b3, uint32_t b4,uint32_t b5,uint32_t b6,uint32_t b7,
                        uint32_t b8,uint32_t b9,uint32_t b10,uint32_t b11, uint32_t b12,uint32_t b13,uint32_t b14,uint32_t b15)
{
  float scaling = (float)(NUM_LEDS)/16.0f;
  uint32_t palette16[16] = { b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15};
  CreatePalette(fxc, palette16);
}

void CreateQuadBand(FxController &fxc, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3, uint8_t r4, uint8_t g4, uint8_t b4)
{
  CreatePaletteBands(fxc, LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2), LEDRGB(r3,g3,b3),LEDRGB(r4,g4,b4));
}
void CreateTripleBand(FxController &fxc, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t r3, uint8_t g3, uint8_t b3)
{
  CreatePaletteBands(fxc, LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1),
                     LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),
                     LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),
                     LEDRGB(r1,g1,b1),LEDRGB(r2,g2,b2),LEDRGB(r3,g3,b3),LEDRGB(r1,g1,b1)
                     );
}
void CreateDoubleBand(FxController &fxc, uint8_t r1, uint8_t g1, uint8_t b1,uint8_t r2, uint8_t g2, uint8_t b2) { CreateQuadBand(fxc, r1,g1,b1, r2,g2,b2, r1,g1,b1, r2,g2,b2);}
void CreateSingleBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) { CreateQuadBand(fxc, r,g,b,r,g,b,r,g,b,r,g,b); }
void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) {
  CreatePaletteBands(fxc, LEDRGB(r/2,g/2,b/2),LEDRGB(r,g,b),LEDRGB(r/2,g/2,b/2),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0));
}

void FxEventProcess(FxController &fxc,int event)
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
      fxc.paletteSpeed = event;
      break;
    case fx_speed_32:
      fxc.paletteSpeed = 32;
      break;

    case fx_speed_pos:fxc.paletteDirection = 1;break;
    case fx_speed_neg:fxc.paletteDirection = -1;break;

    case fx_speed_inc:
      fxc.paletteSpeed++;
      if (fxc.paletteSpeed >= 18)
        fxc.paletteSpeed = 18;
      break;
    case fx_speed_dec:
      fxc.paletteSpeed--;
      if (fxc.paletteSpeed < 0)
        fxc.paletteSpeed = 0;
      break;
    case fx_transition_fast:fxc.transitionType = Transition_Instant;break;
    case fx_transition_timed_fade:fxc.transitionType = Transition_TimedFade;break;
    case fx_transition_timed_wipe_pos:fxc.transitionType = Transition_TimedWipePos;fxc.paletteIndex = 0;fxc.animatePalette = false;break;
    case fx_transition_timed_wipe_neg:fxc.transitionType = Transition_TimedWipeNeg;fxc.paletteIndex = 15;fxc.animatePalette = false;break;

    case fx_palette_lead:CreateSingleBand(fxc, BLUE);break;
    case fx_palette_follow:CreateSingleBand(fxc, RED);break;

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
    case fx_palette_dark:CreateSingleBand(fxc, DARK);break;
    case fx_palette_white:CreateSingleBand(fxc, WHITE);break;
    case fx_palette_red:CreateSingleBand(fxc, RED);break;
    case fx_palette_yellow:CreateSingleBand(fxc, YELLOW);break;
    case fx_palette_green:CreateSingleBand(fxc, GREEN);break;
    case fx_palette_cyan:CreateSingleBand(fxc, CYAN);break;
    case fx_palette_blue:CreateSingleBand(fxc, BLUE);break;
    case fx_palette_magenta:CreateSingleBand(fxc, MAGENTA);break;
    case fx_palette_orange:CreateSingleBand(fxc, ORANGE);break;
    case fx_palette_half:CreateSingleBand(fxc, HALF);break;
    case fx_palette_lowhalf:CreateSingleBand(fxc, LOWHALF);break;

    case fx_palette_pulse_dark:CreateSinglePulseBand(fxc, DARK);break;
    case fx_palette_pulse_white:CreateSinglePulseBand(fxc, WHITE);break;
    case fx_palette_pulse_red:CreateSinglePulseBand(fxc, RED);break;
    case fx_palette_pulse_yellow:CreateSinglePulseBand(fxc, YELLOW);break;
    case fx_palette_pulse_green:CreateSinglePulseBand(fxc, GREEN);break;
    case fx_palette_pulse_cyan:CreateSinglePulseBand(fxc, CYAN);break;
    case fx_palette_pulse_blue:CreateSinglePulseBand(fxc, BLUE);break;
    case fx_palette_pulse_magenta:CreateSinglePulseBand(fxc, MAGENTA);break;
    case fx_palette_pulse_orange:CreateSinglePulseBand(fxc, ORANGE);break;
    case fx_palette_pulse_half:CreateSinglePulseBand(fxc, HALF);break;
    case fx_palette_pulse_lowhalf:CreateSinglePulseBand(fxc, LOWHALF);break;
    
    case fx_palette_dr: CreateDoubleBand(fxc, DARK, RED); break;
    case fx_palette_dy: CreateDoubleBand(fxc, DARK, YELLOW); break;
    case fx_palette_dg: CreateDoubleBand(fxc, DARK, GREEN); break;
    case fx_palette_dc: CreateDoubleBand(fxc, DARK, CYAN); break;
    case fx_palette_db: CreateDoubleBand(fxc, DARK, BLUE); break;
    case fx_palette_dm: CreateDoubleBand(fxc, DARK, MAGENTA); break;
    case fx_palette_wr: CreateDoubleBand(fxc, WHITE, RED); break;
    case fx_palette_wy: CreateDoubleBand(fxc, WHITE, YELLOW); break;
    case fx_palette_wg: CreateDoubleBand(fxc, WHITE, GREEN); break;
    case fx_palette_wc: CreateDoubleBand(fxc, WHITE, CYAN); break;
    case fx_palette_wb: CreateDoubleBand(fxc, WHITE, BLUE); break;
    case fx_palette_wm: CreateDoubleBand(fxc, WHITE, MAGENTA); break;
    case fx_palette_ry: CreateDoubleBand(fxc, RED, YELLOW); break;
    case fx_palette_rg: CreateDoubleBand(fxc, RED, GREEN); break;
    case fx_palette_rc: CreateDoubleBand(fxc, RED, CYAN); break;
    case fx_palette_rb: CreateDoubleBand(fxc, RED, BLUE); break;
    case fx_palette_rm: CreateDoubleBand(fxc, RED, MAGENTA); break;
    case fx_palette_yg: CreateDoubleBand(fxc, YELLOW, GREEN); break;
    case fx_palette_yc: CreateDoubleBand(fxc, YELLOW, CYAN); break;
    case fx_palette_yb: CreateDoubleBand(fxc, YELLOW, BLUE); break;
    case fx_palette_ym: CreateDoubleBand(fxc, YELLOW, MAGENTA); break;
    case fx_palette_gc: CreateDoubleBand(fxc, GREEN, CYAN); break;
    case fx_palette_gb: CreateDoubleBand(fxc, GREEN, BLUE); break;
    case fx_palette_gm: CreateDoubleBand(fxc, GREEN, MAGENTA); break;
    case fx_palette_cb: CreateDoubleBand(fxc, CYAN, BLUE); break;
    case fx_palette_cm: CreateDoubleBand(fxc, CYAN, MAGENTA); break;
    case fx_palette_bm: CreateDoubleBand(fxc, BLUE, MAGENTA); break;

    case fx_palette_wry: CreateQuadBand(fxc, WHITE, RED,    WHITE, YELLOW); break;
    case fx_palette_wrg: CreateQuadBand(fxc, WHITE, RED,    WHITE, GREEN); break;
    case fx_palette_wrc: CreateQuadBand(fxc, WHITE, RED,    WHITE, CYAN); break;
    case fx_palette_wrb: CreateQuadBand(fxc, WHITE, RED,    WHITE, BLUE); break;
    case fx_palette_wrm: CreateQuadBand(fxc, WHITE, RED,    WHITE, MAGENTA); break;
    case fx_palette_wyg: CreateQuadBand(fxc, WHITE, YELLOW, WHITE, GREEN); break;
    case fx_palette_wyc: CreateQuadBand(fxc, WHITE, YELLOW, WHITE, CYAN); break;
    case fx_palette_wyb: CreateQuadBand(fxc, WHITE, YELLOW, WHITE, BLUE); break;
    case fx_palette_wym: CreateQuadBand(fxc, WHITE, YELLOW, WHITE, MAGENTA); break;
    case fx_palette_wgc: CreateQuadBand(fxc, WHITE, GREEN,  WHITE, CYAN); break;
    case fx_palette_wgb: CreateQuadBand(fxc, WHITE, GREEN,  WHITE, BLUE); break;
    case fx_palette_wgm: CreateQuadBand(fxc, WHITE, GREEN,  WHITE, MAGENTA); break;
    case fx_palette_wcb: CreateQuadBand(fxc, WHITE, CYAN,   WHITE, BLUE); break;
    case fx_palette_wcm: CreateQuadBand(fxc, WHITE, CYAN,   WHITE, MAGENTA); break;
    case fx_palette_wbm: CreateQuadBand(fxc, WHITE, BLUE,   WHITE, MAGENTA); break;

    case fx_palette_dry: CreateQuadBand(fxc, DARK, RED,    DARK, YELLOW); break;
    case fx_palette_drg: CreateQuadBand(fxc, DARK, RED,    DARK, GREEN); break;
    case fx_palette_drc: CreateQuadBand(fxc, DARK, RED,    DARK, CYAN); break;
    case fx_palette_drb: CreateQuadBand(fxc, DARK, RED,    DARK, BLUE); break;
    case fx_palette_drm: CreateQuadBand(fxc, DARK, RED,    DARK, MAGENTA); break;
    case fx_palette_dyg: CreateQuadBand(fxc, DARK, YELLOW, DARK, GREEN); break;
    case fx_palette_dyc: CreateQuadBand(fxc, DARK, YELLOW, DARK, CYAN); break;
    case fx_palette_dyb: CreateQuadBand(fxc, DARK, YELLOW, DARK, BLUE); break;
    case fx_palette_dym: CreateQuadBand(fxc, DARK, YELLOW, DARK, MAGENTA); break;
    case fx_palette_dgc: CreateQuadBand(fxc, DARK, GREEN,  DARK, CYAN); break;
    case fx_palette_dgb: CreateQuadBand(fxc, DARK, GREEN,  DARK, BLUE); break;
    case fx_palette_dgm: CreateQuadBand(fxc, DARK, GREEN,  DARK, MAGENTA); break;
    case fx_palette_dcb: CreateQuadBand(fxc, DARK, CYAN,   DARK, BLUE); break;
    case fx_palette_dcm: CreateQuadBand(fxc, DARK, CYAN,   DARK, MAGENTA); break;
    case fx_palette_dbm: CreateQuadBand(fxc, DARK, BLUE,   DARK, MAGENTA); break;

    /*case fx_palette_accel: 
    {
      byte r = (float)((float)127.0f-(float)imuAccelX*120.0f);
      byte g = (float)((float)127.0f-(float)imuAccelY*120.0f);
      byte b = (float)((float)127.0f-(float)imuAccelZ*120.0f);
      CreateSingleBand(r,g,b);
      break;
    }
    case fx_palette_gyro: 
    {
      byte r = (float)((float)127.0f-(float)imuGyroX*120.0f);
      byte g = (float)((float)127.0f-(float)imuGyroY*120.0f);
      byte b = (float)((float)127.0f-(float)imuGyroZ*120.0f);
      CreateSingleBand(r,g,b);
      break;
    }*/
 }
}
