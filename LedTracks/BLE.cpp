#include "Config.h"
#if ENABLE_BLE
#include "BLE.h"

#include <Arduino_LSM9DS1.h>
const int BLE_LED_PIN = LED_BUILTIN;
const int RSSI_LED_PIN = LED_PWR;

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

bool bleSetup()
{
  pinMode( BLE_LED_PIN, OUTPUT );
  pinMode( RSSI_LED_PIN, OUTPUT );
  
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

  digitalWrite( BLE_LED_PIN, HIGH );    
  return true;
}

void bleloop()
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

    if ( central.connected() )
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
          if ( IMU.accelerationAvailable() )
          {
            float imuAccelX, imuAccelY, imuAccelZ;
            IMU.readAcceleration( imuAccelX, imuAccelY, imuAccelZ );
            Serial.print(F("Acc="));
            Serial.print(imuAccelX);
            Serial.print('\t');
            Serial.print(imuAccelY);
            Serial.print('\t');
            Serial.print(imuAccelZ);
            accelerationCharacteristicX.writeValue( imuAccelX );
            accelerationCharacteristicY.writeValue( imuAccelY );
            accelerationCharacteristicZ.writeValue( imuAccelZ );
          }

          if ( IMU.gyroscopeAvailable() )
          {
            float imuGyroX, imuGyroY, imuGyroZ;
            IMU.readGyroscope( imuGyroX, imuGyroY, imuGyroZ );
            Serial.print(F("Gyro="));
            Serial.print(imuGyroX);
            Serial.print('\t');
            Serial.print(imuGyroY);
            Serial.print('\t');
            Serial.print(imuGyroZ);
            gyroCharacteristicX.writeValue( imuGyroX );
            gyroCharacteristicY.writeValue( imuGyroY);
            gyroCharacteristicZ.writeValue( imuGyroZ );
          }

          counter++;
          Serial.print(F("Count="));
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

#endif
