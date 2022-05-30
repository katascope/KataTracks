#ifndef DEVICES_DEF
#define DEVIES_DEF

//////////////// NeoPixel Section ////////////////
#if ENABLE_NEOPIXEL
#include <Adafruit_NeoPixel.h>
void neopixelSetup();
void neopixelSetBrightness(int strip, unsigned char brightness);
void neopixelSetPalette(int slot, int numleds , uint32_t *palette, int paletteIndex);
void neopixelSetPixel(int slot, int offset, uint32_t rgb);
#endif
//////////////// NeoPixel Section ////////////////

#if ENABLE_BLE
#include "Fx.h"
// BLE UUIDs
#define BLE_UUID_LIGHTSUIT_SERVICE                      "02FE4875-5056-48B5-AD15-36E30665D9B4"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_AUTHENTICATE  "4C75BB42-5365-458D-A3EA-2B91339646B7"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_STATUS        "D01C9106-91BD-4998-9554-85264D33ACB2"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COMMAND       "220154BF-1DCE-4F03-85F0-7BA905D2D6B0"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_PLAY          "3B140EF5-0A72-4891-AD38-83B5A2595622"

// BLE Functions
bool bleSetup();
void blePoll(FxController &fxc);
#endif

#endif
