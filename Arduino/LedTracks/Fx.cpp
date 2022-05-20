#include <Arduino.h>
#include "Config.h"
#include "Devices.h"
#include "Fx.h"
#include "Track.h"

void FxCreatePalette(FxController &fxController, int strip, uint32_t *pal16, unsigned int palSize)
{
      if (fxController.strip[strip].transitionType == Transition_Instant)
      {
        LerpPaletteFromMicroPalette(fxController.strip[strip].palette, NUM_LEDS, pal16, palSize);
      }
      else if (fxController.strip[strip].transitionType == Transition_TimedFade)
      {
        CopyPalette(fxController.strip[strip].initialPalette, fxController.strip[strip].palette);
        LerpPaletteFromMicroPalette(fxController.strip[strip].nextPalette, NUM_LEDS, pal16, palSize);
      }
      else if (fxController.strip[strip].transitionType >= Transition_TimedWipePos        
          && fxController.strip[strip].transitionType <= Transition_TimedWipeInOut)
      {
        CopyPalette(fxController.strip[strip].initialPalette, fxController.strip[strip].palette);
        LerpPaletteFromMicroPalette(fxController.strip[strip].nextPalette, NUM_LEDS, pal16, palSize);
      }
}

void CreateSingleColor(FxController &fxc, uint8_t r, uint8_t g, uint8_t b)
{  
  uint32_t palette[16];
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
       for (int i=0;i<16;i++)
       {
         palette[i] = LEDRGB(r,g,b);
       }
       FxCreatePalette(fxc, strip, palette,16);
    }
  }
}

void CreateDoubleColor(FxController &fxc, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2 )
{  
  uint32_t palette[16];
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
        palette[0] = LEDRGB(r1,g1,b1);
        palette[1] = LEDRGB(r2,g2,b2);
        FxCreatePalette(fxc,strip, palette,2);
    }
  }
}

void CreateQuadColor(FxController &fxc, 
  byte r1, byte g1, byte b1, 
  byte r2, byte g2, byte b2,
  byte r3, byte g3, byte b3,
  byte r4, byte g4, byte b4)
{  
  uint32_t palette[16];
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
        palette[0] = LEDRGB(r1,g1,b1);
        palette[1] = LEDRGB(r2,g2,b2);
        palette[2] = LEDRGB(r3,g3,b3);
        palette[3] = LEDRGB(r4,g4,b4);
        FxCreatePalette(fxc,strip, palette,2);
    }
  }
}

void Create16Color(FxController &fxc, uint32_t b0,uint32_t b1,uint32_t b2,uint32_t b3, uint32_t b4,uint32_t b5,uint32_t b6,uint32_t b7,
                        uint32_t b8,uint32_t b9,uint32_t b10,uint32_t b11, uint32_t b12,uint32_t b13,uint32_t b14,uint32_t b15)
{
  uint32_t palette[16];
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
        palette[0] = b0;
        palette[1] = b1;
        palette[2] = b2;
        palette[3] = b3;
        palette[4] = b4;
        palette[5] = b5;
        palette[6] = b6;
        palette[7] = b7;
        palette[8] = b8;
        palette[9] = b9;
        palette[10] = b10;
        palette[11] = b11;
        palette[12] = b12;
        palette[13] = b13;
        palette[14] = b14;
        palette[15] = b15;
        FxCreatePalette(fxc,strip, palette,16);
    }
  }
}

void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) {
  Create16Color(fxc, LEDRGB(r/2,g/2,b/2),LEDRGB(r,g,b),LEDRGB(r/2,g/2,b/2),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0));
}

void CreateDoublePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) {
  Create16Color(fxc, LEDRGB(r/2,g/2,b/2),LEDRGB(r,g,b),LEDRGB(r/2,g/2,b/2),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(r/2,g/2,b/2),LEDRGB(r,g,b),LEDRGB(r/2,g/2,b/2),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0));
}

void FxDisplayStatus(FxController &fxc)
{
  Serial.print(F("["));
      Serial.print(DeviceName);
      Serial.print(F(":"));
      Serial.print(GetTime());
      Serial.print(F(":"));
      Serial.print(getTimecodeSongOffset());
      Serial.print(F(":"));
      Serial.print(getTimecodeTimeOffset());
      Serial.print(F("[state="));
      PrintFxStateName(fxc.fxState);
      Serial.print(F(",strip&="));
      Serial.print(fxc.stripMask);

#if ENABLE_BLE      
      Serial.print(F(",BLE on"));
#else
      Serial.print(F(",BLE off"));
#endif
  //Strip debugging
  
      for (int strip=0;strip<NUM_STRIPS;strip++)
      {
        Serial.print(F("["));
        Serial.print(F("b="));
        Serial.print(fxc.strip[strip].brightness);
        Serial.print(F(",ps="));
        Serial.print(fxc.strip[strip].paletteSpeed);
        Serial.print(F(",pd="));
        Serial.print(fxc.strip[strip].paletteDirection);
        Serial.print(F(",u="));
        Serial.print(fxc.strip[strip].fxPaletteUpdateType);
        Serial.print(F("] "));
      }
    
      Serial.print(F(",endAction="));
      PrintFxTrackEndAction(fxc.fxTrackEndAction);
      Serial.print(F(",ftc="));
      Serial.print(GetFinalTimeCodeEntry());      
      Serial.print(F(",tclm="));
      Serial.print(getTimecodeLastMatched());
      Serial.print(F(")"));
      /*
      if (fxc.fxState == FxState_PlayingTrack)
      {
        int match = GetCurrentTimeCodeMatch(GetTime());
        Serial.print(F("="));
        PrintFxEventName(SongTrack_event(match));
        Serial.print(F(" "));
        Serial.print(SongTrack_timecode(match));
      }*/

      Serial.println();
}

void SetTransitionType(FxController &fxc, FxTransitionType t)
{
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
      fxc.strip[strip].transitionType = t;
      if (t == Transition_TimedWipePos || t == Transition_TimedWipeNeg
        || t == Transition_TimedWipeOutIn || t == Transition_TimedWipeInOut) 
        {
          fxc.strip[strip].fxPaletteUpdateType = FxPaletteUpdateType::None;
          fxc.strip[strip].paletteIndex = 0;
        }
        if (t == fx_transition_timed_wipe_neg)
          fxc.strip[strip].paletteIndex = 15;
    }
  }
}

void ResetPaletteSpeed(FxController &fxc)
{
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
      fxc.strip[strip].paletteSpeed = 0;
      fxc.strip[strip].paletteIndex = 0;
      fxc.strip[strip].paletteDirection = 1;
    }
  }
}

void SetPaletteSpeed(FxController &fxc, int v)
{
  for (int strip=0;strip<NUM_STRIPS;strip++)
    if (fxc.stripMask & (1<<strip)) 
      fxc.strip[strip].paletteSpeed = v;
}

void ChangePaletteSpeed(FxController &fxc, int ps)
{
  for (int strip=0;strip<NUM_STRIPS;strip++)
    if (fxc.stripMask & (1<<strip)) 
      fxc.strip[strip].paletteSpeed += ps;
}

void SetPaletteDirection(FxController &fxc, int c)
{
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip)) 
    {
      fxc.strip[strip].paletteDirection = c;
      if (fxc.strip[strip].paletteSpeed >= 18)
        fxc.strip[strip].paletteSpeed = 18;
      if (fxc.strip[strip].paletteSpeed < 0)
        fxc.strip[strip].paletteSpeed = 0;
    }
  }
}

void FxEventProcess(FxController &fxc,int event)
{
  bool updatePal = false;

  if (event >= fx_stripmask_0 && event <= fx_stripmask_255)
  {
    fxc.stripMask = (unsigned int)event-(unsigned int)fx_stripmask_0;
    return;
  }
  
  switch (event)
  {
    case fx_strip_all:   fxc.stripMask = (unsigned int)(LEDS_0|LEDS_1|LEDS_2|LEDS_3|LEDS_4|LEDS_5|LEDS_6|LEDS_7); break;
    case fx_strip_odds:  fxc.stripMask = (unsigned int)(LEDS_1|LEDS_3|LEDS_5|LEDS_7); break;
    case fx_strip_evens: fxc.stripMask = (unsigned int)(LEDS_0|LEDS_2|LEDS_4|LEDS_6); break;
    case fx_strip_none:  fxc.stripMask = (unsigned int)0; break;
    
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
      SetPaletteSpeed(fxc,event);
      break;
    case fx_speed_32:
      SetPaletteSpeed(fxc,32);
      break;

    case fx_speed_pos:SetPaletteDirection(fxc,1);break;
    case fx_speed_neg:SetPaletteDirection(fxc,-1);break;
    case fx_speed_inc:ChangePaletteSpeed(fxc,1);break;
    case fx_speed_dec:ChangePaletteSpeed(fxc,-1);break;
    case fx_speed_rst:
      ResetPaletteSpeed(fxc);break;
      
    case fx_transition_fast:             SetTransitionType(fxc,Transition_Instant);break;
    case fx_transition_timed_fade:       SetTransitionType(fxc,Transition_TimedFade);break;
    case fx_transition_timed_wipe_pos:   SetTransitionType(fxc,Transition_TimedWipePos);break;
    case fx_transition_timed_wipe_neg:   SetTransitionType(fxc,Transition_TimedWipeNeg);break;
    case fx_transition_timed_wipe_outin: SetTransitionType(fxc,Transition_TimedWipeOutIn);break;
    case fx_transition_timed_wipe_inout: SetTransitionType(fxc,Transition_TimedWipeInOut);break;

    case fx_palette_lead:   CreateSingleColor(fxc, BLUE);break;
    case fx_palette_follow: CreateSingleColor(fxc, RED);break;
    
    case fx_palette_dark:   CreateSingleColor(fxc, DARK);break;
    case fx_palette_white:  CreateSingleColor(fxc, WHITE);break;
    case fx_palette_red:    CreateSingleColor(fxc, RED);break;
    case fx_palette_yellow: CreateSingleColor(fxc, YELLOW);break;
    case fx_palette_green:  CreateSingleColor(fxc, GREEN);break;
    case fx_palette_cyan:   CreateSingleColor(fxc, CYAN);break;
    case fx_palette_blue:   CreateSingleColor(fxc, BLUE);break;
    case fx_palette_magenta:CreateSingleColor(fxc, MAGENTA);break;
    case fx_palette_orange: CreateSingleColor(fxc, ORANGE);break;
    case fx_palette_half:   CreateSingleColor(fxc, HALF);break;
    case fx_palette_lowhalf:CreateSingleColor(fxc, LOWHALF);break;

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

    case fx_palette_pulse2_dark:CreateDoublePulseBand(fxc, DARK);break;
    case fx_palette_pulse2_white:CreateDoublePulseBand(fxc, WHITE);break;
    case fx_palette_pulse2_red:CreateDoublePulseBand(fxc, RED);break;
    case fx_palette_pulse2_yellow:CreateDoublePulseBand(fxc, YELLOW);break;
    case fx_palette_pulse2_green:CreateDoublePulseBand(fxc, GREEN);break;
    case fx_palette_pulse2_cyan:CreateDoublePulseBand(fxc, CYAN);break;
    case fx_palette_pulse2_blue:CreateDoublePulseBand(fxc, BLUE);break;
    case fx_palette_pulse2_magenta:CreateDoublePulseBand(fxc, MAGENTA);break;
    case fx_palette_pulse2_orange:CreateDoublePulseBand(fxc, ORANGE);break;
    case fx_palette_pulse2_half:CreateDoublePulseBand(fxc, HALF);break;
    case fx_palette_pulse2_lowhalf:CreateDoublePulseBand(fxc, LOWHALF);break;    

    case fx_palette_dr: CreateDoubleColor(fxc, DARK, RED); break;
    case fx_palette_dy: CreateDoubleColor(fxc, DARK, YELLOW); break;
    case fx_palette_dg: CreateDoubleColor(fxc, DARK, GREEN); break;
    case fx_palette_dc: CreateDoubleColor(fxc, DARK, CYAN); break;
    case fx_palette_db: CreateDoubleColor(fxc, DARK, BLUE); break;
    case fx_palette_dm: CreateDoubleColor(fxc, DARK, MAGENTA); break;
    case fx_palette_wr: CreateDoubleColor(fxc, WHITE, RED); break;
    case fx_palette_wy: CreateDoubleColor(fxc, WHITE, YELLOW); break;
    case fx_palette_wg: CreateDoubleColor(fxc, WHITE, GREEN); break;
    case fx_palette_wc: CreateDoubleColor(fxc, WHITE, CYAN); break;
    case fx_palette_wb: CreateDoubleColor(fxc, WHITE, BLUE); break;
    case fx_palette_wm: CreateDoubleColor(fxc, WHITE, MAGENTA); break;
    case fx_palette_ry: CreateDoubleColor(fxc, RED, YELLOW); break;
    case fx_palette_rg: CreateDoubleColor(fxc, RED, GREEN); break;
    case fx_palette_rc: CreateDoubleColor(fxc, RED, CYAN); break;
    case fx_palette_rb: CreateDoubleColor(fxc, RED, BLUE); break;
    case fx_palette_rm: CreateDoubleColor(fxc, RED, MAGENTA); break;
    case fx_palette_yg: CreateDoubleColor(fxc, YELLOW, GREEN); break;
    case fx_palette_yc: CreateDoubleColor(fxc, YELLOW, CYAN); break;
    case fx_palette_yb: CreateDoubleColor(fxc, YELLOW, BLUE); break;
    case fx_palette_ym: CreateDoubleColor(fxc, YELLOW, MAGENTA); break;
    case fx_palette_gc: CreateDoubleColor(fxc, GREEN, CYAN); break;
    case fx_palette_gb: CreateDoubleColor(fxc, GREEN, BLUE); break;
    case fx_palette_gm: CreateDoubleColor(fxc, GREEN, MAGENTA); break;
    case fx_palette_cb: CreateDoubleColor(fxc, CYAN, BLUE); break;
    case fx_palette_cm: CreateDoubleColor(fxc, CYAN, MAGENTA); break;
    case fx_palette_bm: CreateDoubleColor(fxc, BLUE, MAGENTA); break;

    case fx_palette_wry: CreateQuadColor(fxc, WHITE, RED,    WHITE, YELLOW); break;
    case fx_palette_wrg: CreateQuadColor(fxc, WHITE, RED,    WHITE, GREEN); break;
    case fx_palette_wrc: CreateQuadColor(fxc, WHITE, RED,    WHITE, CYAN); break;
    case fx_palette_wrb: CreateQuadColor(fxc, WHITE, RED,    WHITE, BLUE); break;
    case fx_palette_wrm: CreateQuadColor(fxc, WHITE, RED,    WHITE, MAGENTA); break;
    case fx_palette_wyg: CreateQuadColor(fxc, WHITE, YELLOW, WHITE, GREEN); break;
    case fx_palette_wyc: CreateQuadColor(fxc, WHITE, YELLOW, WHITE, CYAN); break;
    case fx_palette_wyb: CreateQuadColor(fxc, WHITE, YELLOW, WHITE, BLUE); break;
    case fx_palette_wym: CreateQuadColor(fxc, WHITE, YELLOW, WHITE, MAGENTA); break;
    case fx_palette_wgc: CreateQuadColor(fxc, WHITE, GREEN,  WHITE, CYAN); break;
    case fx_palette_wgb: CreateQuadColor(fxc, WHITE, GREEN,  WHITE, BLUE); break;
    case fx_palette_wgm: CreateQuadColor(fxc, WHITE, GREEN,  WHITE, MAGENTA); break;
    case fx_palette_wcb: CreateQuadColor(fxc, WHITE, CYAN,   WHITE, BLUE); break;
    case fx_palette_wcm: CreateQuadColor(fxc, WHITE, CYAN,   WHITE, MAGENTA); break;
    case fx_palette_wbm: CreateQuadColor(fxc, WHITE, BLUE,   WHITE, MAGENTA); break;

    case fx_palette_dry: CreateQuadColor(fxc, DARK, RED,    DARK, YELLOW); break;
    case fx_palette_drg: CreateQuadColor(fxc, DARK, RED,    DARK, GREEN); break;
    case fx_palette_drc: CreateQuadColor(fxc, DARK, RED,    DARK, CYAN); break;
    case fx_palette_drb: CreateQuadColor(fxc, DARK, RED,    DARK, BLUE); break;
    case fx_palette_drm: CreateQuadColor(fxc, DARK, RED,    DARK, MAGENTA); break;
    case fx_palette_dyg: CreateQuadColor(fxc, DARK, YELLOW, DARK, GREEN); break;
    case fx_palette_dyc: CreateQuadColor(fxc, DARK, YELLOW, DARK, CYAN); break;
    case fx_palette_dyb: CreateQuadColor(fxc, DARK, YELLOW, DARK, BLUE); break;
    case fx_palette_dym: CreateQuadColor(fxc, DARK, YELLOW, DARK, MAGENTA); break;
    case fx_palette_dgc: CreateQuadColor(fxc, DARK, GREEN,  DARK, CYAN); break;
    case fx_palette_dgb: CreateQuadColor(fxc, DARK, GREEN,  DARK, BLUE); break;
    case fx_palette_dgm: CreateQuadColor(fxc, DARK, GREEN,  DARK, MAGENTA); break;
    case fx_palette_dcb: CreateQuadColor(fxc, DARK, CYAN,   DARK, BLUE); break;
    case fx_palette_dcm: CreateQuadColor(fxc, DARK, CYAN,   DARK, MAGENTA); break;
    case fx_palette_dbm: CreateQuadColor(fxc, DARK, BLUE,   DARK, MAGENTA); break;

    case fx_palette_rbm: CreateQuadColor(fxc, RED, MAGENTA, BLUE,   DARK); break;

    case fx_palette_lava:Create16Color(fxc,
        WEBRGB::Black,WEBRGB::Maroon,WEBRGB::Black,WEBRGB::Maroon,    
        WEBRGB::DarkRed,WEBRGB::Maroon,WEBRGB::DarkRed,WEBRGB::DarkRed,    
        WEBRGB::DarkRed,WEBRGB::DarkRed,WEBRGB::Red,WEBRGB::Orange,    
        WEBRGB::White,WEBRGB::Orange,WEBRGB::Red,WEBRGB::DarkRed);
      break;
    case fx_palette_cloud:Create16Color(fxc,  
      WEBRGB::Blue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,
      WEBRGB::DarkBlue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,
      WEBRGB::Blue,WEBRGB::DarkBlue,WEBRGB::SkyBlue,WEBRGB::SkyBlue,
      WEBRGB::LightBlue,WEBRGB::White,WEBRGB::LightBlue,WEBRGB::SkyBlue);
      break;
    case fx_palette_ocean:Create16Color(fxc,    
      WEBRGB::DarkGreen,
      WEBRGB::DarkGreen,
      WEBRGB::DarkOliveGreen,
      WEBRGB::DarkGreen,
  
      WEBRGB::Green,
      WEBRGB::ForestGreen,
      WEBRGB::OliveDrab,
      WEBRGB::Green,
  
      WEBRGB::SeaGreen,
      WEBRGB::MediumAquamarine,
      WEBRGB::LimeGreen,
      WEBRGB::YellowGreen,
  
      WEBRGB::LightGreen,
      WEBRGB::LawnGreen,
      WEBRGB::MediumAquamarine,
      WEBRGB::ForestGreen);break;
    case fx_palette_forest:Create16Color(fxc,    
      WEBRGB::DarkGreen,
      WEBRGB::DarkGreen,
      WEBRGB::DarkOliveGreen,
      WEBRGB::DarkGreen,
  
      WEBRGB::Green,
      WEBRGB::ForestGreen,
      WEBRGB::OliveDrab,
      WEBRGB::Green,
  
      WEBRGB::SeaGreen,
      WEBRGB::MediumAquamarine,
      WEBRGB::LimeGreen,
      WEBRGB::YellowGreen,
  
      WEBRGB::LightGreen,
      WEBRGB::LawnGreen,
      WEBRGB::MediumAquamarine,
      WEBRGB::ForestGreen);break;
    case fx_palette_rainbow:Create16Color(fxc, 
      0xFF0000, 0xD52A00, 0xAB5500, 0xAB7F00,
      0xABAB00, 0x56D500, 0x00FF00, 0x00D52A,
      0x00AB55, 0x0056AA, 0x0000FF, 0x2A00D5,
      0x5500AB, 0x7F0081, 0xAB0055, 0xD5002B);break;
    case fx_palette_rainbowstripe:Create16Color(fxc,    
      0xFF0000, 0x000000, 0xAB5500, 0x000000,
      0xABAB00, 0x000000, 0x00FF00, 0x000000,
      0x00AB55, 0x000000, 0x0000FF, 0x000000,
      0x5500AB, 0x000000, 0xAB0055, 0x000000);break;
    case fx_palette_party:Create16Color(fxc,   
      0x5500AB, 0x84007C, 0xB5004B, 0xE5001B,
      0xE81700, 0xB84700, 0xAB7700, 0xABAB00,
      0xAB5500, 0xDD2200, 0xF2000E, 0xC2003E,
      0x8F0071, 0x5F00A1, 0x2F00D0, 0x0007F9);break;
    case fx_palette_heat:Create16Color(fxc,
      0x000000, 0x330000, 0x660000, 0x990000, 
      0xCC0000, 0xFF0000, 0xFF3300, 0xFF6600, 
      0xFF9900, 0xFFCC00, 0xFFFF00, 0xFFFF33, 
      0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF);break;

 }
}
