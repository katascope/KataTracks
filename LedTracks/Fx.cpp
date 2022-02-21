#include <Arduino.h>
#include "Config.h"
#include "Devices.h"
#include "Fx.h"
#include "Track.h"


void FxCreatePalette(FxController &fxController, uint32_t *pal16, unsigned int palSize)
{
    if (fxController.transitionType == Transition_Instant)
    {
      LerpPaletteFromMicroPalette(fxController.palette, NUM_LEDS, pal16, palSize);
    }
    else if (fxController.transitionType == Transition_TimedFade)
    {
      CopyPalette(fxController.initialPalette, fxController.palette);
      LerpPaletteFromMicroPalette(fxController.nextPalette, NUM_LEDS, pal16, palSize);
    }
    else if (fxController.transitionType == Transition_TimedWipePos)
    {
      CopyPalette(fxController.initialPalette, fxController.palette);
      LerpPaletteFromMicroPalette(fxController.nextPalette, NUM_LEDS, pal16, palSize);
    }
    else if (fxController.transitionType == Transition_TimedWipeNeg)
    {
      CopyPalette(fxController.initialPalette, fxController.palette);
      LerpPaletteFromMicroPalette(fxController.nextPalette, NUM_LEDS, pal16, palSize);
    }
}

void SetMicroPaletteSlot(FxController &fxc, int slot, uint32_t rgb)
{
  if (slot < 16 )
  {
    fxc.microPalette[slot] = rgb;  
    if (fxc.microPaletteSize < slot)
      fxc.microPaletteSize = slot + 1;  
    FxCreatePalette(fxc,fxc.microPalette, fxc.microPaletteSize);
  }
}

void SetMicroPalette(FxController &fxc, byte r, byte g, byte b)
{
  SetMicroPaletteSlot(fxc, 0, LEDRGB(r,g,b));
  fxc.microPaletteSize = 1;
}
void SetMicroPalette2(FxController &fxc, byte r1, byte g1, byte b1, byte r2, byte g2, byte b2)
{
  SetMicroPaletteSlot(fxc,0, LEDRGB(r1,g1,b1) );
  SetMicroPaletteSlot(fxc,1, LEDRGB(r2,g2,b2) );
  fxc.microPaletteSize = 2;
}
void SetMicroPalette4(FxController &fxc, 
  byte r1, byte g1, byte b1, 
  byte r2, byte g2, byte b2,
  byte r3, byte g3, byte b3,
  byte r4, byte g4, byte b4)
{
  SetMicroPaletteSlot(fxc, 0, LEDRGB(r1,g1,b1) );
  SetMicroPaletteSlot(fxc, 1, LEDRGB(r2,g2,b2) );
  SetMicroPaletteSlot(fxc, 2, LEDRGB(r3,g3,b3) );
  SetMicroPaletteSlot(fxc, 3, LEDRGB(r4,g4,b4) );
  fxc.microPaletteSize = 4;
}
void SetMicroPalette16(FxController &fxc, uint32_t b0,uint32_t b1,uint32_t b2,uint32_t b3, uint32_t b4,uint32_t b5,uint32_t b6,uint32_t b7,
                        uint32_t b8,uint32_t b9,uint32_t b10,uint32_t b11, uint32_t b12,uint32_t b13,uint32_t b14,uint32_t b15)
{
  SetMicroPaletteSlot(fxc, 0, b0 );
  SetMicroPaletteSlot(fxc, 1, b1 );
  SetMicroPaletteSlot(fxc, 2, b2 );
  SetMicroPaletteSlot(fxc, 3, b3 );
  SetMicroPaletteSlot(fxc, 4, b4 );
  SetMicroPaletteSlot(fxc, 5, b5 );
  SetMicroPaletteSlot(fxc, 6, b6 );
  SetMicroPaletteSlot(fxc, 7, b7 );
  SetMicroPaletteSlot(fxc, 8, b8 );
  SetMicroPaletteSlot(fxc, 9, b9 );
  SetMicroPaletteSlot(fxc, 10, b10 );
  SetMicroPaletteSlot(fxc, 11, b11 );
  SetMicroPaletteSlot(fxc, 12, b12 );
  SetMicroPaletteSlot(fxc, 13, b13 );
  SetMicroPaletteSlot(fxc, 14, b14 );
  SetMicroPaletteSlot(fxc, 15, b15 );
  fxc.microPaletteSize = 16;
}

void CreateSinglePulseBand(FxController &fxc, uint8_t r, uint8_t g, uint8_t b) {
  SetMicroPalette16(fxc, LEDRGB(r/2,g/2,b/2),LEDRGB(r,g,b),LEDRGB(r/2,g/2,b/2),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),
                      LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0),LEDRGB(0,0,0));
}
static unsigned long lastTimeDisplay = 0;
void FxDisplayStatus(FxController &fxc)
{
    unsigned long t =  millis();
    if (t - lastTimeDisplay > 1000)//delay to let bluetooth get data
    {      
      Serial.print(GetTime());
      Serial.print(F(":"));
      Serial.print(getTimecodeSongOffset());
      Serial.print(F(":"));
      Serial.print(getTimecodeTimeOffset());
      Serial.print(F("["));
      PrintFxStateName(fxc.fxState);
      Serial.print(F("-"));
      PrintFxTransitionName(fxc.transitionType);
      Serial.print(F("-"));
      PrintFxPaletteUpdateType(fxc.fxPaletteUpdateType);
      Serial.print(F("]"));
      if (fxc.fxState == FxState_PlayingTrack)
      {
        int match = GetCurrentTimeCodeMatch(GetTime());
        Serial.print(F("="));
        PrintFxEventName(SongTrack_event(match));
        Serial.print(F(" "));
        Serial.print(SongTrack_timecode(match));
      }

#if ENABLE_IMU
      Serial.print(F(" IMU:"));
      Serial.print(getAccelX());
      Serial.print(F(" "));
      Serial.print(getAccelY());
      Serial.print(F(" "));
      Serial.print(getAccelZ());
      Serial.print(F(" "));
      Serial.print(getGyroX());
      Serial.print(F(" "));
      Serial.print(getGyroY());
      Serial.print(F(" "));
      Serial.print(getGyroZ());
#endif            

      Serial.print(F(" pal("));
      Serial.print(fxc.microPaletteSize);
      Serial.print(F(")="));
      for (int i=0;i<fxc.microPaletteSize;i++)
      {
        Serial.print(fxc.microPalette[i], HEX);
        Serial.print(F(" "));
      }
      Serial.println(F(""));      

      lastTimeDisplay = t;
    }
}
void FxEventProcess(FxController &fxc,int event)
{
  bool updatePal = false;
  
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
    case fx_transition_fast:          fxc.transitionType = Transition_Instant;break;
    case fx_transition_timed_fade:    fxc.transitionType = Transition_TimedFade;break;
    case fx_transition_timed_wipe_pos:fxc.transitionType = Transition_TimedWipePos;fxc.paletteIndex = 0;fxc.fxPaletteUpdateType = FxPaletteUpdateType::None;break;
    case fx_transition_timed_wipe_neg:fxc.transitionType = Transition_TimedWipeNeg;fxc.paletteIndex = 15;fxc.fxPaletteUpdateType = FxPaletteUpdateType::None;break;

    case fx_palette_lead:   SetMicroPalette(fxc, BLUE);break;
    case fx_palette_follow: SetMicroPalette(fxc, RED);break;

    case fx_colors1:fxc.microPaletteSize = 1; break;
    case fx_colors2:fxc.microPaletteSize = 2; break;
    case fx_colors3:fxc.microPaletteSize = 3; break;
    case fx_colors4:fxc.microPaletteSize = 4; break;
    case fx_colors5:fxc.microPaletteSize = 5; break;
    case fx_colors6:fxc.microPaletteSize = 6; break;
    case fx_colors7:fxc.microPaletteSize = 7; break;
    case fx_colors8:fxc.microPaletteSize = 8; break;
    case fx_colors9:fxc.microPaletteSize = 9; break;
    case fx_colors10:fxc.microPaletteSize = 10; break;
    case fx_colors11:fxc.microPaletteSize = 11; break;
    case fx_colors12:fxc.microPaletteSize = 12; break;
    case fx_colors13:fxc.microPaletteSize = 13; break;
    case fx_colors14:fxc.microPaletteSize = 14; break;
    case fx_colors15:fxc.microPaletteSize = 15; break;
    case fx_colors16:fxc.microPaletteSize = 16; break;

    case fx_color1_dark:    SetMicroPaletteSlot(fxc,0, LEDRGB(DARK));break;
    case fx_color1_white:   SetMicroPaletteSlot(fxc,0, LEDRGB(WHITE));break;
    case fx_color1_red:     SetMicroPaletteSlot(fxc,0, LEDRGB(RED));break;
    case fx_color1_yellow:  SetMicroPaletteSlot(fxc,0, LEDRGB(YELLOW));break;
    case fx_color1_green:   SetMicroPaletteSlot(fxc,0, LEDRGB(GREEN));break;
    case fx_color1_cyan:    SetMicroPaletteSlot(fxc,0, LEDRGB(CYAN));break;
    case fx_color1_blue:    SetMicroPaletteSlot(fxc,0, LEDRGB(BLUE));break;
    case fx_color1_magenta: SetMicroPaletteSlot(fxc,0, LEDRGB(MAGENTA));break;
    case fx_color1_orange:  SetMicroPaletteSlot(fxc,0, LEDRGB(ORANGE));break;
    case fx_color1_half:    SetMicroPaletteSlot(fxc,0, LEDRGB(HALF));break;
    case fx_color1_lowhalf: SetMicroPaletteSlot(fxc,0, LEDRGB(LOWHALF));break;

    case fx_color2_dark:    SetMicroPaletteSlot(fxc,1, LEDRGB(DARK));break;
    case fx_color2_white:   SetMicroPaletteSlot(fxc,1, LEDRGB(WHITE));break;
    case fx_color2_red:     SetMicroPaletteSlot(fxc,1, LEDRGB(RED));break;
    case fx_color2_yellow:  SetMicroPaletteSlot(fxc,1, LEDRGB(YELLOW));break;
    case fx_color2_green:   SetMicroPaletteSlot(fxc,1, LEDRGB(GREEN));break;
    case fx_color2_cyan:    SetMicroPaletteSlot(fxc,1, LEDRGB(CYAN));break;
    case fx_color2_blue:    SetMicroPaletteSlot(fxc,1, LEDRGB(BLUE));break;
    case fx_color2_magenta: SetMicroPaletteSlot(fxc,1, LEDRGB(MAGENTA));break;
    case fx_color2_orange:  SetMicroPaletteSlot(fxc,1, LEDRGB(ORANGE));break;
    case fx_color2_half:    SetMicroPaletteSlot(fxc,1, LEDRGB(HALF));break;
    case fx_color2_lowhalf: SetMicroPaletteSlot(fxc,1, LEDRGB(LOWHALF));break;

    case fx_color3_dark:    SetMicroPaletteSlot(fxc,2, LEDRGB(DARK));break;
    case fx_color3_white:   SetMicroPaletteSlot(fxc,2, LEDRGB(WHITE));break;
    case fx_color3_red:     SetMicroPaletteSlot(fxc,2, LEDRGB(RED));break;
    case fx_color3_yellow:  SetMicroPaletteSlot(fxc,2, LEDRGB(YELLOW));break;
    case fx_color3_green:   SetMicroPaletteSlot(fxc,2, LEDRGB(GREEN));break;
    case fx_color3_cyan:    SetMicroPaletteSlot(fxc,2, LEDRGB(CYAN));break;
    case fx_color3_blue:    SetMicroPaletteSlot(fxc,2, LEDRGB(BLUE));break;
    case fx_color3_magenta: SetMicroPaletteSlot(fxc,2, LEDRGB(MAGENTA));break;
    case fx_color3_orange:  SetMicroPaletteSlot(fxc,2, LEDRGB(ORANGE));break;
    case fx_color3_half:    SetMicroPaletteSlot(fxc,2, LEDRGB(HALF));break;
    case fx_color3_lowhalf: SetMicroPaletteSlot(fxc,2, LEDRGB(LOWHALF));break;

    case fx_palette_dark:   SetMicroPalette(fxc, DARK);break;
    case fx_palette_white:  SetMicroPalette(fxc, WHITE);break;
    case fx_palette_red:    SetMicroPalette(fxc, RED);break;
    case fx_palette_yellow: SetMicroPalette(fxc, YELLOW);break;
    case fx_palette_green:  SetMicroPalette(fxc, GREEN);break;
    case fx_palette_cyan:   SetMicroPalette(fxc, CYAN);break;
    case fx_palette_blue:   SetMicroPalette(fxc, BLUE);break;
    case fx_palette_magenta:SetMicroPalette(fxc, MAGENTA);break;
    case fx_palette_orange: SetMicroPalette(fxc, ORANGE);break;
    case fx_palette_half:   SetMicroPalette(fxc, HALF);break;
    case fx_palette_lowhalf:SetMicroPalette(fxc, LOWHALF);break;

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

    case fx_palette_dr: SetMicroPalette2(fxc, DARK, RED); break;
    case fx_palette_dy: SetMicroPalette2(fxc, DARK, YELLOW); break;
    case fx_palette_dg: SetMicroPalette2(fxc, DARK, GREEN); break;
    case fx_palette_dc: SetMicroPalette2(fxc, DARK, CYAN); break;
    case fx_palette_db: SetMicroPalette2(fxc, DARK, BLUE); break;
    case fx_palette_dm: SetMicroPalette2(fxc, DARK, MAGENTA); break;
    case fx_palette_wr: SetMicroPalette2(fxc, WHITE, RED); break;
    case fx_palette_wy: SetMicroPalette2(fxc, WHITE, YELLOW); break;
    case fx_palette_wg: SetMicroPalette2(fxc, WHITE, GREEN); break;
    case fx_palette_wc: SetMicroPalette2(fxc, WHITE, CYAN); break;
    case fx_palette_wb: SetMicroPalette2(fxc, WHITE, BLUE); break;
    case fx_palette_wm: SetMicroPalette2(fxc, WHITE, MAGENTA); break;
    case fx_palette_ry: SetMicroPalette2(fxc, RED, YELLOW); break;
    case fx_palette_rg: SetMicroPalette2(fxc, RED, GREEN); break;
    case fx_palette_rc: SetMicroPalette2(fxc, RED, CYAN); break;
    case fx_palette_rb: SetMicroPalette2(fxc, RED, BLUE); break;
    case fx_palette_rm: SetMicroPalette2(fxc, RED, MAGENTA); break;
    case fx_palette_yg: SetMicroPalette2(fxc, YELLOW, GREEN); break;
    case fx_palette_yc: SetMicroPalette2(fxc, YELLOW, CYAN); break;
    case fx_palette_yb: SetMicroPalette2(fxc, YELLOW, BLUE); break;
    case fx_palette_ym: SetMicroPalette2(fxc, YELLOW, MAGENTA); break;
    case fx_palette_gc: SetMicroPalette2(fxc, GREEN, CYAN); break;
    case fx_palette_gb: SetMicroPalette2(fxc, GREEN, BLUE); break;
    case fx_palette_gm: SetMicroPalette2(fxc, GREEN, MAGENTA); break;
    case fx_palette_cb: SetMicroPalette2(fxc, CYAN, BLUE); break;
    case fx_palette_cm: SetMicroPalette2(fxc, CYAN, MAGENTA); break;
    case fx_palette_bm: SetMicroPalette2(fxc, BLUE, MAGENTA); break;

    case fx_palette_wry: SetMicroPalette4(fxc, WHITE, RED,    WHITE, YELLOW); break;
    case fx_palette_wrg: SetMicroPalette4(fxc, WHITE, RED,    WHITE, GREEN); break;
    case fx_palette_wrc: SetMicroPalette4(fxc, WHITE, RED,    WHITE, CYAN); break;
    case fx_palette_wrb: SetMicroPalette4(fxc, WHITE, RED,    WHITE, BLUE); break;
    case fx_palette_wrm: SetMicroPalette4(fxc, WHITE, RED,    WHITE, MAGENTA); break;
    case fx_palette_wyg: SetMicroPalette4(fxc, WHITE, YELLOW, WHITE, GREEN); break;
    case fx_palette_wyc: SetMicroPalette4(fxc, WHITE, YELLOW, WHITE, CYAN); break;
    case fx_palette_wyb: SetMicroPalette4(fxc, WHITE, YELLOW, WHITE, BLUE); break;
    case fx_palette_wym: SetMicroPalette4(fxc, WHITE, YELLOW, WHITE, MAGENTA); break;
    case fx_palette_wgc: SetMicroPalette4(fxc, WHITE, GREEN,  WHITE, CYAN); break;
    case fx_palette_wgb: SetMicroPalette4(fxc, WHITE, GREEN,  WHITE, BLUE); break;
    case fx_palette_wgm: SetMicroPalette4(fxc, WHITE, GREEN,  WHITE, MAGENTA); break;
    case fx_palette_wcb: SetMicroPalette4(fxc, WHITE, CYAN,   WHITE, BLUE); break;
    case fx_palette_wcm: SetMicroPalette4(fxc, WHITE, CYAN,   WHITE, MAGENTA); break;
    case fx_palette_wbm: SetMicroPalette4(fxc, WHITE, BLUE,   WHITE, MAGENTA); break;

    case fx_palette_dry: SetMicroPalette4(fxc, DARK, RED,    DARK, YELLOW); break;
    case fx_palette_drg: SetMicroPalette4(fxc, DARK, RED,    DARK, GREEN); break;
    case fx_palette_drc: SetMicroPalette4(fxc, DARK, RED,    DARK, CYAN); break;
    case fx_palette_drb: SetMicroPalette4(fxc, DARK, RED,    DARK, BLUE); break;
    case fx_palette_drm: SetMicroPalette4(fxc, DARK, RED,    DARK, MAGENTA); break;
    case fx_palette_dyg: SetMicroPalette4(fxc, DARK, YELLOW, DARK, GREEN); break;
    case fx_palette_dyc: SetMicroPalette4(fxc, DARK, YELLOW, DARK, CYAN); break;
    case fx_palette_dyb: SetMicroPalette4(fxc, DARK, YELLOW, DARK, BLUE); break;
    case fx_palette_dym: SetMicroPalette4(fxc, DARK, YELLOW, DARK, MAGENTA); break;
    case fx_palette_dgc: SetMicroPalette4(fxc, DARK, GREEN,  DARK, CYAN); break;
    case fx_palette_dgb: SetMicroPalette4(fxc, DARK, GREEN,  DARK, BLUE); break;
    case fx_palette_dgm: SetMicroPalette4(fxc, DARK, GREEN,  DARK, MAGENTA); break;
    case fx_palette_dcb: SetMicroPalette4(fxc, DARK, CYAN,   DARK, BLUE); break;
    case fx_palette_dcm: SetMicroPalette4(fxc, DARK, CYAN,   DARK, MAGENTA); break;
    case fx_palette_dbm: SetMicroPalette4(fxc, DARK, BLUE,   DARK, MAGENTA); break;

    case fx_palette_lava:SetMicroPalette16(fxc,
        WEBRGB::Black,WEBRGB::Maroon,WEBRGB::Black,WEBRGB::Maroon,    
        WEBRGB::DarkRed,WEBRGB::Maroon,WEBRGB::DarkRed,WEBRGB::DarkRed,    
        WEBRGB::DarkRed,WEBRGB::DarkRed,WEBRGB::Red,WEBRGB::Orange,    
        WEBRGB::White,WEBRGB::Orange,WEBRGB::Red,WEBRGB::DarkRed);
      break;
    case fx_palette_cloud:SetMicroPalette16(fxc,  
      WEBRGB::Blue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,
      WEBRGB::DarkBlue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,WEBRGB::DarkBlue,
      WEBRGB::Blue,WEBRGB::DarkBlue,WEBRGB::SkyBlue,WEBRGB::SkyBlue,
      WEBRGB::LightBlue,WEBRGB::White,WEBRGB::LightBlue,WEBRGB::SkyBlue);
      break;
    case fx_palette_ocean:SetMicroPalette16(fxc,    
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
    case fx_palette_forest:SetMicroPalette16(fxc,    
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
    case fx_palette_rainbow:SetMicroPalette16(fxc, 
      0xFF0000, 0xD52A00, 0xAB5500, 0xAB7F00,
      0xABAB00, 0x56D500, 0x00FF00, 0x00D52A,
      0x00AB55, 0x0056AA, 0x0000FF, 0x2A00D5,
      0x5500AB, 0x7F0081, 0xAB0055, 0xD5002B);break;
    case fx_palette_rainbowstripe:SetMicroPalette16(fxc,    
      0xFF0000, 0x000000, 0xAB5500, 0x000000,
      0xABAB00, 0x000000, 0x00FF00, 0x000000,
      0x00AB55, 0x000000, 0x0000FF, 0x000000,
      0x5500AB, 0x000000, 0xAB0055, 0x000000);break;
    case fx_palette_party:SetMicroPalette16(fxc,   
      0x5500AB, 0x84007C, 0xB5004B, 0xE5001B,
      0xE81700, 0xB84700, 0xAB7700, 0xABAB00,
      0xAB5500, 0xDD2200, 0xF2000E, 0xC2003E,
      0x8F0071, 0x5F00A1, 0x2F00D0, 0x0007F9);break;
    case fx_palette_heat:SetMicroPalette16(fxc,
      0x000000, 0x330000, 0x660000, 0x990000, 
      0xCC0000, 0xFF0000, 0xFF3300, 0xFF6600, 
      0xFF9900, 0xFFCC00, 0xFFFF00, 0xFFFF33, 
      0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF);break;

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
