#ifndef DEVICES_DEF
#define DEVIES_DEF

//hsv2rgb and rgb2hsv
void rgb2hsv(const unsigned char &src_r, const unsigned char &src_g, const unsigned char &src_b, unsigned char &dst_h, unsigned char &dst_s, unsigned char &dst_v);
void hsv2rgb(const unsigned char &src_h, const unsigned char &src_s, const unsigned char &src_v, unsigned char &dst_r, unsigned char &dst_g, unsigned char &dst_b);

//////////////// NeoPixel Section ////////////////
#if ENABLE_NEOPIXEL
#define LED_PIN    3 //3 most of the time, 5 on old things
#include <Adafruit_NeoPixel.h>
void neopixelSetup();
void neopixelSetBrightness(unsigned char brightness);
void neopixelSetPalette(uint32_t *palette, int paletteIndex);
#endif
//////////////// NeoPixel Section ////////////////



 /////////////////// IMU Section ///////////////////
#if ENABLE_IMU
struct IMUData
{
  float accelX = 0.0f;
  float accelY = 0.0f;
  float accelZ = 0.0f;
  float gyroX = 0.0f;
  float gyroY = 0.0f;
  float gyroZ = 0.0f;
};

void imuSetup();
void imuPoll();

float getAccelX();
float getAccelY();
float getAccelZ();

float getGyroX();
float getGyroY();
float getGyroZ();
#endif
/////////////////// IMU Section ///////////////////

#if ENABLE_BLE
#include "Fx.h"
// BLE UUIDs
#define BLE_UUID_LIGHTSUIT_SERVICE                      "02FE4875-5056-48B5-AD15-36E30665D9B4"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_AUTHENTICATE  "4C75BB42-5365-458D-A3EA-2B91339646B7"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TEST          "BEECBFDC-D6EB-42DC-827E-27D3DF924864"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TIMECODE      "10365297-362D-44FB-8807-A6AA13B1BD83"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_STATUS        "D01C9106-91BD-4998-9554-85264D33ACB2"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COMMAND       "220154BF-1DCE-4F03-85F0-7BA905D2D6B0"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_PLAY          "3B140EF5-0A72-4891-AD38-83B5A2595622"

#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_RSSI          "3640006A-FB78-4580-8A73-EFA9DA098263"

#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_X       "C3340E05-7DAE-4BEE-A913-B2631667BFD6"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Y       "C18AEDF7-CC1B-49D6-8D01-57D43950895E"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Z       "71DC8A5E-A5E2-45C4-BA3E-268ECD0B5DA5"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_X        "DEFFFE29-9813-4E0B-8B25-600CC1F4441D"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Y        "9BDD84C0-7865-42FA-99B3-A52E6E9A901A"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Z        "B53E6C07-73D1-4DE6-85F8-04CB9A1B773E"

#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER       "612DD356-9632-48CF-A279-935D3D4EF242"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER_RESET "EA7CE01E-808B-4EF3-8735-2A05F1C48DFF"

// BLE Functions
bool bleSetup();
void blePoll(FxController &fxc);
#endif

//////////////// Microphone Section ////////////////
#if ENABLE_MIC
#define MIC_PIN 0
class MicrophoneSampler
{
  private:
    static const int sampleWindow; // Sample window width in mS (50 mS = 20Hz)
    static float level;
  public:
    static double GetLevel();
    static void Poll();
};
#endif

#endif
