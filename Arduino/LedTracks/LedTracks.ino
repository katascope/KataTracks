// LightDrive : A time-track event system for Addressable LED
// Purpose is for a wearable dance-synchronized lightsuit.
#include "Config.h"
#include "Fx.h"
#include "Track.h"
#include "Cmd.h"
#include "State.h"
#include "Devices.h"
static FxController fxController;
static unsigned long lastTimeDisplay = 0;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print(DeviceName);
  Serial.print(F("Serial init: "));
  Serial.println(SERIAL_BAUD_RATE);
#if SYSTEM_NANO_33_BLE
  Serial.println(F("System: Arduino Nano 33 BLE"));
#elif SYSTEM_NANO_33_IOT
  Serial.println(F("System: Arduino Nano 33 IOT"));
#elif SYSTEM_UNO
  Serial.println(F("System: Arduino UNO"));
#elif SYSTEM_NANO
  Serial.println(F("System: Arduino Nano"));
#else
  Serial.println(F("System: UNKNOWN"));
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
  for (int strip=0;strip<NUM_STRIPS;strip++)
    for (int led=0;led<NUM_LEDS;led++)
      fxController.strip[strip].palette[led] = 0;
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

  fxController.fxState = FxState_PlayingTrack;//Default;//FxState_TestPattern;//PlayingTrack;//

  if (fxController.fxState == FxState_TestPattern)
  { 
    Serial.println("Setting test pattern.");
    FxEventProcess(fxController, fx_palette_drb);
#if ENABLE_NEOPIXEL &&  ENABLE_BRIGHTNESS
    fxController.brightness = 192;
    neopixelSetBrightness(fxController.brightness);    
#endif
  }

  if (fxController.fxState == FxState_PlayingTrack)
  {
    fxController.fxTrackEndAction = FxTrackEndAction::LoopAtEnd;
    trackStart(fxController, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), fxController.fxTrackEndAction);
  }
  else Serial.println(F("Ready"));

//Display brightness levels
  Serial.print(F("Brightness = { "));
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    fxController.strip[strip].brightness = 25;
    neopixelSetBrightness(strip,fxController.strip[strip].brightness);
    Serial.print(fxController.strip[strip].brightness);
    Serial.print(F(" "));
  }
  Serial.println(F(" }"));

  Serial.println("Setup complete.");
}

void UpdatePalette()
{
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if ((int)fxController.strip[strip].fxPaletteUpdateType != 0)
    {
      fxController.strip[strip].paletteIndex = fxController.strip[strip].paletteIndex + (fxController.strip[strip].paletteSpeed * fxController.strip[strip].paletteDirection);
      if (fxController.strip[strip].paletteIndex >= NUM_LEDS)
        fxController.strip[strip].paletteIndex -= NUM_LEDS;
      if (fxController.strip[strip].paletteIndex < 0)
        fxController.strip[strip].paletteIndex = NUM_LEDS - 1;
    }
    neopixelSetPalette(strip, fxController.strip[strip].palette, fxController.strip[strip].paletteIndex);
  }
}

void loop()
{
  while (Serial.available())  
    UserCommandInput(fxController, Serial.read());
 
#if ENABLE_BLE
  blePoll(fxController);
#endif

  State_Poll(fxController);

  bool needsUpdate = false;
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxController.strip[strip].fxPaletteUpdateType == FxPaletteUpdateType::Once
    || fxController.strip[strip].fxPaletteUpdateType == FxPaletteUpdateType::Always)
      needsUpdate = true;
  }
  
  if (fxController.fxState == FxState_PlayingTrack)// || needsUpdate)
  {
    unsigned long t =  millis();
    int ledDelay = 30;

#if SYSTEM_NANO_33_IOT
    ledDelay = 100;
#endif

    if (t - fxController.lastTimeLedUpdate > ledDelay)//delay to let bluetooth get data(fastled issue)
    {
      UpdatePalette();
      fxController.lastTimeLedUpdate = t;
      
      for (int strip=0;strip<NUM_STRIPS;strip++)
      {
        if (fxController.strip[strip].fxPaletteUpdateType == FxPaletteUpdateType::Once)
          fxController.strip[strip].fxPaletteUpdateType = FxPaletteUpdateType::Done;
      }
    }

  }


//Display status once a second
  unsigned long t =  millis();
  if (t - lastTimeDisplay > 1000)//delay to let bluetooth get data
  {      
    if (fxController.fxState != FxState_PlayingTrack)
      FxDisplayStatus(fxController);      
    lastTimeDisplay = t;
  }

}
