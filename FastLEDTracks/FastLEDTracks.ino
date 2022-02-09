// FastLEDTracks : A time-track event system for FastLED
// Author: Layne Thomas
// Purpose is for a wearable dance-synchronized light-suit.
// Uses:
//  FastLED for addressable LED
//  SoftwareSerial for BlueTooth
//  Fx for LED effects
//  Track for track system
/*
   Design Criteria:
    Audioreactive : The device must represent the dance music.
    Lead-Follow : The follow device can synchronize with the lead device.
    Simple : The device must be extremely easy to use once setup.
    Reliable : The software must work correctly during the dance.
     Care with overloading bluetooth buffer
     Startup 3 seconds for led safety
    Minimal : The device must strenously optimize RAM usage.
     PROGMEM for Track - Can expand without using RAM
     See: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
    Configurable : The code must be highly configurable by #DEFINE.
    Recoverable : The device should be able to recover from mistimings.
    Cheap : The device must be low cost and easy to produce.
    Portable : The device must be human wearable and untethered.
    Stable : The device must withstand repeated heavy use dancing.
    Subtle : Indirect lighting for led's, hazed frosted fogged.
    Compatible : The device must maximize use of standards.
     Arduino Nano : Standard microcontroller kit
     WS2811 : Addressable LED wire : Standard 3-wire connectors
     BTF-Lighting Connectors : Addressable 3-wire LED wire connectors
     Also used for power connector into arduino.
     XT-60 Battery connector with D-Sun BEC Voltage convert (3-cell 12v down to 5v)
      or 18650 Battery Shield case using 5-V output
     Thingiverse Case & plans
     ffmpeg for Spectrum Analysis
     HC-05 Bluetooth https://www.evelta.com/blog/instructions-to-set-bluetooth-module-hc05-password-using-arduino/
      AT+NAME?
      AT+NAME="LedLight"
      AT+PSWD="3838"
     Master+Slave BT bindings: https://www.instructables.com/Arduino-Bluetooth-Master-and-Slave-Using-Any-HC-05/
   Tradeoffs:
     Audio track setup does not have to be easy or quick.
     Different arduinos can be used.
     Different forms of power/battery can be used.
     Arduino Micro Pro can be used if possible instead of Arduino Nano
   Aesthetic Criteria:
     Tasteful : Use complex colors, avoid 'rgb rainbow land'
     Smooth : Fading color transitions over palette rotations
     Fade-To interpolated timing so endings match startings
   To create a spectrum analysis for use in creating the events:
     Use ffmpeg with a size of (song length * 10). ex 205 seconds * 10 = 2050x512 as below.
      ex. ffmpeg -i "game.m4a" -lavfi showspectrumpic=s=2050x512:color=4:scale=lin:stop=8000 gameLd.png

   Ideas:
    https://learn.sparkfun.com/tutorials/prototype-wearable-led-dance-harness/all
    https://learn.sparkfun.com/tutorials/motion-controlled-wearable-led-dance-harness
    https://learn.sparkfun.com/tutorials/hackers-in-residence---sound-and-motion-reactivity-for-wearables
   Radio: dw
    NRF24L01 https://www.instructables.com/Arduino-and-NRF24L01/
    RTF433 https://www.instructables.com/RF-315433-MHz-Transmitter-receiver-Module-and-Ardu/
   JY-MCU Bluetooth module communication example for Arduino.
    Connect RX_PIN to TX pin of the module,
    Connect TX_PIN to RX pin of the module.
   Set Bluetooth HC-05

   16k - For a bluetooth-enabled 300-addressableled-driving music-synchronized system

   //Accelerometer: https://electropeak.com/learn/interfacing-mma7361-accelerometer-module-with-arduino/
*/
#include "Fx.h"
#include "Track.h"
static FxState fxState = FxState_Default;
//static FxState fxState = FxState_PlayingTrack;
//static FxState fxState = FxState_TestPattern;

//////////////// FastLED Section ////////////////
#include <FastLED.h>
#define LED_PIN     3 // 3, 5 for some, should be 3 
#define NUM_LEDS    310
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
//////////////// FastLED Section ////////////////

//////////////// BlueTooth Section ////////////////
#include <SoftwareSerial.h>
const PROGMEM int RX_PIN = 5;
const PROGMEM int TX_PIN = 6;
const PROGMEM unsigned long BLUETOOTH_BAUD_RATE = 38400;
SoftwareSerial bluetooth(RX_PIN, TX_PIN);
//////////////// BlueTooth Section ////////////////

static signed long timeOffset = 0;
static unsigned long lastMatchedTimecode = 0;
static unsigned long lastTimeLed = 0;
static unsigned long GetTime() {
  return (unsigned long)((signed long)millis() - (signed long)timeOffset);
}

void Print(String str)
{
  Serial.print(str);
  bluetooth.print(str);
}

void Println(String str)
{
  Serial.println(str);
  bluetooth.println(str);
}

void trackStart()
{
  CRGB dk(0, 0, 0);
  fxState = FxState_PlayingTrack;
  fxController.currentPalette = CRGBPalette16(dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk);
  fxController.initialPalette = CRGBPalette16(dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk, dk);
  fxController.paletteSpeed = 0;
  fxController.paletteDirection = 1;
  fxController.transitionType = Transition_Instant;
  lastMatchedTimecode = 0;
  fxController.transitionMux = 0;
  timeOffset = (unsigned long)(millis() - (signed long)TRACK_START_DELAY);

  Print(F("Playing Track"));
  Print(F(", Time Offset = "));
  Println(String(timeOffset));
}

void trackStop()
{
  fxState = FxState_Default;
  fxController.animatePalette = false;
  Print(F("Stopping Track"));
}

void FastLED_FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( fxController.currentPalette, colorIndex, brightness, LINEARBLEND);
    colorIndex += 3;
  }
}

void FastLED_SetPalette()
{
  if (fxController.animatePalette)
    fxController.paletteIndex = fxController.paletteIndex + (fxController.paletteSpeed * fxController.paletteDirection);
  FastLED_FillLEDsFromPaletteColors(fxController.paletteIndex);
  FastLED.show();
}

void setup() {
  Serial.begin(9600); //serial communication at 9600 bauds
  delay( 3000 ); // power-up safety delay
  Serial.println(F("Startup Ok"));
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  FastLED_SetPalette();

  bluetooth.begin(BLUETOOTH_BAUD_RATE);
  Print(F("BT:"));
  Println(String(BLUETOOTH_BAUD_RATE));

  if (fxState == FxState_PlayingTrack)
    trackStart();
  else Println(F("Ready"));

  if (fxState == FxState_TestPattern)
  {
    Println(F("TestMode"));
    FxEventProcess(fx_palette_rgb);
    fxController.paletteDirection = 1;
    fxController.paletteSpeed = 3;
    fxController.animatePalette = true;
  }
}

void FxEventPoll(unsigned long timecode)
{
  int match = GetCurrentTimeCodeMatch(timecode);
  int nextmatch = GetNextTimeCodeMatch(match);
  unsigned long matchedTimecode = SongTrack_timecode(match);
  unsigned long nextMatchedTimecode = SongTrack_timecode(nextmatch);

  if (matchedTimecode > lastMatchedTimecode)
  {
    if (fxController.transitionType == Transition_TimedWipePos || fxController.transitionType == Transition_TimedWipeNeg)
    {
      fxController.currentPalette = fxController.nextPalette;
    }
    fxController.transitionType = Transition_Instant;
    fxController.animatePalette = true;

    FxTrackSay(timecode, matchedTimecode, nextMatchedTimecode);
    /*Print(String((float)matchedTimecode / (float)1000.0f));
    Print(F(" : next @ "));
    Println(String((float)nextMatchedTimecode / (float)1000.0f));*/

    for (int i = 0; i < numSongTracks; i++)
      if (SongTrack_timecode(i) == matchedTimecode)
        FxEventProcess(SongTrack_event(i));

    lastMatchedTimecode = timecode;
  }

  unsigned long totalSpan = nextMatchedTimecode - lastMatchedTimecode;
  fxController.transitionMux = ((float)timecode - (float)lastMatchedTimecode ) / (float)totalSpan;

  if (fxController.transitionType == Transition_TimedFade)
  {
    //Interpolate initial palette to next palette, based on transition (0 to 1)
    for (int i = 0; i < 16; i++)
    {
      CRGB rgb = LerpRGB(fxController.transitionMux,
                         fxController.initialPalette[i][0], fxController.initialPalette[i][1], fxController.initialPalette[i][2],
                         fxController.nextPalette[i][0], fxController.nextPalette[i][1], fxController.nextPalette[i][2]);
      fxController.currentPalette[i] = rgb;
    }
  }  
  if (fxController.transitionType == Transition_TimedWipePos)
  {
    float mux = (1-fxController.transitionMux);
    int limit = mux * 15;
    fxController.currentPalette = fxController.initialPalette;
    for (int i = 15; i >= limit; i--)
      fxController.currentPalette[i] = CRGB(fxController.nextPalette[i][0], fxController.nextPalette[i][1], fxController.nextPalette[i][2]);        
    fxController.paletteIndex = mux * NUM_LEDS;
  }
  if (fxController.transitionType == Transition_TimedWipeNeg)
  {
    float mux = fxController.transitionMux;
    int limit = mux * 15;
    fxController.currentPalette = fxController.nextPalette;    
    for (int i = 15; i >= limit; i--)
      fxController.currentPalette[i] = CRGB(fxController.initialPalette[i][0], fxController.initialPalette[i][1], fxController.initialPalette[i][2]);    
    fxController.paletteIndex = mux * NUM_LEDS;
  }
}

void DirectEvent(int event)
{
  fxState = FxState_Default;
  fxController.transitionType = Transition_Instant;
  if (event != fx_nothing)
    Println(FxEventName(event));
  FxEventProcess(event);
}

static void magicColors(int count, char *colors)
{
  CRGB palette[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int index = 0;
  for (int i=0;i<16;i++)
  {
    palette[i] = CRGB(ShortnameToCRGB(colors[index]));
    index++;
    if (index >= count) index = 0;  
  }
  CreatePaletteBands(
    palette[0],  palette[1],  palette[2],  palette[3], 
    palette[4],  palette[5],  palette[6],  palette[7], 
    palette[8],  palette[9],  palette[10], palette[11], 
    palette[12], palette[13], palette[14], palette[15]);
  
  //animatePalette = false; 
  DirectEvent(fx_nothing);
  FastLED_SetPalette(); 
}

enum CaptureTextMode
{
  CaptureNone,
  CaptureColorCode,
  CaptureTimeCode
};
static CaptureTextMode captureMode = CaptureNone;
static char colorDefinitionStack[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int colorDefinitionCount = 0;
static String capturedTimeCode = "";
static void processCapturedText()
{
  if (captureMode == CaptureColorCode)
  {  
    Print(F("ColorDef("));
    Print(String(colorDefinitionCount));
    Print(F(")"));
    for (int i = 0; i < colorDefinitionCount; i++)
    {
      Print(F(" "));
      Print(String((char)colorDefinitionStack[i]));
    }
    Println(F(""));
    
    magicColors(colorDefinitionCount, &colorDefinitionStack[0]);
    colorDefinitionCount = 0;
    captureMode = CaptureNone;
  }
  else if (captureMode == CaptureTimeCode)
  { 
    captureMode = CaptureNone;
     
    unsigned long tc = capturedTimeCode.toInt()*100;

    /*timeOffset = millis();
    int match = GetCurrentTimeCodeMatch(tc);
    int nextmatch = GetNextTimeCodeMatch(match);
    timeOffset -= tc;*/

/*    Print(F("TC:"));
    Print(String(tc));
    Print(F(" vs t="));
    Print(String(GetTime()));
    Print(F(", to="));
    Print(String(timeOffset));
*/
  /*  Print(F(", to+tc="));
    Print(String(timeOffset ));
    Print(F(", "));
*/
  /*  Print(F(" Match:"));
    Print(String(match));
    Print(F(","));
    Print(String(nextmatch));
    Print(F(", now t="));
    Print(String(GetTime()));
    Println(F(""));
*/
    
  }

}

static void processInput(int data)
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
      //Println(F("Capturing ColorCode"));
      captureMode = CaptureColorCode;
      break;
    case '@':
      //Println(F("Capturing TimeCode"));
      capturedTimeCode = "";
      captureMode = CaptureTimeCode;
      break;
    case '?':
      Println(F("? : Help Menu"));
      Println(F("+ : Rotate Pos"));
      Println(F("- : Rotate Neg"));
      Println(F("d : Track Start"));
      Println(F("s : Track Stop"));
      Println(F("0-9 : Color"));
      Println(F("!code : Color code"));
      Println(F("(q)lava (w)cloud (e)ocean (r)forest (t)rainbow (y)rainbowstripe (u)party (i)heat"));
      break;

    case ')': trackStart(); break;
    case '(': trackStop(); break;

    case '0': fxController.animatePalette = false; DirectEvent(fx_palette_dark); FastLED_SetPalette(); break;
    case '1': fxController.animatePalette = false; DirectEvent(fx_palette_white); FastLED_SetPalette(); break;
    case '2': fxController.animatePalette = false; DirectEvent(fx_palette_red); FastLED_SetPalette(); break;
    case '3': fxController.animatePalette = false; DirectEvent(fx_palette_yellow); FastLED_SetPalette(); break;
    case '4': fxController.animatePalette = false; DirectEvent(fx_palette_green); FastLED_SetPalette(); break;
    case '5': fxController.animatePalette = false; DirectEvent(fx_palette_cyan); FastLED_SetPalette(); break;
    case '6': fxController.animatePalette = false; DirectEvent(fx_palette_blue); FastLED_SetPalette(); break;
    case '7': fxController.animatePalette = false; DirectEvent(fx_palette_magenta); FastLED_SetPalette(); break;
    case '8': fxController.animatePalette = false; DirectEvent(fx_palette_orange); FastLED_SetPalette(); break;
    case '9': fxController.animatePalette = false; DirectEvent(fx_palette_rgb); FastLED_SetPalette(); break;

    case 'q': DirectEvent(fx_palette_lava); FastLED_SetPalette(); break;
    case 'w': DirectEvent(fx_palette_cloud); FastLED_SetPalette(); break;
    case 'e': DirectEvent(fx_palette_ocean); FastLED_SetPalette(); break;
    case 'r': DirectEvent(fx_palette_forest); FastLED_SetPalette(); break;
    case 't': DirectEvent(fx_palette_rainbow); FastLED_SetPalette(); break;
    case 'y': DirectEvent(fx_palette_rainbowstripe); FastLED_SetPalette(); break;
    case 'u': DirectEvent(fx_palette_party); FastLED_SetPalette(); break;
    case 'i': DirectEvent(fx_palette_heat); FastLED_SetPalette(); break;

    case '_': fxController.animatePalette = true; DirectEvent(fx_speed_neg); break;
    case '+': fxController.animatePalette = true; DirectEvent(fx_speed_pos); break;
    case '-': fxController.animatePalette = true; DirectEvent(fx_speed_dec); break;
    case '=': fxController.animatePalette = true; DirectEvent(fx_speed_inc); break;
    case '~': fxController.animatePalette = true; DirectEvent(fx_speed_0); break;
    
    case 10:
    case 13:
      if (captureMode != CaptureNone)
        processCapturedText();
    case 0:
    case 225: break;
    default:
      Print(F("unk:"));
      Println(String(data));
      break;
  }
}


void loop()
{
/*
    Print(String(GetTime()));
    Print(F(" : "));
    Print(String(timeOffset));
    Println(F(""));
    //delay(500);
  */
  while (Serial.available())
    processInput(Serial.read());
  while (bluetooth.available())
    processInput(bluetooth.read());

  if (fxState == FxState_PlayingTrack)
    FxEventPoll(GetTime());

  if (fxState == FxState_PlayingTrack || fxController.animatePalette)
  {
    unsigned long t =  millis();
    if (t - lastTimeLed > 45)//delay to let bluetooth get data
    {
      FastLED_SetPalette();
      lastTimeLed = t;
    }
  }
}
