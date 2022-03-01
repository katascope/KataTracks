#ifndef CONFIG_DEF
#define CONFIG_DEF

#define NUM_LEDS            70
#define LED_PIN             3
#define SERIAL_BAUD_RATE    9600
static const char *DeviceName = "LightSuitB";

#ifdef ARDUINO_AVR_UNO
 #define SYSTEM_UNO          1
#elif ARDUINO_AVR_NANO
 #define SYSTEM_NANO         1
#else
 #define SYSTEM_NANO_33_BLE  1
#endif

#ifdef SYSTEM_UNO
#define ENABLE_TEST_PATTERN 0 //Show a simple test pattern
#define ENABLE_TEST_TRACK   0 //Run test track
#define ENABLE_MEMORYUSAGE  1 //Do AVR-based memory check in beginning
#define ENABLE_BRIGHTNESS   1 //Allow adjustments to brightness - this can cause excess heat
#define ENABLE_STATUS       1 //Periodically output heartbeat status to log
#define ENABLE_NEOPIXEL     1 //Enable Neopixel led library
#define ENABLE_BLUETOOTH    1 //Enable classic bluetooth
#define ENABLE_BLE          0 //Enable Bluetooth Low-Energy
#define ENABLE_IMU          0 //Enable Inertial Motion Unit
#define ENABLE_MIC          0 //Enable Microphone
#endif

#ifdef SYSTEM_NANO
#define ENABLE_TEST_PATTERN 1 //Show a simple test pattern
#define ENABLE_TEST_TRACK   0 //Run test track
#define ENABLE_MEMORYUSAGE  0 //Do AVR-based memory check in beginning
#define ENABLE_BRIGHTNESS   1 //Allow adjustments to brightness - this can cause excess heat
#define ENABLE_STATUS       1 //Periodically output heartbeat status to log
#define ENABLE_NEOPIXEL     1 //Enable Neopixel led library
#define ENABLE_BLUETOOTH    1 //Enable classic bluetooth
#define ENABLE_BLE          0 //Enable Bluetooth Low-Energy
#define ENABLE_IMU          0 //Enable Inertial Motion Unit
#define ENABLE_MIC          0 //Enable Microphone
#endif

#ifdef SYSTEM_NANO_33_BLE
#define ENABLE_TEST_PATTERN 0
#define ENABLE_TEST_TRACK   0
#define ENABLE_MEMORYUSAGE  0
#define ENABLE_BRIGHTNESS   1
#define ENABLE_STATUS       1
#define ENABLE_NEOPIXEL     1
#define ENABLE_BLUETOOTH    0
#define ENABLE_BLE          1
#define ENABLE_IMU          1
#define ENABLE_MIC          0
#endif

#if ENABLE_MEMORYUSAGE
#include <MemoryUsage.h>
#endif

#endif
