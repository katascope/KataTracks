// lol copyrights
// LightDrive : A time-track event system for Addressable LED
// Purpose is for a wearable dance-synchronized lightsuit.
#include "Config.h"
#include "Timecode.h"
#include "Fx.h"
#include "Track.h"
#include "Commands.h"
static FxController fxController;

void setup() {
  fxController.fxState = FxState_TestPattern;
//static FxState fxState = FxState_Default;
//static FxState fxState = FxState_PlayingTrack;
  Serial.begin(9600); //serial communication at 9600 bauds
  Serial.println(F("Serial Ok"));
  delay( 3000 ); // power-up safety delay
  Serial.println(F("3-second delay done."));

#if ENABLE_NEOPIXEL  
  neopixelSetup();
  PaletteGradient(fxController.palette);  
#endif  

#if ENABLE_BLE
  bleSetup();
#endif

#if ENABLE_BLUETOOTH
  bluetooth.begin(BLUETOOTH_BAUD_RATE);
  PrintLog(F("BT:"));
  PrintLogln(String(BLUETOOTH_BAUD_RATE));
#endif

#if ENABLE_IMU
  imuSetup();
#endif  

  if (fxController.fxState == FxState_PlayingTrack)
    trackStart(fxController, 0);
  else PrintLogln(F("Ready"));

  if (fxController.fxState == FxState_TestPattern)
  {
    PrintLogln(F("TestMode"));
    FxEventProcess(fxController,fx_palette_drb);
    fxController.paletteDirection = 1;
    fxController.paletteSpeed = 1;
    fxController.animatePalette = true;
  }
}

void SetPalette()
{
  if (fxController.animatePalette)
  {
    fxController.paletteIndex = fxController.paletteIndex + (fxController.paletteSpeed * fxController.paletteDirection);
    if (fxController.paletteIndex >= NUM_LEDS)
      fxController.paletteIndex -= NUM_LEDS;
    if (fxController.paletteIndex < 0)
      fxController.paletteIndex = NUM_LEDS-1;
  }
  
#if ENABLE_NEOPIXEL  
  neopixelSetPalette(fxController);
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
    float mux = (1-fxController.transitionMux);
    int limit = mux * (NUM_LEDS-1);
    CopyPalette(fxController.palette,fxController.initialPalette);    
    for (int i = NUM_LEDS-1; i >= limit; i--)
      fxController.palette[i] =fxController.nextPalette[i];
    fxController.paletteIndex = mux * NUM_LEDS;
  }
  if (fxController.transitionType == Transition_TimedWipeNeg)
  {
    float mux = fxController.transitionMux;
    int limit = mux * (NUM_LEDS-1);
    CopyPalette(fxController.palette,fxController.initialPalette);    
    for (int i = NUM_LEDS; i >= limit; i--)
      fxController.palette[i] =fxController.nextPalette[i];
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
    FxEventProcess(fxc,fx_palette_drb);
    fxc.paletteDirection = 2;
    fxc.paletteSpeed = 2;
    fxc.animatePalette = true;
  }
      
  if (fxc.fxState == FxState_PlayingTrack)
    FxEventPoll(GetTime());  
}

static unsigned long lastTimeLed = 0;
void loop()
{
/*
    PrintLog(String(GetTime()));
    PrintLog(F(" : "));
    PrintLog(String(timeOffset));
    PrintLogln(F(""));
    //delay(500);
  */
  while (Serial.available())
    UserCommandInput(fxController, Serial.read());
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
