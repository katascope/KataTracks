#if !defined BLE_DEF
#define BLE_DEF
//#include <ArduinoBLE.h>

//----------------------------------------------------------------------------------------------------------------------
// BLE UUIDs
//----------------------------------------------------------------------------------------------------------------------

#define BLE_UUID_LIGHTSUIT_SERVICE                      "02FE4875-5056-48B5-AD15-36E30665D9B4"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TEST          "BEECBFDC-D6EB-42DC-827E-27D3DF924864"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TIMECODE      "10365297-362D-44FB-8807-A6AA13B1BD83"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_FXSTATE       "D01C9106-91BD-4998-9554-85264D33ACB2"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_PLAYSTATE     "220154BF-1DCE-4F03-85F0-7BA905D2D6B0"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_X       "C3340E05-7DAE-4BEE-A913-B2631667BFD6"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Y       "C18AEDF7-CC1B-49D6-8D01-57D43950895E"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Z       "71DC8A5E-A5E2-45C4-BA3E-268ECD0B5DA5"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_X        "DEFFFE29-9813-4E0B-8B25-600CC1F4441D"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Y        "9BDD84C0-7865-42FA-99B3-A52E6E9A901A"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Z        "B53E6C07-73D1-4DE6-85F8-04CB9A1B773E"

#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER       "612DD356-9632-48CF-A279-935D3D4EF242"
#define BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER_RESET "EA7CE01E-808B-4EF3-8735-2A05F1C48DFF"

//----------------------------------------------------------------------------------------------------------------------
// BLE
//----------------------------------------------------------------------------------------------------------------------

bool bleSetup();
void bleloop();

#endif