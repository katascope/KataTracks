#ifndef CONFIG_DEF
#define CONFIG_DEF

static const char *DeviceName = "LightSuitE";

#define STARTUP_STATE       FxState_Default    //FxState_Default;//FxState_TestPattern;//FxState_PlayingTracklayingTrack;//
#define BRIGHTNESS          30  //Default brightness
#define BRIGHTNESS_LIMIT    127 //Maximum allowed brightness
#define NUM_LEDS            80
#define NUM_STRIPS          8
#define ENABLE_MULTISTRIP   1   //Enable multiple LED strips
#define LED_PIN             3
#define SERIAL_BAUD_RATE    9600
#define ENABLE_NEOPIXEL     1

#if ARDUINO_AVR_NANO
 #define SYSTEM_NANO         1
#else
//#define SYSTEM_NANO_33_IOT  1
 #define SYSTEM_NANO_33_BLE  1
#endif

#define DEBUG_BLE           0

#if ENABLE_MEMORYUSAGE
#include <MemoryUsage.h>
#endif
#endif
