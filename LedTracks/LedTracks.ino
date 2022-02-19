// LightDrive : A time-track event system for Addressable LED
// Purpose is for a wearable dance-synchronized lightsuit.
#include "Config.h"
#include "Timecode.h"
#include "Fx.h"
#include "Track.h"
#include "Commands.h"
#include "Status.h"

static FxController fxController;

unsigned long GetTime() { return (unsigned long)((signed long)millis() - (signed long)getTimecodeTimeOffset() + getTimecodeSongOffset()); }

void setup() {
  fxController.fxState = FxState_Default;//TestPattern;//PlayingTrack;
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print(F("Serial init: "));
  Serial.println(SERIAL_BAUD_RATE);

#if SYSTEM_NANO_33_BLE
  Serial.println(F("System: Arduino Nano 33 BLE"));
#endif
#if SYSTEM_NANO
  Serial.println(F("System: Arduino Nano"));
#endif

#if ENABLE_MEMORYUSAGE
  Serial.println(F("MemoryUsage"));
  MEMORY_PRINT_STACKSIZE
  MEMORY_PRINT_HEAPSIZE
#endif  

#if ENABLE_NEOPIXEL
  Serial.println(F("Delaying 3 seconds for LEDs."));
  delay( 3000 ); // power-up safety delay
  neopixelSetup();
  PaletteGradient(fxController.palette);
  Serial.print(F("NeoPixel init: "));
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
  Serial.print(F("BT init: "));
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

  if (fxController.fxState == FxState_TestPattern)
  {
    Serial.println("Setting test pattern.");
    FxEventProcess(fxController, fx_palette_drb);
    fxController.paletteDirection = 1;
    fxController.paletteSpeed = 1;
    fxController.updatePalette = true;
  }

  if (fxController.fxState == FxState_PlayingTrack)
    trackStart(fxController, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), fxController.trackEndAction);
  else Serial.println(F("Ready"));

  Serial.println("Setup complete.");
}

void UpdatePalette()
{
  if (fxController.updatePalette)
  {
    fxController.paletteIndex = fxController.paletteIndex + (fxController.paletteSpeed * fxController.paletteDirection);
    if (fxController.paletteIndex >= NUM_LEDS)
      fxController.paletteIndex -= NUM_LEDS;
    if (fxController.paletteIndex < 0)
      fxController.paletteIndex = NUM_LEDS - 1;
  }
#if ENABLE_NEOPIXEL
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
    fxController.updatePalette = true;

    FxTrackSay(timecode, matchedTimecode, nextMatchedTimecode);
    /*Serial.print(((float)matchedTimecode / (float)1000.0f);
      Serial.print(F(" : next @ "));
      Serial.println((float)nextMatchedTimecode / (float)1000.0f);*/

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
      //PrintLogln(F("IMUMode"));
      //FxEventProcess(fx_palette_drb);
      //FxEventProcess(fx_palette_accel);
      //byte r = (float)((float)127.0f-(float)imuGyroX*120.0f);
      //byte g = (float)((float)127.0f-(float)imuGyroY*120.0f);
      //byte b = (float)((float)127.0f-(float)imuGyroZ*120.0f);

      byte r = 0;//(float)((float)127.0f-(float)imuGyroX*1.0f);
      byte g = (float)((float)127.0f-(float)getGyroY()*1.0f);
      byte b = (float)((float)127.0f-(float)getGyroZ()*1.0f);

      fxc.palette[0] = LEDRGB(r,g,b);
      rotPalette(fxc.palette);
      fxc.paletteDirection = 0;
      fxc.paletteSpeed = 0;
      fxc.updatePalette = true;
#endif
  }
  if (fxc.fxState == FxState_TestPattern)
  {
    FxEventProcess(fxc, fx_palette_drb);
    fxc.paletteDirection = 2;
    fxc.paletteSpeed = 2;
    fxc.updatePalette = true;
  }

  if (fxc.fxState == FxState_PlayingTrack)
    FxEventPoll(GetTime());
}






static unsigned long lastTimeLed = 0;
void loop()
{
  while (Serial.available())  
    UserCommandInput(fxController, Serial.read());
#if BLUETOOTH_ENABLE
  while (bluetooth.available())
    UserCommandInput(fxController, bluetooth.read());
#endif

#if ENABLE_BLE
  bleloop();
#endif

#if ENABLE_IMU
  imuPoll();
#endif
  
  StatePoll(fxController);

  if (fxController.fxState == FxState_PlayingTrack || fxController.updatePalette)
  {
    unsigned long t =  millis();
    if (t - lastTimeLed > 45)//delay to let bluetooth get data(fastled issue)
    {
      UpdatePalette();
      lastTimeLed = t;
    }
  }

#if ENABLE_STATUS
  FxDisplayStatus(fxController);
#endif
}
