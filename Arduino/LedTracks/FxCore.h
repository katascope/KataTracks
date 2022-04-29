#ifndef FX_TYPES_DEF
#define FX_TYPES_DEF
#include <Arduino.h>

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

enum FxPaletteUpdateType
{
  None,
  Once,
  Done,
  Always
};

enum FxState
{
  FxState_Default       = 0,
  FxState_TestPattern   = 1,
  FxState_PlayingTrack  = 2,
  FxState_IMU           = 3,
  FxState_MIC           = 4,
};

/*
   Event types:
    Adjust speed/dir
    Track play/stop
    Transition
     Fast
     Timed
     WipePos
     WipeNeg
    Drive off value
     Test
     IMU
    Effects
     Sparkle "until next"? or on/off
      Single: fx_sparkles_on and fx_sparkles_off
     One-Off effect
     Brightness change
*/
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

  fx_transition_fast,
  fx_transition_timed_fade,
  fx_transition_timed_wipe_pos,
  fx_transition_timed_wipe_neg,
  fx_transition_timed_wipe_outin,
  fx_transition_timed_wipe_inout,

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

  fx_palette_pulse2_dark,
  fx_palette_pulse2_white,
  fx_palette_pulse2_red,
  fx_palette_pulse2_yellow,
  fx_palette_pulse2_green,
  fx_palette_pulse2_cyan,
  fx_palette_pulse2_blue,
  fx_palette_pulse2_magenta,
  fx_palette_pulse2_orange,
  fx_palette_pulse2_half,
  fx_palette_pulse2_lowhalf,  

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
  fx_palette_mic,

  fx_color1_dark,
  fx_color1_white,
  fx_color1_red,
  fx_color1_yellow,
  fx_color1_green,
  fx_color1_cyan,
  fx_color1_blue,
  fx_color1_magenta,
  fx_color1_orange,
  fx_color1_half,
  fx_color1_lowhalf,

  fx_color2_dark,
  fx_color2_white,
  fx_color2_red,
  fx_color2_yellow,
  fx_color2_green,
  fx_color2_cyan,
  fx_color2_blue,
  fx_color2_magenta,
  fx_color2_orange,
  fx_color2_half,
  fx_color2_lowhalf,

  fx_color3_dark,
  fx_color3_white,
  fx_color3_red,
  fx_color3_yellow,
  fx_color3_green,
  fx_color3_cyan,
  fx_color3_blue,
  fx_color3_magenta,
  fx_color3_orange,
  fx_color3_half,
  fx_color3_lowhalf,

  fx_colors1,
  fx_colors2,
  fx_colors3,
  fx_colors4,
  fx_colors5,
  fx_colors6,
  fx_colors7,
  fx_colors8,
  fx_colors9,
  fx_colors10,
  fx_colors11,
  fx_colors12,
  fx_colors13,
  fx_colors14,
  fx_colors15,
  fx_colors16,

  fx_nothing = 255
};

struct Fx {
  unsigned long timecode;
  unsigned long event;
};

enum FxTransitionType
{
  Transition_Instant        = 0,
  Transition_TimedFade      = 1,
  Transition_TimedWipePos   = 2,
  Transition_TimedWipeNeg   = 3,
  Transition_TimedWipeOutIn = 4,
  Transition_TimedWipeInOut = 5,
};

enum FxTrackEndAction
{
  StopAtEnd = 0,
  LoopAtEnd = 1
};

enum    WEBRGB {
  AliceBlue = 0xF0F8FF, Amethyst = 0x9966CC, AntiqueWhite = 0xFAEBD7, Aqua = 0x00FFFF,
  Aquamarine = 0x7FFFD4, Azure = 0xF0FFFF, Beige = 0xF5F5DC, Bisque = 0xFFE4C4,
  Black = 0x000000, BlanchedAlmond = 0xFFEBCD, Blue = 0x0000FF, BlueViolet = 0x8A2BE2,
  Brown = 0xA52A2A, BurlyWood = 0xDEB887, CadetBlue = 0x5F9EA0, Chartreuse = 0x7FFF00,
  Chocolate = 0xD2691E, Coral = 0xFF7F50, CornflowerBlue = 0x6495ED, Cornsilk = 0xFFF8DC,
  Crimson = 0xDC143C, Cyan = 0x00FFFF, DarkBlue = 0x00008B, DarkCyan = 0x008B8B,
  DarkGoldenrod = 0xB8860B, DarkGray = 0xA9A9A9, DarkGrey = 0xA9A9A9, DarkGreen = 0x006400,
  DarkKhaki = 0xBDB76B, DarkMagenta = 0x8B008B, DarkOliveGreen = 0x556B2F, DarkOrange = 0xFF8C00,
  DarkOrchid = 0x9932CC, DarkRed = 0x8B0000, DarkSalmon = 0xE9967A, DarkSeaGreen = 0x8FBC8F,
  DarkSlateBlue = 0x483D8B, DarkSlateGray = 0x2F4F4F, DarkSlateGrey = 0x2F4F4F, DarkTurquoise = 0x00CED1,
  DarkViolet = 0x9400D3, DeepPink = 0xFF1493, DeepSkyBlue = 0x00BFFF, DimGray = 0x696969,
  DimGrey = 0x696969, DodgerBlue = 0x1E90FF, FireBrick = 0xB22222, FloralWhite = 0xFFFAF0,
  ForestGreen = 0x228B22, Fuchsia = 0xFF00FF, Gainsboro = 0xDCDCDC, GhostWhite = 0xF8F8FF,
  Gold = 0xFFD700, Goldenrod = 0xDAA520, Gray = 0x808080, Grey = 0x808080,
  Green = 0x008000, GreenYellow = 0xADFF2F, Honeydew = 0xF0FFF0, HotPink = 0xFF69B4,
  IndianRed = 0xCD5C5C, Indigo = 0x4B0082, Ivory = 0xFFFFF0, Khaki = 0xF0E68C,
  Lavender = 0xE6E6FA, LavenderBlush = 0xFFF0F5, LawnGreen = 0x7CFC00, LemonChiffon = 0xFFFACD,
  LightBlue = 0xADD8E6, LightCoral = 0xF08080, LightCyan = 0xE0FFFF, LightGoldenrodYellow = 0xFAFAD2,
  LightGreen = 0x90EE90, LightGrey = 0xD3D3D3, LightPink = 0xFFB6C1, LightSalmon = 0xFFA07A,
  LightSeaGreen = 0x20B2AA, LightSkyBlue = 0x87CEFA, LightSlateGray = 0x778899, LightSlateGrey = 0x778899,
  LightSteelBlue = 0xB0C4DE, LightYellow = 0xFFFFE0, Lime = 0x00FF00, LimeGreen = 0x32CD32,
  Linen = 0xFAF0E6, Magenta = 0xFF00FF, Maroon = 0x800000, MediumAquamarine = 0x66CDAA,
  MediumBlue = 0x0000CD, MediumOrchid = 0xBA55D3, MediumPurple = 0x9370DB, MediumSeaGreen = 0x3CB371,
  MediumSlateBlue = 0x7B68EE, MediumSpringGreen = 0x00FA9A, MediumTurquoise = 0x48D1CC, MediumVioletRed = 0xC71585,
  MidnightBlue = 0x191970, MintCream = 0xF5FFFA, MistyRose = 0xFFE4E1, Moccasin = 0xFFE4B5,
  NavajoWhite = 0xFFDEAD, Navy = 0x000080, OldLace = 0xFDF5E6, Olive = 0x808000,
  OliveDrab = 0x6B8E23, Orange = 0xFFA500, OrangeRed = 0xFF4500, Orchid = 0xDA70D6,
  PaleGoldenrod = 0xEEE8AA, PaleGreen = 0x98FB98, PaleTurquoise = 0xAFEEEE, PaleVioletRed = 0xDB7093,
  PapayaWhip = 0xFFEFD5, PeachPuff = 0xFFDAB9, Peru = 0xCD853F, Pink = 0xFFC0CB,
  Plaid = 0xCC5533, Plum = 0xDDA0DD, PowderBlue = 0xB0E0E6, Purple = 0x800080,
  Red = 0xFF0000, RosyBrown = 0xBC8F8F, RoyalBlue = 0x4169E1, SaddleBrown = 0x8B4513,
  Salmon = 0xFA8072, SandyBrown = 0xF4A460, SeaGreen = 0x2E8B57, Seashell = 0xFFF5EE,
  Sienna = 0xA0522D, Silver = 0xC0C0C0, SkyBlue = 0x87CEEB, SlateBlue = 0x6A5ACD,
  SlateGray = 0x708090, SlateGrey = 0x708090, Snow = 0xFFFAFA, SpringGreen = 0x00FF7F,
  SteelBlue = 0x4682B4, Tan = 0xD2B48C, Teal = 0x008080, Thistle = 0xD8BFD8,
  Tomato = 0xFF6347, Turquoise = 0x40E0D0, Violet = 0xEE82EE, Wheat = 0xF5DEB3,
  White = 0xFFFFFF, WhiteSmoke = 0xF5F5F5, Yellow = 0xFFFF00, YellowGreen = 0x9ACD32,
  FairyLight = 0xFFE42D, FairyLightNCC = 0xFF9D2A
};

uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b);
unsigned char lerp(float mux, unsigned char a, unsigned char b);
uint32_t LerpRGB(float t, unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2);
uint32_t LerpRGB(float t, uint32_t rgb1, uint32_t rgb2);
void LerpPaletteFromMicroPalette(uint32_t *palette, unsigned int paletteSize, uint32_t* microPalette, unsigned int microPaletteSize);
void CopyPalette(uint32_t *dst, uint32_t *src);

uint32_t ShortnameToCRGB(char shortName);

void PrintFxTrackEndAction(FxTrackEndAction fxTrackEndAction);
void PrintFxPaletteUpdateType(FxPaletteUpdateType paletteUpdateType);
void PrintFxStateName(FxState s);
void PrintFxEventName(int event);
void PrintFxTransitionName(FxTransitionType t);

//////// Time code section ////////
struct TimeCode
{
  signed long timeOffset = 0;
  signed long songOffset = 0;
  unsigned long lastMatchedTimecode = 0;
};
signed long getTimecodeTimeOffset();
signed long getTimecodeSongOffset();
signed long setTimecodeTimeOffset(signed long tc);
signed long setTimecodeSongOffset(signed long tc);
void setTimecodeLastMatched(unsigned long match);
unsigned long getTimecodeLastMatched();
unsigned long GetTime();
//////// Time code section ////////



#endif
