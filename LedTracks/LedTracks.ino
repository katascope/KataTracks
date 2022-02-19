// LightDrive : A time-track event system for Addressable LED
// Purpose is for a wearable dance-synchronized lightsuit.
//#include <avr/pgmspace.h>
#include "Config.h"
#include "Timecode.h"
#include "Fx.h"
#include "Track.h"
#include "Commands.h"

static FxController fxController;
static uint32_t palette16[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static CaptureTextMode captureMode = CaptureNone;
static char captureBuffer[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int captureCount = 0;
static String capturedTimeCode = "";

unsigned long GetTime()
{ 
  return (unsigned long)((signed long)millis() - (signed long)getTimecodeTimeOffset() + getTimecodeSongOffset()); 
}

void setup() {
  fxController.fxState = FxState_Default;//TestPattern;
  //static FxState fxState = FxState_Default;
  //static FxState fxState = FxState_PlayingTrack;
  Serial.begin(SERIAL_BAUD_RATE); //serial communication at 9600 bauds
  Serial.print(F("Serial init "));
  Serial.println(SERIAL_BAUD_RATE);

#if ENABLE_NEOPIXEL
  Serial.println(F("Delaying 3 seconds for LEDs."));
  delay( 3000 ); // power-up safety delay
  neopixelSetup();
  PaletteGradient(fxController.palette);
  Serial.print(F("NeoPixel init "));
  Serial.print(NUM_LEDS);
  Serial.print(F(" LEDs on pin "));
  Serial.println(LED_PIN);
#else
  Serial.println(F("No NeoPixel init"));
#endif

#if ENABLE_BLE
  Serial.println(F("BLE init"));
  bleSetup();
#else
  Serial.println(F("No BLE init"));
#endif

#if ENABLE_BLUETOOTH
  Serial.print(F("BT init "));
  Serial.println(BLUETOOTH_BAUD_RATE);
  bluetooth.begin(BLUETOOTH_BAUD_RATE);
#else
  Serial.println(F("No BT init"));
#endif

#if ENABLE_IMU
  Serial.println(F("IMU init"));
  imuSetup();
#else
  Serial.println(F("No IMU init"));
#endif

  if (fxController.fxState == FxState_PlayingTrack)
    trackStart(fxController, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY));
  else Serial.println(F("Ready"));

  if (fxController.fxState == FxState_TestPattern)
  {
    FxEventProcess(fxController, fx_palette_drb);
    fxController.paletteDirection = 1;
    fxController.paletteSpeed = 1;
    fxController.animatePalette = true;
  }

  Serial.println("Setup complete.");
}

void SetPalette()
{
  if (fxController.animatePalette)
  {
    fxController.paletteIndex = fxController.paletteIndex + (fxController.paletteSpeed * fxController.paletteDirection);
    if (fxController.paletteIndex >= NUM_LEDS)
      fxController.paletteIndex -= NUM_LEDS;
    if (fxController.paletteIndex < 0)
      fxController.paletteIndex = NUM_LEDS - 1;
  }

#if ENABLE_NEOPIXEL
  //neopixelSetPalette(fxController);
  neopixelSetPalette(fxController.palette, fxController.paletteIndex);
#endif
}

void FxEventPoll(unsigned long timecode)
{
  int match = GetCurrentTimeCodeMatch(timecode);
  int nextmatch = GetNextTimeCodeMatch(match);
  unsigned long matchedTimecode = SongTrack_timecode(match);
  unsigned long nextMatchedTimecode = SongTrack_timecode(nextmatch);

  if (matchedTimecode > getTimecodeLastMatched())
  {
    if (fxController.transitionType == Transition_TimedWipePos || fxController.transitionType == Transition_TimedWipeNeg)
    {
      CopyPalette(fxController.palette, fxController.nextPalette);
    }
    fxController.transitionType = Transition_Instant;
    fxController.animatePalette = true;

    FxTrackSay(timecode, matchedTimecode, nextMatchedTimecode);
    /*PrintLog(String((float)matchedTimecode / (float)1000.0f));
      PrintLog(F(" : next @ "));
      PrintLogln(String((float)nextMatchedTimecode / (float)1000.0f));*/

    for (int i = 0; i < numSongTracks; i++)
      if (SongTrack_timecode(i) == matchedTimecode)
        FxEventProcess(fxController, SongTrack_event(i));

    setTimecodeLastMatched(timecode);//timeController.lastMatchedTimecode = timecode;
  }

  unsigned long totalSpan = nextMatchedTimecode - getTimecodeLastMatched();
  fxController.transitionMux = ((float)timecode - (float)getTimecodeLastMatched() ) / (float)totalSpan;

  if (fxController.transitionType == Transition_TimedFade)
  {
    //Interpolate initial palette to next palette, based on transition (0 to 1)
    for (int i = 0; i < NUM_LEDS; i++)
    {
      uint32_t rgb = LerpRGB(fxController.transitionMux,
                             fxController.initialPalette[i],
                             fxController.nextPalette[i]);
      fxController.palette[i] = rgb;
    }
  }
  if (fxController.transitionType == Transition_TimedWipePos)
  {
    float mux = (1 - fxController.transitionMux);
    int limit = mux * (NUM_LEDS - 1);
    CopyPalette(fxController.palette, fxController.initialPalette);
    for (int i = NUM_LEDS - 1; i >= limit; i--)
      fxController.palette[i] = fxController.nextPalette[i];
    fxController.paletteIndex = mux * NUM_LEDS;
  }
  if (fxController.transitionType == Transition_TimedWipeNeg)
  {
    float mux = fxController.transitionMux;
    int limit = mux * (NUM_LEDS - 1);
    CopyPalette(fxController.palette, fxController.initialPalette);
    for (int i = NUM_LEDS; i >= limit; i--)
      fxController.palette[i] = fxController.nextPalette[i];
    fxController.paletteIndex = mux * NUM_LEDS;
  }
}

void StatePoll(FxController &fxc)
{
  if (fxc.fxState == FxState_IMU)
  {
#if ENABLE_IMU
    /*if ( IMU.accelerationAvailable() )
      IMU.readAcceleration( fxc.imu.accelX, fxc.imu.accelY, fxc.imu.accelZ );
      if ( IMU.gyroscopeAvailable() )
      IMU.readGyroscope( fxc.imu.gyroX, fxc.imu.gyroY, fxc.imu.gyroZ );

      //PrintLogln(F("IMUMode"));
      //FxEventProcess(fx_palette_drb);
      //FxEventProcess(fx_palette_accel);
      //byte r = (float)((float)127.0f-(float)imuGyroX*120.0f);
      //byte g = (float)((float)127.0f-(float)imuGyroY*120.0f);
      //byte b = (float)((float)127.0f-(float)imuGyroZ*120.0f);

      byte r = 0;//(float)((float)127.0f-(float)imuGyroX*1.0f);
      byte g = (float)((float)127.0f-(float)imuGyroY*1.0f);
      byte b = (float)((float)127.0f-(float)imuGyroZ*1.0f);

      fxc.palette[0] = LEDRGB(r,g,b);
      rotPalette();
      fxc.paletteDirection = 0;
      fxc.paletteSpeed = 0;
      fxc.animatePalette = true;*/
#endif
  }
  if (fxc.fxState == FxState_TestPattern)
  {
    FxEventProcess(fxc, fx_palette_drb);
    fxc.paletteDirection = 2;
    fxc.paletteSpeed = 2;
    fxc.animatePalette = true;
  }

  if (fxc.fxState == FxState_PlayingTrack)
    FxEventPoll(GetTime());
}

static unsigned long lastTimeDisplay = 0;
void DisplayStatus(FxController &fxc)
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
      Serial.print(F("]"));
      if (fxc.fxState == FxState_PlayingTrack)
      {
        int match = GetCurrentTimeCodeMatch(GetTime());
        Serial.print(F("="));
        PrintFxEventName(SongTrack_event(match));
        Serial.print(F(" "));
        Serial.print(SongTrack_timecode(match));
      }

      Serial.println(F(""));
      
      lastTimeDisplay = t;
    }
}


void DirectEvent(FxController &fxc, int event)
{
  fxc.fxState = FxState_Default;
  fxc.transitionType = Transition_Instant;
  if (event != fx_nothing)
    PrintFxEventName(event);
  FxEventProcess(fxc, event);
}


void magicColors(FxController &fxc, int count)
{
  int index = 0;
  for (int i=0;i<16;i++)
  {
    char c = captureBuffer[index];
    uint32_t crgb = ShortnameToCRGB(c);
    palette16[i] = crgb;
    index++;
    if (index > count) index = 0;  
  }
  CreatePaletteBands(fxc,//v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15);
    palette16[0],  palette16[1],  palette16[2],  palette16[3], 
    palette16[4],  palette16[5],  palette16[6],  palette16[7], 
    palette16[8],  palette16[9],  palette16[10], palette16[11], 
    palette16[12], palette16[13], palette16[14], palette16[15]);
  //animatePalette = false;
  
  DirectEvent(fxc, fx_nothing);
  SetPalette(); 
}

void processCapturedText(FxController &fxc)
{
  if (captureMode == CaptureColorCode)
  {  
    Serial.print(F("ColorDef("));
    Serial.print(captureCount);
    Serial.print(F(")=("));
    for (int i = 0; i < captureCount; i++)
    {
      Serial.print((char)captureBuffer[i]);
    }
    Serial.print(F(")"));
    Serial.println();

    //Magic colors is currently broken as it breaks serial print for some unknown reason
    magicColors(fxc,captureCount);
    captureCount = 0;
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
  

    Serial.print(F("TC:"));
    Serial.print(tc);
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

    trackStart(fxc,tc, (unsigned long)(millis() - (signed long)TRACK_START_DELAY));

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
      Serial.println(F("? : Help Menu"));
      Serial.println(F("+ : Rotate Pos"));
      Serial.println(F("- : Rotate Neg"));
      Serial.println(F("( : Track Start"));
      Serial.println(F(") : Track Stop"));
      Serial.println(F("0-9 : Color"));
      Serial.println(F("!code : Color code"));
      Serial.println(F("(q)lava (w)cloud (e)ocean (r)forest (t)rainbow (y)rainbowstripe (u)party (i)heat"));
      break;
    case Cmd_State_Default: fxc.fxState = FxState_Default;break;
    case Cmd_State_Test:    fxc.fxState = FxState_TestPattern;break;
    case Cmd_State_IMU:     fxc.fxState = FxState_IMU;break;
      
    case Cmd_PlayFromStart: trackStart(fxc, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY)); break;
    case Cmd_PlayFrom:      fxc.fxState = FxState_PlayingTrack;break;
    case Cmd_PlayStop:      trackStop(fxc); break;

    case Cmd_SpeedNeg:      fxc.animatePalette = true; DirectEvent(fxc, fx_speed_neg); break;
    case Cmd_SpeedPos:      fxc.animatePalette = true; DirectEvent(fxc, fx_speed_pos); break;
    case Cmd_SpeedDec:      fxc.animatePalette = true; DirectEvent(fxc, fx_speed_dec); break;
    case Cmd_SpeedInc:      fxc.animatePalette = true; DirectEvent(fxc, fx_speed_inc); break;
    case Cmd_SpeedRst:      fxc.animatePalette = true; DirectEvent(fxc, fx_speed_0); break;
    
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
    if (captureCount < 16)
    {
      captureBuffer[captureCount] = (char)data;
      captureCount++;
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
      captureCount = 0;
      captureMode = CaptureColorCode;
      break;
    case '@':
      //PrintLogln(F("Capturing TimeCode"));
      captureCount = 0;
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
      Serial.print(F("unk:"));
      Serial.println(String(data));
      break;
  }
}
static unsigned long lastTimeLed = 0;
void loop()
{
  while (Serial.available())
  {
    int data = Serial.read();
    Serial.print("UC:");
    Serial.println(data);    
    UserCommandInput(fxController, data);
  }
#if BLUETOOTH_ENABLE
  while (bluetooth.available())
    UserCommandInput(fxController, bluetooth.read());
#endif

  StatePoll(fxController);

#if ENABLE_BLE
  bleloop();
#endif

  if (fxController.fxState == FxState_PlayingTrack || fxController.animatePalette)
  {
    unsigned long t =  millis();
    if (t - lastTimeLed > 45)//delay to let bluetooth get data
    {
      SetPalette();
      lastTimeLed = t;
    }
  }

#if ENABLE_STATUS
  DisplayStatus(fxController);
#endif
}
