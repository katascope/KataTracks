#include "Config.h"
#include "Fx.h"
#include "Devices.h"

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#if ENABLE_NEOPIXEL
#include <Adafruit_NeoPixel.h>
static Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+0, NEO_GRB + NEO_KHZ800);
#if ENABLE_MULTISTRIP
static Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+1, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+2, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+3, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+4, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+5, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+6, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+7, NEO_GRB + NEO_KHZ800);
#endif
void neopixelSetup()
{
  strip1.begin();
  strip1.setBrightness(25);
#if ENABLE_MULTISTRIP  
  strip2.begin();
  strip2.setBrightness(25);
  strip3.begin();
  strip3.setBrightness(25);
  strip4.begin();
  strip4.setBrightness(25);
  strip5.begin();
  strip5.setBrightness(25);
  strip6.begin();
  strip6.setBrightness(25);
  strip7.begin();
  strip7.setBrightness(25);
  strip8.begin();
  strip8.setBrightness(25);
#endif  
}
void neopixelSetBrightness(unsigned char brightness)
{
  strip1.setBrightness(brightness);
  strip1.show();
#if ENABLE_MULTISTRIP  
  strip2.setBrightness(brightness);
  strip2.show();
  strip3.setBrightness(brightness);
  strip3.show();
  strip4.setBrightness(brightness);
  strip4.show();
  strip5.setBrightness(brightness);
  strip5.show();
  strip6.setBrightness(brightness);
  strip6.show();
  strip7.setBrightness(brightness);
  strip7.show();
  strip8.setBrightness(brightness);
  strip8.show();
#endif  
}
void neopixelSetPalette(uint32_t *palette, int paletteIndex)
{  
  uint32_t offset = paletteIndex;
  for(uint16_t i=0; i<strip1.numPixels(); i++)
  {
    if (offset >= strip1.numPixels())
     offset=0;    
    strip1.setPixelColor(offset, 0xFF7F7F7F);
#if ENABLE_MULTISTRIP    
    strip2.setPixelColor(offset, 0xFFFF7F00);
    strip3.setPixelColor(offset, 0xFFFF0000);
    strip4.setPixelColor(offset, 0xFFFFFF00);
    strip5.setPixelColor(offset, 0xFF00FF00);
    strip6.setPixelColor(offset, 0xFF00FFFF);
    strip7.setPixelColor(offset, 0xFF0000FF);
    strip8.setPixelColor(offset, 0xFFFFFF00);
#endif    
    offset++;    
  }
  strip1.show();
#if ENABLE_MULTISTRIP  
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip7.show();
  strip8.show();
#endif  
}
#endif


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#if ENABLE_IMU
#include <Arduino_LSM9DS1.h>
struct IMUData imu;
float getAccelX() { return imu.accelX; }
float getAccelY() { return imu.accelY; }
float getAccelZ() { return imu.accelZ; }
float getGyroX() { return imu.gyroX; }
float getGyroY() { return imu.gyroY; }
float getGyroZ() { return imu.gyroZ; }
void imuPoll()
{
  if ( IMU.accelerationAvailable() )
    IMU.readAcceleration( imu.accelX, imu.accelY, imu.accelZ );
  if ( IMU.gyroscopeAvailable() )
    IMU.readGyroscope( imu.gyroX, imu.gyroY, imu.gyroZ );
}
void imuSetup()
{
  if ( !IMU.begin() )
  {
    Serial.print( F("Failed to initialize IMU!" ));
    while ( 1 );
  }
  Serial.print(F("Accelerometer sample rate = " ));
  Serial.print(IMU.accelerationSampleRate() );
  Serial.print(F(" Hz" ));
}
#endif

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#if ENABLE_BLE
//#include "BLE.h"
#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
#include "Fx.h"
#include "Cmd.h"
#include "Track.h"
const int BLE_LED_PIN = LED_BUILTIN;
const int RSSI_LED_PIN = 25;//LED_PWR;
BLEService lightsuitService( BLE_UUID_LIGHTSUIT_SERVICE );
BLEUnsignedLongCharacteristic authenticateCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_AUTHENTICATE, BLEWrite);
BLEUnsignedLongCharacteristic testCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TEST, BLERead | BLENotify);
BLEUnsignedLongCharacteristic timecodeCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_TIMECODE, BLERead | BLENotify );
BLEUnsignedLongCharacteristic statusCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_STATUS, BLEWrite | BLERead | BLENotify );
BLECharCharacteristic commandCharacteristic( BLE_UUID_LIGHTSUIT_CHARACTERISTIC_COMMAND, BLERead | BLEWrite  );
BLEUnsignedLongCharacteristic playCharacteristic(BLE_UUID_LIGHTSUIT_CHARACTERISTIC_PLAY, BLERead | BLEWrite  );
BLEUnsignedLongCharacteristic rssiCharacteristic(BLE_UUID_LIGHTSUIT_CHARACTERISTIC_RSSI, BLERead  );

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
  //Serial.print(F("Connected event, central: "));
  //Serial.println(central.address());
}
void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  //Serial.print(F("Disconnected event, central: "));
  //Serial.println(central.address());
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
  lightsuitService.addCharacteristic( rssiCharacteristic );
  
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
void blePoll(FxController &fxc)
{
  static unsigned long counter = 0;
  static long previousMillis = 0;

  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();
  //Serial.println(F("Waiting for connection."));

  if ( central )
  {
//    Serial.println( F("Connected to central: " ));
  //  Serial.println( central.address() );

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

            
#if ENABLE_IMU            
            accelerationCharacteristicX.writeValue( getAccelX() );
            accelerationCharacteristicY.writeValue( getAccelY() );
            accelerationCharacteristicZ.writeValue( getAccelZ() );
  
            gyroCharacteristicZ.writeValue( getGyroX() );
            gyroCharacteristicZ.writeValue( getGyroY() );
            gyroCharacteristicZ.writeValue( getGyroZ() );
#endif  
            counter++;
            counterCharacteristic.writeValue( counter );

            unsigned long u = 
              ( (fxc.fxState & 0xFF) << 24 ) |
              ( ((signed char)fxc.paletteSpeed & 0xFF) << 16 ) |
              ( ((signed char)fxc.paletteDirection & 0xFF) << 8 ) |
              ( ((unsigned char)central.rssi() & 0xFF) );
              
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

    //Serial.print( F( "Disconnected from central: " ) );
    //Serial.println( central.address() );
  } // if central
} // loop
#endif

#if ENABLE_MIC
const int MicrophoneSampler::sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
float MicrophoneSampler::level = 0.0f;
static double MicrophoneSampler::GetLevel()
{
  return level;
}

void MicrophoneSampler::Poll()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    unsigned int sample = analogRead(MIC_PIN);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  //   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  // Serial.println(volts);

  level = (double)peakToPeak  / 1024.0f;  // convert to volts  
}
#endif
