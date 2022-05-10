#ifndef CONFIG_DEF
#define CONFIG_DEF

static const char *DeviceName = "LightSuitPwr";

#define NUM_LEDS            70
#define NUM_STRIPS          8
#define LED_PIN             3
#define BRIGHTNESS_LIMIT    127 //Maximum allowed brightness
#define SERIAL_BAUD_RATE    9600

#if ARDUINO_AVR_NANO
 #define SYSTEM_NANO         1
#else
 #define SYSTEM_NANO_33_IOT  1
// #define SYSTEM_NANO_33_BLE  1
#endif

#ifdef SYSTEM_NANO
#define ENABLE_NEOPIXEL     1 //Enable Neopixel led library
#define ENABLE_BLE          0 //Enable Bluetooth Low-Energy
#define ENABLE_MULTISTRIP   0 //Enable multiple LED strips
#endif

#ifdef SYSTEM_NANO_33_BLE
#define ENABLE_NEOPIXEL     1
#define ENABLE_BLE          1
#define ENABLE_MULTISTRIP   1 //Enable multiple LED strips
#endif

#ifdef SYSTEM_NANO_33_IOT
#define ENABLE_NEOPIXEL     1
#define ENABLE_BLE          1
#define ENABLE_MULTISTRIP   1 //Enable multiple LED strips
#endif

#if ENABLE_MEMORYUSAGE
#include <MemoryUsage.h>
#endif

#endif
