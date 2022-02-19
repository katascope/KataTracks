#include <Arduino.h>
#include "Config.h"
#include "Fx.h"
//#include <avr/pgmspace.h> 

unsigned char lerp(float mux, unsigned char a, unsigned char b) { return (unsigned char)(a * (1.0 - mux) + b * mux); }
uint32_t LerpRGB(float t, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2) { return LEDRGB(lerp(t, r1, r2),lerp(t, g1, g2),lerp(t, b1, b2)); }
uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2) {
  unsigned char r1 = (rgb1 >> 16) & 0xFF;
  unsigned char g1 = (rgb1 >> 8) & 0xFF;
  unsigned char b1 = (rgb1 >> 0) & 0xFF;
  unsigned char r2 = (rgb2 >> 16) & 0xFF;
  unsigned char g2 = (rgb2 >> 8) & 0xFF;
  unsigned char b2 = (rgb2 >> 0) & 0xFF;
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
  return CRGB_DARK;
}

void PrintFxStateName(FxState s)
{
  switch (s)
  {
    case FxState_Default:       Serial.print("Norm"); break;
    case FxState_TestPattern:   Serial.print("Test"); break;
    case FxState_PlayingTrack:  Serial.print("Play"); break;
    case FxState_IMU:           Serial.print("IMU"); break;
    default: Serial.print("Unk");
  }
}

void PrintFxEventName(int event)
{
  switch(event)
  {
    case fx_speed_0: Serial.print(F("x0"));break;
    case fx_speed_1: Serial.print(F("x1"));break;
    case fx_speed_2: Serial.print(F("x2"));break;
    case fx_speed_3: Serial.print(F("x3"));break;
    case fx_speed_4: Serial.print(F("x4"));break;
    case fx_speed_5: Serial.print(F("x5"));break;
    case fx_speed_6: Serial.print(F("x6"));break;
    case fx_speed_7: Serial.print(F("x7"));break;
    case fx_speed_8: Serial.print(F("x8"));break;
    case fx_speed_9: Serial.print(F("x9"));break;
    case fx_speed_10: Serial.print(F("x10"));break;
    case fx_speed_11: Serial.print(F("x11"));break;
    case fx_speed_12: Serial.print(F("x12"));break;
    case fx_speed_13: Serial.print(F("x13"));break;
    case fx_speed_14: Serial.print(F("x14"));break;
    case fx_speed_15: Serial.print(F("x15"));break;
    case fx_speed_16: Serial.print(F("x16"));break;
    case fx_speed_17: Serial.print(F("x17"));break;
    case fx_speed_18: Serial.print(F("x18"));break;
    case fx_speed_32: Serial.print(F("x32"));break;

    case fx_speed_pos: Serial.print(F("speed pos"));break;
    case fx_speed_neg: Serial.print(F("speed neg"));break;
    case fx_speed_inc: Serial.print(F("speed inc"));break;
    case fx_speed_dec: Serial.print(F("speed dec"));break;
    
    case fx_transition_fast: Serial.print(F("t-fast"));break;
    case fx_transition_timed_fade:Serial.print(F("t-timed-fade"));break;
    case fx_transition_timed_wipe_pos:Serial.print(F("t-timed-wipe-pos"));break;
    case fx_transition_timed_wipe_neg:Serial.print(F("t-timed-wipe-neg"));break;
    
    case fx_palette_lead:    Serial.print(F("lead"));break;    
    case fx_palette_follow:  Serial.print(F("follow"));break;       

    case fx_palette_lava: Serial.print(F("lava"));break;
    case fx_palette_cloud: Serial.print(F("cloud"));break;
    case fx_palette_ocean: Serial.print(F("ocean"));break;
    case fx_palette_forest: Serial.print(F("forest"));break;
    case fx_palette_rainbow: Serial.print(F("rainbow"));break;
    case fx_palette_rainbowstripe: Serial.print(F("rainbowstripe"));break;
    case fx_palette_party: Serial.print(F("party"));break;
    case fx_palette_heat: Serial.print(F("heat"));break;

    case fx_palette_dark:    Serial.print(F("dark"));break;
    case fx_palette_white:   Serial.print(F("white"));break;
    case fx_palette_red:     Serial.print(F("red"));break;
    case fx_palette_yellow:  Serial.print(F("yellow"));break;
    case fx_palette_green:   Serial.print(F("green"));break;
    case fx_palette_cyan:    Serial.print(F("cyan"));break;
    case fx_palette_blue:    Serial.print(F("blue"));break;
    case fx_palette_magenta: Serial.print(F("magenta"));break;
    case fx_palette_orange:  Serial.print(F("orange"));break;
    case fx_palette_half:  Serial.print(F("half"));break;
    case fx_palette_lowhalf:  Serial.print(F("lowhalf"));break;

    case fx_palette_pulse_dark:    Serial.print(F("pulse-dark"));break;
    case fx_palette_pulse_white:   Serial.print(F("pulse-white"));break;
    case fx_palette_pulse_red:     Serial.print(F("pulse-red"));break;
    case fx_palette_pulse_yellow:  Serial.print(F("pulse-yellow"));break;
    case fx_palette_pulse_green:   Serial.print(F("pulse-green"));break;
    case fx_palette_pulse_cyan:    Serial.print(F("pulse-cyan"));break;
    case fx_palette_pulse_blue:    Serial.print(F("pulse-blue"));break;
    case fx_palette_pulse_magenta: Serial.print(F("pulse-magenta"));break;
    case fx_palette_pulse_orange:  Serial.print(F("pulse-orange"));break;
    case fx_palette_pulse_half:  Serial.print(F("pulse-half"));break;
    case fx_palette_pulse_lowhalf:  Serial.print(F("pulse-lowhalf"));break;
   
    case fx_palette_dw: Serial.print(F("dark-white"));break;
    case fx_palette_dr: Serial.print(F("dark-red"));break;
    case fx_palette_dy: Serial.print(F("dark-yellow"));break;
    case fx_palette_dg: Serial.print(F("dark-green"));break;
    case fx_palette_dc: Serial.print(F("dark-cyan"));break;
    case fx_palette_db: Serial.print(F("dark-blue"));break;
    case fx_palette_dm: Serial.print(F("dark-magenta"));break;
    case fx_palette_wr: Serial.print(F("white-red"));break;
    case fx_palette_wy: Serial.print(F("white-yellow"));break;
    case fx_palette_wg: Serial.print(F("white-green"));break;
    case fx_palette_wc: Serial.print(F("white-cyan"));break;
    case fx_palette_wb: Serial.print(F("white-blue"));break;
    case fx_palette_wm: Serial.print(F("white-magenta"));break;
    case fx_palette_ry: Serial.print(F("red-yellow"));break;
    case fx_palette_rg: Serial.print(F("red-green"));break;
    case fx_palette_rc: Serial.print(F("red-cyan"));break;
    case fx_palette_rb: Serial.print(F("red-blue"));break;
    case fx_palette_rm: Serial.print(F("red-magenta"));break;
    case fx_palette_yg: Serial.print(F("yellow-green"));break;
    case fx_palette_yc: Serial.print(F("yellow-cyan"));break;
    case fx_palette_yb: Serial.print(F("yellow-blue"));break;
    case fx_palette_ym: Serial.print(F("yellow-magenta"));break;
    case fx_palette_gc: Serial.print(F("green-cyan"));break;
    case fx_palette_gb: Serial.print(F("green-blue"));break;
    case fx_palette_gm: Serial.print(F("green-magenta"));break;
    case fx_palette_cb: Serial.print(F("cyan-blue"));break;
    case fx_palette_cm: Serial.print(F("cyan-magenta"));break;
    case fx_palette_bm: Serial.print(F("blue-magenta"));break;

    case fx_palette_wry:Serial.print(F("wry"));break;
    case fx_palette_wrg:Serial.print(F("wrg"));break;
    case fx_palette_wrc:Serial.print(F("wrc"));break;
    case fx_palette_wrb:Serial.print(F("wrb"));break;
    case fx_palette_wrm:Serial.print(F("wrm"));break;
    case fx_palette_wyg:Serial.print(F("wyg"));break;
    case fx_palette_wyc:Serial.print(F("wyc"));break;
    case fx_palette_wyb:Serial.print(F("wyb"));break;
    case fx_palette_wym:Serial.print(F("wym"));break;
    case fx_palette_wgc:Serial.print(F("wgc"));break;
    case fx_palette_wgb:Serial.print(F("wgb"));break;
    case fx_palette_wgm:Serial.print(F("wgm"));break;
    case fx_palette_wcb:Serial.print(F("wcb"));break;
    case fx_palette_wcm:Serial.print(F("wcm"));break;
    case fx_palette_wbm:Serial.print(F("wbm"));break;

    case fx_palette_dry:Serial.print(F("dry"));break;
    case fx_palette_drg:Serial.print(F("drg"));break;
    case fx_palette_drc:Serial.print(F("drc"));break;
    case fx_palette_drb:Serial.print(F("drb"));break;
    case fx_palette_drm:Serial.print(F("drm"));break;
    case fx_palette_dyg:Serial.print(F("dyg"));break;
    case fx_palette_dyc:Serial.print(F("dyc"));break;
    case fx_palette_dyb:Serial.print(F("dyb"));break;
    case fx_palette_dym:Serial.print(F("dym"));break;
    case fx_palette_dgc:Serial.print(F("dgc"));break;
    case fx_palette_dgb:Serial.print(F("dgb"));break;
    case fx_palette_dgm:Serial.print(F("dgm"));break;
    case fx_palette_dcb:Serial.print(F("dcb"));break;
    case fx_palette_dcm:Serial.print(F("dcm"));break;
    case fx_palette_dbm:Serial.print(F("dbm"));break;

    case fx_palette_accel:Serial.print(F("accel"));break;
    case fx_palette_gyro:Serial.print(F("gyro"));break;

    case fx_nothing:Serial.print(F("nothing"));break;
  }
}

void PrintFxTransitionName(FxTransitionType t)
{
  switch (t)
  {
    case Transition_Instant:      Serial.print(F("Fast")); break;
    case Transition_TimedFade:    Serial.print(F("Fade")); break;
    case Transition_TimedWipePos: Serial.print(F("Wip+")); break;
    case Transition_TimedWipeNeg: Serial.print(F("Wip-")); break;
    default: Serial.print("Unknown");
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

enum    CRGB {
  AliceBlue =0xF0F8FF, Amethyst =0x9966CC, AntiqueWhite =0xFAEBD7, Aqua =0x00FFFF,
  Aquamarine =0x7FFFD4, Azure =0xF0FFFF, Beige =0xF5F5DC, Bisque =0xFFE4C4,
  Black =0x000000, BlanchedAlmond =0xFFEBCD, Blue =0x0000FF, BlueViolet =0x8A2BE2,
  Brown =0xA52A2A, BurlyWood =0xDEB887, CadetBlue =0x5F9EA0, Chartreuse =0x7FFF00,
  Chocolate =0xD2691E, Coral =0xFF7F50, CornflowerBlue =0x6495ED, Cornsilk =0xFFF8DC,
  Crimson =0xDC143C, Cyan =0x00FFFF, DarkBlue =0x00008B, DarkCyan =0x008B8B,
  DarkGoldenrod =0xB8860B, DarkGray =0xA9A9A9, DarkGrey =0xA9A9A9, DarkGreen =0x006400,
  DarkKhaki =0xBDB76B, DarkMagenta =0x8B008B, DarkOliveGreen =0x556B2F, DarkOrange =0xFF8C00,
  DarkOrchid =0x9932CC, DarkRed =0x8B0000, DarkSalmon =0xE9967A, DarkSeaGreen =0x8FBC8F,
  DarkSlateBlue =0x483D8B, DarkSlateGray =0x2F4F4F, DarkSlateGrey =0x2F4F4F, DarkTurquoise =0x00CED1,
  DarkViolet =0x9400D3, DeepPink =0xFF1493, DeepSkyBlue =0x00BFFF, DimGray =0x696969,
  DimGrey =0x696969, DodgerBlue =0x1E90FF, FireBrick =0xB22222, FloralWhite =0xFFFAF0,
  ForestGreen =0x228B22, Fuchsia =0xFF00FF, Gainsboro =0xDCDCDC, GhostWhite =0xF8F8FF,
  Gold =0xFFD700, Goldenrod =0xDAA520, Gray =0x808080, Grey =0x808080,
  Green =0x008000, GreenYellow =0xADFF2F, Honeydew =0xF0FFF0, HotPink =0xFF69B4,
  IndianRed =0xCD5C5C, Indigo =0x4B0082, Ivory =0xFFFFF0, Khaki =0xF0E68C,
  Lavender =0xE6E6FA, LavenderBlush =0xFFF0F5, LawnGreen =0x7CFC00, LemonChiffon =0xFFFACD,
  LightBlue =0xADD8E6, LightCoral =0xF08080, LightCyan =0xE0FFFF, LightGoldenrodYellow =0xFAFAD2,
  LightGreen =0x90EE90, LightGrey =0xD3D3D3, LightPink =0xFFB6C1, LightSalmon =0xFFA07A,
  LightSeaGreen =0x20B2AA, LightSkyBlue =0x87CEFA, LightSlateGray =0x778899, LightSlateGrey =0x778899,
  LightSteelBlue =0xB0C4DE, LightYellow =0xFFFFE0, Lime =0x00FF00, LimeGreen =0x32CD32,
  Linen =0xFAF0E6, Magenta =0xFF00FF, Maroon =0x800000, MediumAquamarine =0x66CDAA,
  MediumBlue =0x0000CD, MediumOrchid =0xBA55D3, MediumPurple =0x9370DB, MediumSeaGreen =0x3CB371,
  MediumSlateBlue =0x7B68EE, MediumSpringGreen =0x00FA9A, MediumTurquoise =0x48D1CC, MediumVioletRed =0xC71585,
  MidnightBlue =0x191970, MintCream =0xF5FFFA, MistyRose =0xFFE4E1, Moccasin =0xFFE4B5,
  NavajoWhite =0xFFDEAD, Navy =0x000080, OldLace =0xFDF5E6, Olive =0x808000,
  OliveDrab =0x6B8E23, Orange =0xFFA500, OrangeRed =0xFF4500, Orchid =0xDA70D6,
  PaleGoldenrod =0xEEE8AA, PaleGreen =0x98FB98, PaleTurquoise =0xAFEEEE, PaleVioletRed =0xDB7093,
  PapayaWhip =0xFFEFD5, PeachPuff =0xFFDAB9, Peru =0xCD853F, Pink =0xFFC0CB,
  Plaid =0xCC5533, Plum =0xDDA0DD, PowderBlue =0xB0E0E6, Purple =0x800080,
  Red =0xFF0000, RosyBrown =0xBC8F8F, RoyalBlue =0x4169E1, SaddleBrown =0x8B4513,
  Salmon =0xFA8072, SandyBrown =0xF4A460, SeaGreen =0x2E8B57, Seashell =0xFFF5EE,
  Sienna =0xA0522D, Silver =0xC0C0C0, SkyBlue =0x87CEEB, SlateBlue =0x6A5ACD,
  SlateGray =0x708090, SlateGrey =0x708090, Snow =0xFFFAFA, SpringGreen =0x00FF7F,
  SteelBlue =0x4682B4, Tan =0xD2B48C, Teal =0x008080, Thistle =0xD8BFD8,
  Tomato =0xFF6347, Turquoise =0x40E0D0, Violet =0xEE82EE, Wheat =0xF5DEB3,
  White =0xFFFFFF, WhiteSmoke =0xF5F5F5, Yellow =0xFFFF00, YellowGreen =0x9ACD32,
  FairyLight =0xFFE42D, FairyLightNCC =0xFF9D2A
};

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
    case fx_transition_timed_wipe_pos:fxc.transitionType = Transition_TimedWipePos;fxc.paletteIndex = 0;fxc.updatePalette = false;break;
    case fx_transition_timed_wipe_neg:fxc.transitionType = Transition_TimedWipeNeg;fxc.paletteIndex = 15;fxc.updatePalette = false;break;

    case fx_palette_lead:CreateSingleBand(fxc, BLUE);break;
    case fx_palette_follow:CreateSingleBand(fxc, RED);break;

    //case fx_palette_dark:break;//CreateDefaultBand(DARK);break;
    case fx_palette_lava:CreatePaletteBands(fxc,
        CRGB::Black,CRGB::Maroon,CRGB::Black,CRGB::Maroon,    
        CRGB::DarkRed,CRGB::Maroon,CRGB::DarkRed,CRGB::DarkRed,    
        CRGB::DarkRed,CRGB::DarkRed,CRGB::Red,CRGB::Orange,    
        CRGB::White,CRGB::Orange,CRGB::Red,CRGB::DarkRed);
      break;
    case fx_palette_cloud:CreatePaletteBands(fxc,  
      CRGB::Blue,CRGB::DarkBlue,CRGB::DarkBlue,CRGB::DarkBlue,
      CRGB::DarkBlue,CRGB::DarkBlue,CRGB::DarkBlue,CRGB::DarkBlue,
      CRGB::Blue,CRGB::DarkBlue,CRGB::SkyBlue,CRGB::SkyBlue,
      CRGB::LightBlue,CRGB::White,CRGB::LightBlue,CRGB::SkyBlue);
      break;
    case fx_palette_ocean:CreatePaletteBands(fxc,    
      CRGB::DarkGreen,
      CRGB::DarkGreen,
      CRGB::DarkOliveGreen,
      CRGB::DarkGreen,
  
      CRGB::Green,
      CRGB::ForestGreen,
      CRGB::OliveDrab,
      CRGB::Green,
  
      CRGB::SeaGreen,
      CRGB::MediumAquamarine,
      CRGB::LimeGreen,
      CRGB::YellowGreen,
  
      CRGB::LightGreen,
      CRGB::LawnGreen,
      CRGB::MediumAquamarine,
      CRGB::ForestGreen);break;
    case fx_palette_forest:CreatePaletteBands(fxc,    
      CRGB::DarkGreen,
      CRGB::DarkGreen,
      CRGB::DarkOliveGreen,
      CRGB::DarkGreen,
  
      CRGB::Green,
      CRGB::ForestGreen,
      CRGB::OliveDrab,
      CRGB::Green,
  
      CRGB::SeaGreen,
      CRGB::MediumAquamarine,
      CRGB::LimeGreen,
      CRGB::YellowGreen,
  
      CRGB::LightGreen,
      CRGB::LawnGreen,
      CRGB::MediumAquamarine,
      CRGB::ForestGreen);break;
    case fx_palette_rainbow:CreatePaletteBands(fxc, 
      0xFF0000, 0xD52A00, 0xAB5500, 0xAB7F00,
      0xABAB00, 0x56D500, 0x00FF00, 0x00D52A,
      0x00AB55, 0x0056AA, 0x0000FF, 0x2A00D5,
      0x5500AB, 0x7F0081, 0xAB0055, 0xD5002B);break;
    case fx_palette_rainbowstripe:CreatePaletteBands(fxc,    
      0xFF0000, 0x000000, 0xAB5500, 0x000000,
      0xABAB00, 0x000000, 0x00FF00, 0x000000,
      0x00AB55, 0x000000, 0x0000FF, 0x000000,
      0x5500AB, 0x000000, 0xAB0055, 0x000000);break;
    case fx_palette_party:CreatePaletteBands(fxc,   
      0x5500AB, 0x84007C, 0xB5004B, 0xE5001B,
      0xE81700, 0xB84700, 0xAB7700, 0xABAB00,
      0xAB5500, 0xDD2200, 0xF2000E, 0xC2003E,
      0x8F0071, 0x5F00A1, 0x2F00D0, 0x0007F9);break;
    case fx_palette_heat:CreatePaletteBands(fxc,
      0x000000, 0x330000, 0x660000, 0x990000, 
      0xCC0000, 0xFF0000, 0xFF3300, 0xFF6600, 
      0xFF9900, 0xFFCC00, 0xFFFF00, 0xFFFF33, 
      0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF);break;
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
