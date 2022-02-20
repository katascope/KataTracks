#ifndef CONFIG_DEF
#define CONFIG_DEF

#define NUM_LEDS   50
static const char *DeviceName = "LightSuitA";

#ifdef ARDUINO_AVR_NANO
 #define SYSTEM_NANO         1
#else
 #define SYSTEM_NANO_33_BLE  1
#endif

#ifdef SYSTEM_NANO
#define ENABLE_MEMORYUSAGE  1 //Do AVR-based memory check in beginning
#define ENABLE_BRIGHTNESS   1 //Allow adjustments to brightness - this can cause excess heat
#define ENABLE_STATUS       1 //Periodically output heartbeat status to log
#define ENABLE_NEOPIXEL     1 //Enable Neopixel led library
#define ENABLE_BLUETOOTH    1 //Enable classic bluetooth
#define ENABLE_BLE          0 //Enable Bluetooth Low-Energy
#define ENABLE_IMU          0 //Enable Inertial Motion Unit
#endif

#ifdef SYSTEM_NANO_33_BLE
#define ENABLE_MEMORYUSAGE  0
#define ENABLE_BRIGHTNESS   0
#define ENABLE_STATUS       1
#define ENABLE_NEOPIXEL     1
#define ENABLE_BLUETOOTH    0
#define ENABLE_BLE          1
#define ENABLE_IMU          1
#endif

#define SERIAL_BAUD_RATE  9600

#include "Palette.h"

#if ENABLE_MEMORYUSAGE
#include <MemoryUsage.h>
#endif

#if ENABLE_STATUS
#include "Status.h"
#endif

//////////////// NeoPixel Section ////////////////
#if ENABLE_NEOPIXEL
#define LED_PIN    3 //3 most of the time, 5 on old things
#include "NeoPixel.h"
#include <Adafruit_NeoPixel.h>
#endif
//////////////// NeoPixel Section ////////////////

 /////////////////// IMU Section ///////////////////
#if ENABLE_IMU
#include <Arduino_LSM9DS1.h>
#include "IMU.h"
#endif

//////////////// BlueTooth Section ////////////////
#if ENABLE_BLUETOOTH
#include <SoftwareSerial.h>
const PROGMEM int RX_PIN = 5;
const PROGMEM int TX_PIN = 6;
const PROGMEM unsigned long BLUETOOTH_BAUD_RATE = 9600;
static SoftwareSerial bluetooth(RX_PIN, TX_PIN);
#endif

//////////////// BluetoothLowEnergy ////////////////
#if ENABLE_BLE
#include "BLE.h"
#endif


#endif
