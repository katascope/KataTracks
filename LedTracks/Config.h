#if !defined CONFIG_DEF
#define CONFIG_DEF

/*
#if defined ARDUINO_AVR_NANO
 #define SYSTEM_NANO
#else
#endif
*/
//#define SYSTEM_NANO_33_BLE 1
#define SYSTEM_NANO 1

#ifdef SYSTEM_NANO
#define ENABLE_STATUS     1 //Periodically output heartbeat status to log
#define ENABLE_NEOPIXEL   1
#define ENABLE_BLUETOOTH  0
#define ENABLE_BLE        0
#define ENABLE_IMU        0
#endif

#ifdef SYSTEM_NANO_33_BLE
#define ENABLE_STATUS     1
#define ENABLE_NEOPIXEL   1
#define ENABLE_BLUETOOTH  0
#define ENABLE_BLE        1
#define ENABLE_IMU        1
#endif

#define SERIAL_BAUD_RATE  9600

#include "Palette.h"

//////////////// NeoPixel Section ////////////////
#if ENABLE_NEOPIXEL
#define LED_PIN    5 //3 most of the time, 5 on old things
#define NUM_LEDS   70
#include <Adafruit_NeoPixel.h>
#include "NeoPixel.h"
#endif
//////////////// NeoPixel Section ////////////////

 /////////////////// IMU Section ///////////////////
#if ENABLE_IMU
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
