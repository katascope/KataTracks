#include "Config.h"
#if ENABLE_BLE
#include "BLE.h"
#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
#include "Fx.h"
#include "IMU.h"
#include "Commands.h"
#include "Timecode.h"
#include "Track.h"

const int BLE_LED_PIN = LED_BUILTIN;
const int RSSI_LED_PIN = LED_PWR;

BLEService lightsuitService( BLE_UUID_LIGHTSUIT_SERVICE );
BLEUnsignedLongCharacteristic authenticateCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_AUTHENTICATE, BLEWrite);
BLEUnsignedLongCharacteristic testCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TEST, BLERead | BLENotify);
BLEUnsignedLongCharacteristic timecodeCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TIMECODE, BLERead | BLENotify );
BLEUnsignedLongCharacteristic statusCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_STATUS, BLEWrite | BLERead | BLENotify );
BLECharCharacteristic commandCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COMMAND, BLERead | BLEWrite  );
BLEUnsignedLongCharacteristic playCharacteristic(BLE_UUID_LIGHTSUIT_CHARACTERISTIC_PLAY, BLERead | BLEWrite  );

BLEFloatCharacteristic accelerationCharacteristicX( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_X, BLERead | BLENotify );
BLEFloatCharacteristic accelerationCharacteristicY( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Y, BLERead | BLENotify );
BLEFloatCharacteristic accelerationCharacteristicZ( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_ACCEL_Z, BLERead | BLENotify );

BLEFloatCharacteristic gyroCharacteristicX( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_X, BLERead | BLENotify );
BLEFloatCharacteristic gyroCharacteristicY( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Y, BLERead | BLENotify );
BLEFloatCharacteristic gyroCharacteristicZ( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_GYRO_Z, BLERead | BLENotify );

BLEUnsignedLongCharacteristic counterCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER, BLERead | BLENotify );
BLEBoolCharacteristic resetCounterCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COUNTER_RESET, BLEWriteWithoutResponse );

void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  Serial.print(F("Connected event, central: "));
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print(F("Disconnected event, central: "));
  Serial.println(central.address());
}

/*void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
    // central wrote new value to characteristic, update LED
    Serial.print("Characteristic event, written: ");

    switch (switchCharacteristic.value())
    {
    case 'a':
        colorWipe(strip.Color(255, 0, 0), 20); // Red
        break;
    case 'b':
        colorWipe(strip.Color(0, 255, 0), 20); // Green
        break;
    case 'c':
        colorWipe(strip.Color(0, 0, 255), 20); // Blue
        break;
    case 'd':
        theaterChase(strip.Color(255, 0, 0), 20); // Red
        break;
    case 'e':
        theaterChase(strip.Color(0, 255, 0), 20); // Green
        break;
    case 'f':
        theaterChase(strip.Color(255, 0, 255), 20); // Cyan
        break;
    case 'g':
        rainbow(10);
        break;
    case 'h':
        theaterChaseRainbow(20);
        break;
    }
}
*/
bool bleSetup()
{
  pinMode( BLE_LED_PIN, OUTPUT );
  pinMode( RSSI_LED_PIN, OUTPUT );
  
  if ( !BLE.begin() )
  {
    return false;
  }

  // set advertised local name and service UUID:
  BLE.setDeviceName( DeviceName );
  BLE.setLocalName( DeviceName );
  BLE.setAdvertisedService( lightsuitService );

  // BLE add characteristics
  //lightsuitService.addCharacteristic( testCharacteristic );
  lightsuitService.addCharacteristic( authenticateCharacteristic );
  lightsuitService.addCharacteristic( timecodeCharacteristic );
  lightsuitService.addCharacteristic( statusCharacteristic );
  lightsuitService.addCharacteristic( commandCharacteristic );
  lightsuitService.addCharacteristic( playCharacteristic );
  /*lightsuitService.addCharacteristic( accelerationCharacteristicX );
  lightsuitService.addCharacteristic( accelerationCharacteristicY );
  lightsuitService.addCharacteristic( accelerationCharacteristicZ );
  lightsuitService.addCharacteristic( gyroCharacteristicX );
  lightsuitService.addCharacteristic( gyroCharacteristicY );
  lightsuitService.addCharacteristic( gyroCharacteristicZ );*/
  lightsuitService.addCharacteristic( counterCharacteristic );
  lightsuitService.addCharacteristic( resetCounterCharacteristic );

//  playCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);
 
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
  commandCharacteristic.writeValue( 0 );
  playCharacteristic.writeValue(0);
  statusCharacteristic.writeValue(0);
  // start advertising
  BLE.advertise();

  digitalWrite( BLE_LED_PIN, HIGH );    
  return true;
}

void bleloop(FxController &fxc)
{
  static unsigned long counter = 0;
  static long previousMillis = 0;

  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  //Serial.println(F("Waiting for connection."));

  if ( central )
  {
    Serial.println( F("Connected to central: " ));
    Serial.println( central.address() );

    if ( central.connected() )
    {
      //if( authenticateCharacteristic.value() == 3838) //authenticated
      {
        if( resetCounterCharacteristic.written() )
        {
          counter = 0;
        }
        if (commandCharacteristic.written() )
        {   
          UserCommandInput(fxc, commandCharacteristic.value());
        }
        if (playCharacteristic.written() )
        {
          //Get all our timing setup.
          unsigned long tc = playCharacteristic.value();
          int prevmatch = GetPreviousTimeCodeMatch(tc);    
          setTimecodeLastMatched(SongTrack_timecode(prevmatch));
          setTimecodeSongOffset(tc);  
          setTimecodeTimeOffset(millis());
          
          //Finally start the track
          trackStart(fxc,tc, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), FxTrackEndAction::StopAtEnd);
        }
  
        long interval = 20;
        unsigned long currentMillis = millis();
        timecodeCharacteristic.writeValue( currentMillis );
        
        if( currentMillis - previousMillis > interval )
        {
          previousMillis = currentMillis;
  
          if( central.rssi() != 0 )
          {
            digitalWrite( RSSI_LED_PIN, LOW );
            
            accelerationCharacteristicX.writeValue( getAccelX() );
            accelerationCharacteristicY.writeValue( getAccelY() );
            accelerationCharacteristicZ.writeValue( getAccelZ() );
  
            gyroCharacteristicZ.writeValue( getGyroX() );
            gyroCharacteristicZ.writeValue( getGyroY() );
            gyroCharacteristicZ.writeValue( getGyroZ() );
  
            counter++;
            counterCharacteristic.writeValue( counter );
  
            unsigned long u = 
              ( (fxc.fxState & 0xFF) << 24 ) |
              ( ((signed char)fxc.paletteSpeed & 0xFF) << 16 ) |
              ( ((signed char)fxc.paletteDirection & 0xFF) << 8 ) |
              ( ((signed char)0xFF & 0xFF) );
            statusCharacteristic.writeValue( u );
          }
          else
          {
            digitalWrite( RSSI_LED_PIN, HIGH );
          }
        } // intervall
        testCharacteristic.writeValue(0x12345678);
      }

    } // while connected

    Serial.print( F( "Disconnected from central: " ) );
    Serial.println( central.address() );
  } // if central
} // loop

#endif
