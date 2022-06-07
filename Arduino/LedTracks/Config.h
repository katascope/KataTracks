#ifndef CONFIG_DEF
#define CONFIG_DEF

#define LEAD      1 //Generally LightSuit*A silver
#define FOLLOW    0 //Generally LightSuit*B gold
#define SUIT_JACKET    0

#if 1
static const char *DeviceName = "LightSuitAngelQ";
#elif LEAD
static const char *DeviceName = "LightSuitAngelA";
#elif FOLLOW
static const char *DeviceName = "LightSuitAngelB";
#endif

#define STARTUP_STATE       FxState_TestPattern    //FxState_Default;//FxState_TestPattern;//FxState_PlayingTrack;//
#define UPDATE_DELAY        30 //100 //Milliseconds to delay between palette updates, set to 100 for iot, 30 for ble
#define NUM_STRIPS          8
#define BRIGHTNESS          20 //50  //Default brightness
#define BRIGHTNESS_LIMIT    80 //Maximum allowed brightness, //90 possible but runs too hot
#define ENABLE_SAFETY       1

#if LEAD
#define NUM_LEDS_0          41
#define NUM_LEDS_1          41
#define NUM_LEDS_2          76 
#define NUM_LEDS_3          76
#define NUM_LEDS_4          48 //arms
#define NUM_LEDS_5          48
#define NUM_LEDS_6          61 //legs
#define NUM_LEDS_7          61
#endif

#if FOLLOW
#define NUM_LEDS_0          36
#define NUM_LEDS_1          36
#define NUM_LEDS_2          66 
#define NUM_LEDS_3          66
#define NUM_LEDS_4          40 //arms
#define NUM_LEDS_5          40
#define NUM_LEDS_6          53 //legs
#define NUM_LEDS_7          53
#endif

#if SUIT_JACKET
#define NUM_LEDS_0          46
#define NUM_LEDS_1          46
#define NUM_LEDS_2          36 
#define NUM_LEDS_3          36
#define NUM_LEDS_4          38 //arms
#define NUM_LEDS_5          38
#define NUM_LEDS_6          35 //legs
#define NUM_LEDS_7          35
#endif

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
