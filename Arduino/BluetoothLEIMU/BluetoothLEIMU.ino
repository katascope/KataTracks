/*
  This example creates a BLE peripheral with a service that contains a
  couple of characteristics to test BLE connection.
  The yellow LED shows the BLE module is initialized.
  The green LED shows RSSI of zero. The more it blinks the worse the connection.

  The circuit:
  - Arduino Nano 33 BLE Sense board.

  You can use a generic BLE central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

//#include "FX.h"
//#include "Track.h"

//static FxState fxState = FxState_TestPattern;

//////////////// FastLED Section ////////////////
//#include <FastLED.h>
//#include "FastLED-Master\src\FastLED.h"

/*#define LED_PIN     3 // 3, 5 for some, should be 3 
#define NUM_LEDS    310
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];*/
//////////////// FastLED Section ////////////////

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

BLEService lightsuitService( BLE_UUID_LIGHTSUIT_SERVICE );
BLEUnsignedLongCharacteristic testCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TEST, BLERead | BLENotify);
BLEUnsignedLongCharacteristic timecodeCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TIMECODE, BLERead | BLENotify );
BLEUnsignedLongCharacteristic fxStateCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_FXSTATE, BLEWrite | BLERead | BLENotify );
BLEUnsignedLongCharacteristic playStateCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_PLAYSTATE, BLEWrite | BLERead | BLENotify );

BLEFloatCharacteristic accelerationCharacteristicX( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_X, BLERead | BLENotify );
BLEFloatCharacteristic accelerationCharacteristicY( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Y, BLERead | BLENotify );
BLEFloatCharacteristic accelerationCharacteristicZ( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Z, BLERead | BLENotify );

BLEFloatCharacteristic gyroCharacteristicX( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_X, BLERead | BLENotify );
BLEFloatCharacteristic gyroCharacteristicY( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Y, BLERead | BLENotify );
BLEFloatCharacteristic gyroCharacteristicZ( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Z, BLERead | BLENotify );

BLEUnsignedLongCharacteristic counterCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER, BLERead | BLENotify );
BLEBoolCharacteristic resetCounterCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER_RESET, BLEWriteWithoutResponse );


const int BLE_LED_PIN = LED_BUILTIN;
const int RSSI_LED_PIN = LED_PWR;


void setup()
{
  Serial.begin( 9600 );
  //  while ( !Serial );

  pinMode( BLE_LED_PIN, OUTPUT );
  pinMode( RSSI_LED_PIN, OUTPUT );

  if ( !IMU.begin() )
  {
    Serial.println( "Failed to initialize IMU!" );
    while ( 1 );
  }
  Serial.print( "Accelerometer sample rate = " );
  Serial.print( IMU.accelerationSampleRate() );
  Serial.println( " Hz" );

  if( setupBleMode() )
  {
    digitalWrite( BLE_LED_PIN, HIGH );    
  }
} // setup

void loop()
{
  static unsigned long counter = 0;
  static long previousMillis = 0;

  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  //Serial.println("Waiting for connection.");

  if ( central )
  {
    Serial.println( "Connected to central: " );
    Serial.println( central.address() );

    while ( central.connected() )
    {
      if( resetCounterCharacteristic.written() )
      {
        counter = 0;
      }

      long interval = 20;
      unsigned long currentMillis = millis();
      timecodeCharacteristic.writeValue( currentMillis );
      
      if( currentMillis - previousMillis > interval )
      {
        previousMillis = currentMillis;

        //Serial.print( "Central RSSI: " );
       // Serial.println( central.rssi() );

        if( central.rssi() != 0 )
        {
          digitalWrite( RSSI_LED_PIN, LOW );
          float accelerationX, accelerationY, accelerationZ;
          if ( IMU.accelerationAvailable() )
          {
            IMU.readAcceleration( accelerationX, accelerationY, accelerationZ );
            Serial.print("Acc=");
            Serial.print(accelerationX);
            Serial.print('\t');
            Serial.print(accelerationY);
            Serial.print('\t');
            Serial.print(accelerationZ);
            accelerationCharacteristicX.writeValue( accelerationX );
            accelerationCharacteristicY.writeValue( accelerationY );
            accelerationCharacteristicZ.writeValue( accelerationZ );
          }

          float gyroX, gyroY, gyroZ;
          if ( IMU.gyroscopeAvailable() )
          {
            IMU.readGyroscope( gyroX, gyroY, gyroZ );
            Serial.print("Gyro=");
            Serial.print(gyroX);
            Serial.print('\t');
            Serial.print(gyroY);
            Serial.print('\t');
            Serial.print(gyroZ);
            gyroCharacteristicX.writeValue( gyroX );
            gyroCharacteristicY.writeValue( gyroY);
            gyroCharacteristicZ.writeValue( gyroZ );
          }

          counter++;
          Serial.print("Count=");
          Serial.println(counter);
          counterCharacteristic.writeValue( counter );
        }
        else
        {
          digitalWrite( RSSI_LED_PIN, HIGH );
        }
      } // intervall
      testCharacteristic.writeValue(0x12345678);

    } // while connected

    Serial.print( F( "Disconnected from central: " ) );
    Serial.println( central.address() );
  } // if central
} // loop

void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

byte buf[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };  

bool setupBleMode()
{
  if ( !BLE.begin() )
  {
    return false;
  }

  // set advertised local name and service UUID:
  BLE.setDeviceName( "LightSuitA" );
  BLE.setLocalName( "LightSuitA" );
  BLE.setAdvertisedService( lightsuitService );

  // BLE add characteristics
  lightsuitService.addCharacteristic( testCharacteristic );
  lightsuitService.addCharacteristic( timecodeCharacteristic );
  lightsuitService.addCharacteristic( accelerationCharacteristicX );
  lightsuitService.addCharacteristic( accelerationCharacteristicY );
  lightsuitService.addCharacteristic( accelerationCharacteristicZ );
  lightsuitService.addCharacteristic( gyroCharacteristicX );
  lightsuitService.addCharacteristic( gyroCharacteristicY );
  lightsuitService.addCharacteristic( gyroCharacteristicZ );
  lightsuitService.addCharacteristic( counterCharacteristic );
  lightsuitService.addCharacteristic( resetCounterCharacteristic );

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  
  // add service
  BLE.addService( lightsuitService );

  // set the initial value for the characeristics:
  testCharacteristic.writeValue(0x12345678);
  
  accelerationCharacteristicX.writeValue( 0.0 );
  accelerationCharacteristicY.writeValue( 0.0 );
  accelerationCharacteristicZ.writeValue( 0.0 );
  gyroCharacteristicX.writeValue( 0.0 );
  gyroCharacteristicY.writeValue( 0.0 );
  gyroCharacteristicZ.writeValue( 0.0 );
  counterCharacteristic.writeValue( 0 );
  // start advertising
  BLE.advertise();

  return true;
}
