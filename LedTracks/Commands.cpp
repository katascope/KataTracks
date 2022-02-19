#include "Commands.h"
#include "Timecode.h"
#include "Track.h"

void SetPalette();
unsigned long GetTime();

static CaptureTextMode captureMode = CaptureNone;
static char colorDefinitionStack[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int colorDefinitionCount = 0;
static String capturedTimeCode = "";

static void DirectEvent(FxController &fxc, int event)
{
  fxc.fxState = FxState_Default;
  fxc.transitionType = Transition_Instant;
  if (event != fx_nothing)
    PrintLogln(FxEventName(event));
  FxEventProcess(fxc, event);
}

void SetPalette();
unsigned long GetTime();
static void magicColors(FxController &fxc, int count, char *colors)
{
  uint32_t palette16[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int index = 0;
  for (int i=0;i<16;i++)
  {
    palette16[i] = ShortnameToCRGB(colors[index]);
    index++;
    if (index >= count) index = 0;  
  }
  CreatePaletteBands(fxc,
    palette16[0],  palette16[1],  palette16[2],  palette16[3], 
    palette16[4],  palette16[5],  palette16[6],  palette16[7], 
    palette16[8],  palette16[9],  palette16[10], palette16[11], 
    palette16[12], palette16[13], palette16[14], palette16[15]);
  
  //animatePalette = false; 
  DirectEvent(fxc, fx_nothing);
  SetPalette(); 
}

static void processCapturedText(FxController &fxc)
{
  if (captureMode == CaptureColorCode)
  {  
    PrintLog(F("ColorDef("));
    PrintLog(String(colorDefinitionCount));
    PrintLog(F(")"));
    for (int i = 0; i < colorDefinitionCount; i++)
    {
      PrintLog(F(" "));
      PrintLog(String((char)colorDefinitionStack[i]));
    }
    PrintLogln(F(""));
    
    magicColors(fxc,colorDefinitionCount, &colorDefinitionStack[0]);
    colorDefinitionCount = 0;
    captureMode = CaptureNone;
  }
  else if (captureMode == CaptureTimeCode)
  { 
    //PrintLog(F("GOT:"));
    //PrintLogln(String(capturedTimeCode));
    captureMode = CaptureNone;
    //fxState == FxState_PlayingTrack;
    unsigned long tc = capturedTimeCode.toInt();
    //int match = GetCurrentTimeCodeMatch(tc);
    //int nextmatch = GetNextTimeCodeMatch(match);
    int prevmatch = GetPreviousTimeCodeMatch(tc);
    
    setTimecodeLastMatched(SongTrack_timecode(prevmatch));

    /*timeOffset = millis();
    timeOffset -= tc;*/

    //timeController.songOffset = tc;
    setTimecodeSongOffset(tc);
  

    PrintLog(F("TC:"));
    PrintLog(String(tc));
    PrintLog(F(" vs t="));
    PrintLog(String(GetTime()));
    PrintLog(F(", to="));
    PrintLog(String(getTimecodeTimeOffset()));
    setTimecodeTimeOffset(millis());
    PrintLog(F(", "));
    PrintLog(String(getTimecodeLastMatched()));
    PrintLog(F("="));
    PrintLog(String(getTimecodeSongOffset()));
    PrintLog(F(",P:"));
    PrintLog(String(prevmatch));
    PrintLogln(F(""));

    trackStart(fxc,tc);

  /*  PrintLog(F(" Match:"));
    PrintLog(String(match));
    PrintLog(F(","));
    PrintLog(F(", now t="));
    PrintLog(String(GetTime()));
    PrintLogln(F(""));
*/
    
  }
}

void UserCommandExecute(FxController &fxc, int cmd)
{
  switch (cmd)
  {
    case Cmd_Help:
      PrintLogln(F("? : Help Menu"));
      PrintLogln(F("+ : Rotate Pos"));
      PrintLogln(F("- : Rotate Neg"));
      PrintLogln(F("( : Track Start"));
      PrintLogln(F(") : Track Stop"));
      PrintLogln(F("0-9 : Color"));
      PrintLogln(F("!code : Color code"));
      PrintLogln(F("(q)lava (w)cloud (e)ocean (r)forest (t)rainbow (y)rainbowstripe (u)party (i)heat"));
      break;
    case Cmd_State_Default: fxc.fxState = FxState_Default;break;
    case Cmd_State_Test:    fxc.fxState = FxState_TestPattern;break;
    case Cmd_State_IMU:     fxc.fxState = FxState_IMU;break;
      
    case Cmd_PlayFromStart: trackStart(fxc, 0); break;
    case Cmd_PlayFrom:      fxc.fxState = FxState_PlayingTrack;break;
    case Cmd_PlayStop:      trackStop(fxc); break;

    case Cmd_SpeedNeg: fxc.animatePalette = true; DirectEvent(fxc, fx_speed_neg); break;
    case Cmd_SpeedPos: fxc.animatePalette = true; DirectEvent(fxc, fx_speed_pos); break;
    case Cmd_SpeedDec: fxc.animatePalette = true; DirectEvent(fxc, fx_speed_dec); break;
    case Cmd_SpeedInc: fxc.animatePalette = true; DirectEvent(fxc, fx_speed_inc); break;
    case Cmd_SpeedRst: fxc.animatePalette = true; DirectEvent(fxc, fx_speed_0); break;
    
    case Cmd_ColorDark:     fxc.animatePalette = false; DirectEvent(fxc, fx_palette_dark); SetPalette(); break;
    case Cmd_ColorWhite:    fxc.animatePalette = false; DirectEvent(fxc, fx_palette_white); SetPalette(); break;
    case Cmd_ColorRed:      fxc.animatePalette = false; DirectEvent(fxc, fx_palette_red); SetPalette(); break;
    case Cmd_ColorYellow:   fxc.animatePalette = false; DirectEvent(fxc, fx_palette_yellow); SetPalette(); break;
    case Cmd_ColorGreen:    fxc.animatePalette = false; DirectEvent(fxc, fx_palette_green); SetPalette(); break;
    case Cmd_ColorCyan:     fxc.animatePalette = false; DirectEvent(fxc, fx_palette_cyan); SetPalette(); break;
    case Cmd_ColorBlue:     fxc.animatePalette = false; DirectEvent(fxc, fx_palette_blue); SetPalette(); break;
    case Cmd_ColorMagenta:  fxc.animatePalette = false; DirectEvent(fxc, fx_palette_magenta); SetPalette(); break;
    case Cmd_ColorOrange:   fxc.animatePalette = false; DirectEvent(fxc, fx_palette_orange); SetPalette(); break;
    case Cmd_ColorHalf:     fxc.animatePalette = false; DirectEvent(fxc, fx_palette_half); SetPalette(); break;

    case Cmd_ColorLava:           DirectEvent(fxc, fx_palette_lava); SetPalette(); break;
    case Cmd_ColorCloud:          DirectEvent(fxc, fx_palette_cloud); SetPalette(); break;
    case Cmd_ColorOcean:          DirectEvent(fxc, fx_palette_ocean); SetPalette(); break;
    case Cmd_ColorForest:         DirectEvent(fxc, fx_palette_forest); SetPalette(); break;
    case Cmd_ColorRainbow:        DirectEvent(fxc, fx_palette_rainbow); SetPalette(); break;
    case Cmd_ColorRainbowstripe:  DirectEvent(fxc, fx_palette_rainbowstripe); SetPalette(); break;
    case Cmd_ColorParty:          DirectEvent(fxc, fx_palette_party); SetPalette(); break;
    case Cmd_ColorHeat:           DirectEvent(fxc, fx_palette_heat); SetPalette(); break;
    default: break;
  }
}

void UserCommandInput(FxController &fxc, int data)
{
  if (captureMode == CaptureColorCode && data != 10 && data != 13)
  {
    if (colorDefinitionCount < 16)
    {
      colorDefinitionStack[colorDefinitionCount] = (char)data;
      colorDefinitionCount++;
    }
    return;
  }   

  if (captureMode == CaptureTimeCode && data != 10 && data != 13)
  {
    capturedTimeCode = capturedTimeCode + (char)data;
    return;
  }

  switch (data)
  {
    case '!':
      //PrintLogln(F("Capturing ColorCode"));
      captureMode = CaptureColorCode;
      break;
    case '@':
      //PrintLogln(F("Capturing TimeCode"));
      capturedTimeCode = "";
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
    
    case 'q': UserCommandExecute(fxc, Cmd_ColorLava);break;
    case 'w': UserCommandExecute(fxc, Cmd_ColorCloud);break;
    case 'e': UserCommandExecute(fxc, Cmd_ColorOcean);break;
    case 'r': UserCommandExecute(fxc, Cmd_ColorForest);break;
    case 't': UserCommandExecute(fxc, Cmd_ColorRainbow);break;
    case 'y': UserCommandExecute(fxc, Cmd_ColorRainbowstripe);break;
    case 'u': UserCommandExecute(fxc, Cmd_ColorParty);break;
    case 'i': UserCommandExecute(fxc, Cmd_ColorHeat);break;

    case '_': UserCommandExecute(fxc, Cmd_SpeedNeg);break;
    case '+': UserCommandExecute(fxc, Cmd_SpeedPos);break;
    case '-': UserCommandExecute(fxc, Cmd_SpeedDec);break;
    case '=': UserCommandExecute(fxc, Cmd_SpeedInc);break;
    case '~': UserCommandExecute(fxc, Cmd_SpeedRst);break;
    
    case 10:
    case 13:
      if (captureMode != CaptureNone)
        processCapturedText(fxc);
    case 0:
    case 225: break;
    default:
      PrintLog(F("unk:"));
      PrintLogln(String(data));
      break;
  }
}



static unsigned long lastTimeDisplay = 0;
void DisplayStatus(FxController &fxc)
{
    unsigned long t =  millis();
    if (t - lastTimeDisplay > 1000)//delay to let bluetooth get data
    {
      PrintLog(String(GetTime()));
      PrintLog(F(":"));
      PrintLog(String(getTimecodeSongOffset()));
      PrintLog(F(":"));
      PrintLog(String(getTimecodeTimeOffset()));
      PrintLog(F("["));
      PrintLog(FxStateName(fxc.fxState));
      PrintLog(F("-"));
      PrintLog(FxTransitionName(fxc.transitionType));
      PrintLog(F(""));
      PrintLog(F("]"));
      if (fxc.fxState == FxState_PlayingTrack)
      {
        int match = GetCurrentTimeCodeMatch(GetTime());
        PrintLog(F("="));
        PrintLog(FxEventName(SongTrack_event(match)));
        PrintLog(F(" "));
        PrintLog(String(SongTrack_timecode(match)));
      }

      PrintLogln(F(""));
      lastTimeDisplay = t;
    }
}
