#ifndef CONFIG_DEF
#define CONFIG_DEF

static const char *DeviceName = "LightSuitAngelB";

#define STARTUP_STATE       FxState_TestPattern    //FxState_Default;//FxState_TestPattern;//FxState_PlayingTrack;//
#define UPDATE_DELAY        30 //100 //Milliseconds to delay between palette updates, set to 100 for iot, 30 for ble
#define NUM_STRIPS          8
#define BRIGHTNESS          50  //Default brightness
#define BRIGHTNESS_LIMIT    80 //Maximum allowed brightness, //90 possible but runs too hot
#define ENABLE_SAFETY       1

//Relatively fixed
#define NUM_LEDS            80
#define ENABLE_MULTISTRIP   1   //Enable multiple LED strips
#define LED_PIN             3
#define ENABLE_NEOPIXEL     1
#define ENABLE_BLE          1
#define DEBUG_BLE           1
#define SERIAL_BAUD_RATE    9600

#if defined(ARDUINO_AVR_NANO)
#undef STARTUP_STATE
#define STARTUP_STATE       FxState_TestPattern
#undef NUM_LEDS
#define NUM_LEDS            10
#undef ENABLE_BLE
#define ENABLE_BLE          0
#undef NUM_STRIPS
#define NUM_STRIPS          4

#endif

#if ENABLE_MEMORYUSAGE
#include <MemoryUsage.h>
#endif
#endif
