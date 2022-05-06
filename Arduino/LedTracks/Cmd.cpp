#include "Cmd.h"
#include "Fx.h"
#include "Track.h"
#include "Devices.h"

void UpdatePalette();
unsigned long GetTime();

static CaptureTextMode captureMode = CaptureNone;
static char captureBuffer[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0};
static int captureCount = 0;

void InstantEvent(FxController &fxc, int event, FxPaletteUpdateType paletteUpdateType)
{
  fxc.fxPaletteUpdateType = paletteUpdateType;
  fxc.fxState = FxState_Default;
  fxc.transitionType = Transition_Instant;
  if (event != fx_nothing)
    PrintFxEventName(event);
  FxEventProcess(fxc, event);
  UpdatePalette();
}

void magicColors(FxController &fxc, int count)
{
  int index = 0;
  if (count > 16) count = 16;
  for (int i=0;i<count;i++)
  {
    char c = captureBuffer[i];
    uint32_t crgb = ShortnameToCRGB(c);
    fxc.microPalette[i] = crgb;
    Serial.print(F("Colors["));
    Serial.print(i);
    Serial.print(F("] "));
    Serial.print(c);
    Serial.print(F(" = "));
    Serial.println(crgb,HEX);
  }
  fxc.microPaletteSize = count;
  fxc.fxPaletteUpdateType = FxPaletteUpdateType::Once;

  FxCreatePalette(fxc, fxc.microPalette, fxc.microPaletteSize);
  //fxc.updatePalette = true;
  //UpdatePalette(); 
}

void UserCommandExecute(FxController &fxc, int cmd)
{
  switch (cmd)
  {
    case Cmd_Help:
#if SYSTEM_NANO_33_BLE
  Serial.println(F("System: Arduino Nano 33 BLE"));
#elif SYSTEM_UNO
  Serial.println(F("System: Arduino UNO"));
#elif SYSTEM_NANO
  Serial.println(F("System: Arduino Nano"));
#else
  Serial.println(F("System: UNKNOWN"));
#endif
      Serial.println(F("? : Help Menu"));
      Serial.println(F("+ : Rotate Pos"));
      Serial.println(F("- : Rotate Neg"));
      Serial.println(F("( : Track Start"));
      Serial.println(F(") : Track Stop"));
      Serial.println(F("* : Track StartFrom"));
      Serial.println(F("!code : Color code"));
      Serial.println(F("@code : Time code"));
      Serial.println(F("[ b n m , ] : Brightness"));
      Serial.println(F("z:default mode x:test c:imu"));
      Serial.println(F("0:dark 1:white 2:red 3:yellow 4:green 5:cyan 6:blue 7:magenta 8:orange 9:half"));
      Serial.println(F("q:lava w:cloud e:ocean r:forest t:rainbow y:rainbowstripe u:party i:heat"));
        
      break;
    case Cmd_State_Default: fxc.fxState = FxState_Default;break;
    case Cmd_State_Test:    fxc.fxState = FxState_TestPattern;break;
    case Cmd_State_IMU:     fxc.fxState = FxState_IMU;break;
      
    case Cmd_PlayFromStart: trackStart(fxc, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), FxTrackEndAction::StopAtEnd); break;
    case Cmd_PlayFrom:      fxc.fxState = FxState_PlayingTrack;break;
    case Cmd_PlayStop:      trackStop(fxc); break;

    case Cmd_SpeedNeg:      InstantEvent(fxc, fx_speed_neg, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedPos:      InstantEvent(fxc, fx_speed_pos, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedDec:      InstantEvent(fxc, fx_speed_dec, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedInc:      InstantEvent(fxc, fx_speed_inc, FxPaletteUpdateType::Once); break;
    case Cmd_SpeedRst:      InstantEvent(fxc, fx_speed_0,   FxPaletteUpdateType::Once); break;
    
    case Cmd_ColorDark:     InstantEvent(fxc, fx_palette_dark,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorWhite:    InstantEvent(fxc, fx_palette_white,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorRed:      InstantEvent(fxc, fx_palette_red,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorYellow:   InstantEvent(fxc, fx_palette_yellow,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorGreen:    InstantEvent(fxc, fx_palette_green,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorCyan:     InstantEvent(fxc, fx_palette_cyan,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorBlue:     InstantEvent(fxc, fx_palette_blue,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorMagenta:  InstantEvent(fxc, fx_palette_magenta,  FxPaletteUpdateType::Once); break;
    case Cmd_ColorOrange:   InstantEvent(fxc, fx_palette_orange,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorHalf:     InstantEvent(fxc, fx_palette_half,     FxPaletteUpdateType::Once); break;

    case Cmd_ColorRedBlue:      InstantEvent(fxc, fx_palette_rb,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorCyanMagenta:   InstantEvent(fxc, fx_palette_cm,      FxPaletteUpdateType::Once); break;

    case Cmd_ColorPulseDark:     InstantEvent(fxc, fx_palette_pulse_dark,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseWhite:    InstantEvent(fxc, fx_palette_pulse_white,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseRed:      InstantEvent(fxc, fx_palette_pulse_red,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseYellow:   InstantEvent(fxc, fx_palette_pulse_yellow,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseGreen:    InstantEvent(fxc, fx_palette_pulse_green,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseCyan:     InstantEvent(fxc, fx_palette_pulse_cyan,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseBlue:     InstantEvent(fxc, fx_palette_pulse_blue,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseMagenta:  InstantEvent(fxc, fx_palette_pulse_magenta,  FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseOrange:   InstantEvent(fxc, fx_palette_pulse_orange,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulseHalf:     InstantEvent(fxc, fx_palette_pulse_half,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Dark:     InstantEvent(fxc, fx_palette_pulse2_dark,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2White:    InstantEvent(fxc, fx_palette_pulse2_white,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Red:      InstantEvent(fxc, fx_palette_pulse2_red,      FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Yellow:   InstantEvent(fxc, fx_palette_pulse2_yellow,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Green:    InstantEvent(fxc, fx_palette_pulse2_green,    FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Cyan:     InstantEvent(fxc, fx_palette_pulse2_cyan,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Blue:     InstantEvent(fxc, fx_palette_pulse2_blue,     FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Magenta:  InstantEvent(fxc, fx_palette_pulse2_magenta,  FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Orange:   InstantEvent(fxc, fx_palette_pulse2_orange,   FxPaletteUpdateType::Once); break;
    case Cmd_ColorPulse2Half:     InstantEvent(fxc, fx_palette_pulse2_half,   FxPaletteUpdateType::Once); break;
       
    case Cmd_ColorLava:           InstantEvent(fxc, fx_palette_lava,          FxPaletteUpdateType::Once); break;
    case Cmd_ColorCloud:          InstantEvent(fxc, fx_palette_cloud,         FxPaletteUpdateType::Once); break;
    case Cmd_ColorOcean:          InstantEvent(fxc, fx_palette_ocean,         FxPaletteUpdateType::Once); break;
    case Cmd_ColorForest:         InstantEvent(fxc, fx_palette_forest,        FxPaletteUpdateType::Once); break;
    case Cmd_ColorRainbow:        InstantEvent(fxc, fx_palette_rainbow,       FxPaletteUpdateType::Once); break;
    case Cmd_ColorRainbowstripe:  InstantEvent(fxc, fx_palette_rainbowstripe, FxPaletteUpdateType::Once); break;
    case Cmd_ColorParty:          InstantEvent(fxc, fx_palette_party,         FxPaletteUpdateType::Once); break;
    case Cmd_ColorHeat:           InstantEvent(fxc, fx_palette_heat,          FxPaletteUpdateType::Once); break;

    case Cmd_ColorImu:            InstantEvent(fxc, fx_palette_gyro,          FxPaletteUpdateType::Once); break;

#if ENABLE_NEOPIXEL && ENABLE_BRIGHTNESS
    case Cmd_Brightness_VeryHigh: neopixelSetBrightness(250);break;
    case Cmd_Brightness_High: neopixelSetBrightness(150);break;
    case Cmd_Brightness_Normal: neopixelSetBrightness(50);break;
    case Cmd_Brightness_Low: neopixelSetBrightness(20);break;
#endif    

    default: break;
  }
}

void processCapturedText(FxController &fxc)
{
  if (captureMode == CaptureColorCode)
  {  
    Serial.print(F("ColorDef("));
    Serial.print(captureCount);
    Serial.print(F(")=("));
    for (int i = 0; i < captureCount; i++)
      Serial.print((char)captureBuffer[i]);
    Serial.print(F(")"));
    Serial.println();

    //Magic colors is currently broken as it breaks serial print for some unknown reason
    magicColors(fxc,captureCount);
    captureCount = 0;
    captureMode = CaptureNone;
  }
  else if (captureMode == CaptureTimeCode)
  { 
    captureMode = CaptureNone;
    Serial.print(F("TimeCodeBuf( "));
    for (int i = 0; i < captureCount; i++)
    {
      Serial.print((char)captureBuffer[i]);    
      Serial.print(F(" "));
    }
    Serial.print(F(")"));
    captureBuffer[captureCount] = 0;
    Serial.print(F("=\""));
    Serial.print(captureBuffer);
    Serial.print(F("\""));
    unsigned long tc = atol(captureBuffer);
    Serial.print(F("TC:"));
    Serial.print(tc);
    int prevmatch = GetPreviousTimeCodeMatch(tc);    
    setTimecodeLastMatched(SongTrack_timecode(prevmatch));
    setTimecodeSongOffset(tc);  
    Serial.print(F(" vs t="));
    Serial.print(GetTime());
    Serial.print(F(", to="));
    Serial.print(getTimecodeTimeOffset());
    setTimecodeTimeOffset(millis());
    Serial.print(F(", "));
    Serial.print(getTimecodeLastMatched());
    Serial.print(F("="));
    Serial.print(getTimecodeSongOffset());
    Serial.print(F(",P:"));
    Serial.print(prevmatch);
    Serial.println(F(""));

    trackStart(fxc,tc, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), FxTrackEndAction::StopAtEnd);
  }
}

void UserCommandInput(FxController &fxc, int data)
{
  if (captureMode == CaptureColorCode && data != 10 && data != 13)
  {
    if (captureCount < 16)
    {
      captureBuffer[captureCount] = (char)data;
      captureCount++;
    }
    return;
  }   

  if (captureMode == CaptureTimeCode && data != 10 && data != 13)
  {
    if (captureCount < 15)
    {
      Serial.print(F("CC="));
      Serial.print(data);
      captureBuffer[captureCount] = (char)data;
      captureBuffer[captureCount+1] = 0;
      captureCount++;
    }
    return;
  }

  switch (data)
  {
    case '!':
      Serial.print(F("Capturing ColorCode"));
      captureCount = 0;
      captureMode = CaptureColorCode;
      break;
    case '@':
      Serial.print(F("Capturing TimeCode"));
      captureCount = 0;
      //capturedTimeCode = "";
      captureMode = CaptureTimeCode;
      break;
    case '?': UserCommandExecute(fxc, Cmd_Help); break;
      
    case 'z': UserCommandExecute(fxc, Cmd_State_Default);break;
    case 'x': UserCommandExecute(fxc, Cmd_State_Test);break;
    case 'c': UserCommandExecute(fxc, Cmd_State_IMU);break;      
    
    case ')': UserCommandExecute(fxc, Cmd_PlayFromStart); break;
    case '*': UserCommandExecute(fxc, Cmd_PlayFrom); break;
    case '(': UserCommandExecute(fxc, Cmd_PlayStop); break;
    
    case '0': UserCommandExecute(fxc, Cmd_ColorDark); break;
    case '1': UserCommandExecute(fxc, Cmd_ColorWhite); break;
    case '2': UserCommandExecute(fxc, Cmd_ColorRed); break;
    case '3': UserCommandExecute(fxc, Cmd_ColorYellow); break;
    case '4': UserCommandExecute(fxc, Cmd_ColorGreen); break;
    case '5': UserCommandExecute(fxc, Cmd_ColorCyan); break;
    case '6': UserCommandExecute(fxc, Cmd_ColorBlue); break;
    case '7': UserCommandExecute(fxc, Cmd_ColorMagenta); break;
    case '8': UserCommandExecute(fxc, Cmd_ColorOrange); break;
    case '9': UserCommandExecute(fxc, Cmd_ColorHalf); break;

    case 'a': UserCommandExecute(fxc, Cmd_ColorPulseDark); break;
    case 's': UserCommandExecute(fxc, Cmd_ColorPulseWhite); break;
    case 'd': UserCommandExecute(fxc, Cmd_ColorPulseRed); break;
    case 'f': UserCommandExecute(fxc, Cmd_ColorPulseYellow); break;
    case 'g': UserCommandExecute(fxc, Cmd_ColorPulseGreen); break;
    case 'h': UserCommandExecute(fxc, Cmd_ColorPulseCyan); break;
    case 'j': UserCommandExecute(fxc, Cmd_ColorPulseBlue); break;
    case 'k': UserCommandExecute(fxc, Cmd_ColorPulseMagenta); break;
    case 'l': UserCommandExecute(fxc, Cmd_ColorPulseOrange); break;
    case 'm': UserCommandExecute(fxc, Cmd_ColorPulseHalf); break;
    
    case ';': UserCommandExecute(fxc, Cmd_ColorImu);break;
    
    case 'A': UserCommandExecute(fxc, Cmd_ColorPulse2Dark); break;
    case 'S': UserCommandExecute(fxc, Cmd_ColorPulse2White); break;
    case 'D': UserCommandExecute(fxc, Cmd_ColorPulse2Red); break;
    case 'F': UserCommandExecute(fxc, Cmd_ColorPulse2Yellow); break;
    case 'G': UserCommandExecute(fxc, Cmd_ColorPulse2Green); break;
    case 'H': UserCommandExecute(fxc, Cmd_ColorPulse2Cyan); break;
    case 'J': UserCommandExecute(fxc, Cmd_ColorPulse2Blue); break;    
    case 'K': UserCommandExecute(fxc, Cmd_ColorPulse2Magenta); break;
    case 'L': UserCommandExecute(fxc, Cmd_ColorPulse2Orange); break;
    case 'M': UserCommandExecute(fxc, Cmd_ColorPulse2Half); break;
    
    case 'q': UserCommandExecute(fxc, Cmd_ColorRedBlue);break;
    case 'w': UserCommandExecute(fxc, Cmd_ColorCyanMagenta);break;

    case 'Q': UserCommandExecute(fxc, Cmd_ColorLava);break;
    case 'W': UserCommandExecute(fxc, Cmd_ColorCloud);break;
    case 'E': UserCommandExecute(fxc, Cmd_ColorOcean);break;
    case 'R': UserCommandExecute(fxc, Cmd_ColorForest);break;
    case 'T': UserCommandExecute(fxc, Cmd_ColorRainbow);break;
    case 'Y': UserCommandExecute(fxc, Cmd_ColorRainbowstripe);break;
    case 'U': UserCommandExecute(fxc, Cmd_ColorParty);break;
    case 'I': UserCommandExecute(fxc, Cmd_ColorHeat);break;

    case '_': UserCommandExecute(fxc, Cmd_SpeedNeg);break;
    case '+': UserCommandExecute(fxc, Cmd_SpeedPos);break;
    case '-': UserCommandExecute(fxc, Cmd_SpeedDec);break;
    case '=': UserCommandExecute(fxc, Cmd_SpeedInc);break;
    case '~': UserCommandExecute(fxc, Cmd_SpeedRst);break;

    case 'b': UserCommandExecute(fxc, Cmd_Brightness_High);break;
    case 'n': UserCommandExecute(fxc, Cmd_Brightness_Normal);break;
    //case 'm': UserCommandExecute(fxc, Cmd_Brightness_Low);break;
    case ',': UserCommandExecute(fxc, Cmd_Brightness_VeryHigh);break;

    
    case 10:
    case 13:
      if (captureMode != CaptureNone)
      {
        Serial.println(F("Capture end"));
        processCapturedText(fxc);
      }
      //else Serial.println(F("UnkCR"));
    case 0:
    case 225: break;
    default:
      Serial.print(F("unk:"));
      Serial.println(data);
      break;
  }
}
