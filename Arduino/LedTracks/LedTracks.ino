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
  for (int led=0;led<NUM_LEDS;led++)
   fxController.palette[led] = 0;
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

  fxController.fxState = FxState_Default;//FxState_Default;//FxState_TestPattern;//PlayingTrack;//

  if (fxController.fxState == FxState_TestPattern)
  { 
    Serial.println("Setting test pattern.");
    FxEventProcess(fxController, fx_palette_drb);
    fxController.paletteDirection = 1;
    fxController.paletteSpeed = 1;
#if ENABLE_NEOPIXEL &&  ENABLE_BRIGHTNESS
    fxController.brightness = 192;
    neopixelSetBrightness(fxController.brightness);    
#endif
    fxController.fxPaletteUpdateType = FxPaletteUpdateType::Always;
  }

  if (fxController.fxState == FxState_PlayingTrack)
  {
    fxController.fxTrackEndAction = FxTrackEndAction::LoopAtEnd;
    trackStart(fxController, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), fxController.fxTrackEndAction);
  }
  else Serial.println(F("Ready"));

  for (int i=0;i<NUM_STRIPS;i++)
  {
    Serial.print(F("Brightness "));
    Serial.print(i);
    Serial.print(F(" "));
    fxController.strip[i].brightness = 25;
    neopixelSetBrightness(i,fxController.strip[i].brightness);
    Serial.print(fxController.strip[i].brightness);
    Serial.println();
  }

  Serial.println("Setup complete.");
}

void UpdatePalette()
{
  if ((int)fxController.fxPaletteUpdateType != 0)
  {
    fxController.paletteIndex = fxController.paletteIndex + (fxController.paletteSpeed * fxController.paletteDirection);
    if (fxController.paletteIndex >= NUM_LEDS)
      fxController.paletteIndex -= NUM_LEDS;
    if (fxController.paletteIndex < 0)
      fxController.paletteIndex = NUM_LEDS - 1;
  }
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    //fix or remove this check later
    /if (fxController.stripMask & (1<<strip))
      neopixelSetPalette(strip, fxController.palette, fxController.paletteIndex);
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

  if (fxController.fxState == FxState_PlayingTrack 
    || fxController.fxPaletteUpdateType == FxPaletteUpdateType::Once
    || fxController.fxPaletteUpdateType == FxPaletteUpdateType::Always)
  {
    unsigned long t =  millis();
    int ledDelay = 30;
    if (t - fxController.lastTimeLedUpdate > ledDelay)//delay to let bluetooth get data(fastled issue)
    {
      UpdatePalette();
      fxController.lastTimeLedUpdate = t;
    }

    if (fxController.fxPaletteUpdateType == FxPaletteUpdateType::Once)
      fxController.fxPaletteUpdateType == FxPaletteUpdateType::Done;
  }

#if ENABLE_STATUS
    unsigned long t =  millis();
    if (t - lastTimeDisplay > 1000)//delay to let bluetooth get data
    {      
      FxDisplayStatus(fxController);      
      lastTimeDisplay = t;
    }
#endif
}
