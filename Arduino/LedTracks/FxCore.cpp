#include "Config.h"
#include <Arduino.h>
#include "FxCore.h"

static TimeCode timeController;
uint32_t LEDRGB(uint8_t r, uint8_t g, uint8_t b) { return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b; }
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


void PrintFxTrackEndAction(FxTrackEndAction fxTrackEndAction)
{  
  switch (fxTrackEndAction)
  {
    case StopAtEnd: Serial.print(F("StopAtEnd")); break;
    case LoopAtEnd: Serial.print(F("LoopAtEnd")); break;
    default: Serial.print(F("Unk"));
  }
}

void PrintFxPaletteUpdateType(FxPaletteUpdateType paletteUpdateType)
{
  switch (paletteUpdateType)
  {
    case None:    Serial.print(F("None")); break;
    case Once:    Serial.print(F("Once")); break;
    case Done:    Serial.print(F("Done")); break;
    case Always:  Serial.print(F("Alwa")); break;
    default: Serial.print(F("Unk"));
  }
}

void PrintFxStateName(FxState s)
{
  switch (s)
  {
    case FxState_Default:       Serial.print(F("Norm")); break;
    case FxState_TestPattern:   Serial.print(F("Test")); break;
    case FxState_PlayingTrack:  Serial.print(F("Play")); break;
    case FxState_IMU:           Serial.print(F("IMU")); break;
    case FxState_MIC:           Serial.print(F("MIC")); break;
    default: Serial.print(F("Unk"));
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
    case fx_speed_rst: Serial.print(F("speed rst"));break;
    
    case fx_transition_fast: Serial.print(F("t-fast"));break;
    case fx_transition_timed_fade:Serial.print(F("t-timed-fade"));break;
    case fx_transition_timed_wipe_pos:Serial.print(F("t-timed-wipe-pos"));break;
    case fx_transition_timed_wipe_neg:Serial.print(F("t-timed-wipe-neg"));break;
    case fx_transition_timed_wipe_outin:Serial.print(F("t-timed-wipe-outin"));break;
    case fx_transition_timed_wipe_inout:Serial.print(F("t-timed-wipe-inout"));break;
    
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
    case fx_palette_half:    Serial.print(F("half"));break;
    case fx_palette_lowhalf: Serial.print(F("lowhalf"));break;

    case fx_color1_dark:    Serial.print(F("dark1"));break;
    case fx_color1_white:   Serial.print(F("white1"));break;
    case fx_color1_red:     Serial.print(F("red1"));break;
    case fx_color1_yellow:  Serial.print(F("yellow1"));break;
    case fx_color1_green:   Serial.print(F("green1"));break;
    case fx_color1_cyan:    Serial.print(F("cyan1"));break;
    case fx_color1_blue:    Serial.print(F("blue1"));break;
    case fx_color1_magenta: Serial.print(F("magenta1"));break;
    case fx_color1_orange:  Serial.print(F("orange1"));break;
    case fx_color1_half:    Serial.print(F("half1"));break;
    case fx_color1_lowhalf:  Serial.print(F("lowhalf1"));break;

    case fx_color2_dark:    Serial.print(F("dark2"));break;
    case fx_color2_white:   Serial.print(F("white2"));break;
    case fx_color2_red:     Serial.print(F("red2"));break;
    case fx_color2_yellow:  Serial.print(F("yellow2"));break;
    case fx_color2_green:   Serial.print(F("green2"));break;
    case fx_color2_cyan:    Serial.print(F("cyan2"));break;
    case fx_color2_blue:    Serial.print(F("blue2"));break;
    case fx_color2_magenta: Serial.print(F("magenta2"));break;
    case fx_color2_orange:  Serial.print(F("orange2"));break;
    case fx_color2_half:    Serial.print(F("half2"));break;
    case fx_color2_lowhalf:  Serial.print(F("lowhalf2"));break;

    case fx_color3_dark:    Serial.print(F("dark3"));break;
    case fx_color3_white:   Serial.print(F("white3"));break;
    case fx_color3_red:     Serial.print(F("red3"));break;
    case fx_color3_yellow:  Serial.print(F("yellow3"));break;
    case fx_color3_green:   Serial.print(F("green3"));break;
    case fx_color3_cyan:    Serial.print(F("cyan3"));break;
    case fx_color3_blue:    Serial.print(F("blue3"));break;
    case fx_color3_magenta: Serial.print(F("magenta3"));break;
    case fx_color3_orange:  Serial.print(F("orange3"));break;
    case fx_color3_half:    Serial.print(F("half3"));break;
    case fx_color3_lowhalf:  Serial.print(F("lowhalf3"));break;

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

    case fx_palette_pulse2_dark:    Serial.print(F("pulse2-dark"));break;
    case fx_palette_pulse2_white:   Serial.print(F("pulse2-white"));break;
    case fx_palette_pulse2_red:     Serial.print(F("pulse2-red"));break;
    case fx_palette_pulse2_yellow:  Serial.print(F("pulse2-yellow"));break;
    case fx_palette_pulse2_green:   Serial.print(F("pulse2-green"));break;
    case fx_palette_pulse2_cyan:    Serial.print(F("pulse2-cyan"));break;
    case fx_palette_pulse2_blue:    Serial.print(F("pulse2-blue"));break;
    case fx_palette_pulse2_magenta: Serial.print(F("pulse2-magenta"));break;
    case fx_palette_pulse2_orange:  Serial.print(F("pulse2-orange"));break;
    case fx_palette_pulse2_half:  Serial.print(F("pulse2-half"));break;
    case fx_palette_pulse2_lowhalf:  Serial.print(F("pulse2-lowhalf"));break;
   
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

    case fx_colors1:Serial.print(F("colors1"));break;
    case fx_colors2:Serial.print(F("colors2"));break;
    case fx_colors3:Serial.print(F("colors3"));break;
    case fx_colors4:Serial.print(F("colors4"));break;
    case fx_colors5:Serial.print(F("colors5"));break;
    case fx_colors6:Serial.print(F("colors6"));break;
    case fx_colors7:Serial.print(F("colors7"));break;
    case fx_colors8:Serial.print(F("colors8"));break;
    case fx_colors9:Serial.print(F("colors9"));break;
    case fx_colors10:Serial.print(F("colors10"));break;
    case fx_colors11:Serial.print(F("colors11"));break;
    case fx_colors12:Serial.print(F("colors12"));break;
    case fx_colors13:Serial.print(F("colors13"));break;
    case fx_colors14:Serial.print(F("colors14"));break;
    case fx_colors15:Serial.print(F("colors15"));break;
    case fx_colors16:Serial.print(F("colors16"));break;    

    case fx_palette_accel:Serial.print(F("accel"));break;
    case fx_palette_gyro:Serial.print(F("gyro"));break;
    case fx_palette_mic:Serial.print(F("mic"));break;

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
    case Transition_TimedWipeOutIn: Serial.print(F("WipOI")); break;
    case Transition_TimedWipeInOut: Serial.print(F("WipIO")); break;
    default: Serial.print(F("Unknown"));
  }
}

void LerpPaletteFromMicroPalette(uint32_t *palette, unsigned int paletteSize, uint32_t* microPalette, unsigned int microPaletteSize)
{
    if (microPaletteSize == 0) //Nothing TO do..
        return;

    float stepSize = (float)paletteSize / (float)microPaletteSize;
    for (unsigned int phase = 0; phase < microPaletteSize; phase++)
    {
        unsigned int offset = (unsigned int)((float)(phase) * (float)stepSize);
        unsigned int offsetNext = (unsigned int)((float)(phase+1) * (float)stepSize) ;

        unsigned long to = 0;
        if (phase == microPaletteSize-1) //last phase, so loop back to 0 
            to = microPalette[0]; 
        else
            to = microPalette[phase + 1];

        unsigned int len = offsetNext - offset;
        for (unsigned int i = 0; i < len; i++)
        {
            float mux = (float)i / (float)(len-1);
            unsigned int palIndex = offset + i;
            unsigned long val = LerpRGB(mux, microPalette[phase], to);
            palette[palIndex] = val;
        }
    }
}

void CopyPalette(uint32_t *dst, uint32_t *src)
{
  for (int i=0;i<NUM_LEDS;i++)
    dst[i] = src[i];
}



unsigned long GetTime() { return (unsigned long)((signed long)millis() - (signed long)getTimecodeTimeOffset() + getTimecodeSongOffset()); }

void setTimecodeLastMatched(unsigned long match)
{
  timeController.lastMatchedTimecode = match;
}

unsigned long getTimecodeLastMatched()
{
  return timeController.lastMatchedTimecode;
}

signed long getTimecodeTimeOffset()
{
  return timeController.timeOffset;
}

signed long getTimecodeSongOffset()
{
  return timeController.songOffset;
}

signed long setTimecodeTimeOffset(signed long tc)
{
  timeController.timeOffset = tc;  
}

signed long setTimecodeSongOffset(signed long tc)
{
  timeController.songOffset = tc;  
}


  
