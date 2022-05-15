#ifndef CONFIG_DEF
#define CONFIG_DEF

static const char *DeviceName = "LightSuitAngelA";

#define STARTUP_STATE       FxState_Default    //FxState_Default;//FxState_TestPattern;//FxState_PlayingTrack;//
#define UPDATE_DELAY        30 //100 //Milliseconds to delay between palette updates, set to 100 for iot, 30 for ble
#define NUM_STRIPS          8
#define BRIGHTNESS          75  //Default brightness
#define BRIGHTNESS_LIMIT    75 //Maximum allowed brightness
#define ENABLE_SAFETY       1
#define NUM_LEDS            80
#define ENABLE_MULTISTRIP   1   //Enable multiple LED strips
#define LED_PIN             3
#define ENABLE_NEOPIXEL     1
#define ENABLE_BLE          1
#define DEBUG_BLE           0
#define SERIAL_BAUD_RATE    9600

#if ENABLE_MEMORYUSAGE
#include <MemoryUsage.h>
#endif
#endif
