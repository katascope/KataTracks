// LightDrive : A time-track event system for Addressable LED
// Purpose is for a wearable dance-synchronized lightsuit.
#include "Config.h"
#include "Fx.h"
#include "Track.h"
#include "Cmd.h"
#include "State.h"
#include "Devices.h"

namespace KataFxLed
{
  
}
//FXLED and MicroPalette

static FxController fxController;
static unsigned long lastTimeLedUpdate = 0;

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
#if ENABLE_NEOPIXEL &&  ENABLE_BRIGHTNESS
    fxController.brightness = 50;
    neopixelSetBrightness(fxController.brightness);    
#endif
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

void loop()
{
  while (Serial.available())  
    UserCommandInput(fxController, Serial.read());

#if ENABLE_BLUETOOTH
  bluetoothPoll(fxController);
#endif

#if ENABLE_BLE
  blePoll(fxController);
#endif

#if ENABLE_IMU
  imuPoll();  
#endif

  State_Poll(fxController);

  if (fxController.fxState == FxState_PlayingTrack || fxController.updatePalette)
  {
    unsigned long t =  millis();
    if (t - lastTimeLedUpdate > 45)//delay to let bluetooth get data(fastled issue)
    {
      UpdatePalette();
      lastTimeLedUpdate = t;
    }
  }

#if ENABLE_STATUS
  FxDisplayStatus(fxController);
#endif
}
