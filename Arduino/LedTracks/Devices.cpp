#include "Config.h"
#include "Fx.h"
#include "Devices.h"
#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))

void rgb2hsv(const unsigned char &src_r, const unsigned char &src_g, const unsigned char &src_b, unsigned char &dst_h, unsigned char &dst_s, unsigned char &dst_v)
{
    float r = src_r / 255.0f;
    float g = src_g / 255.0f;
    float b = src_b / 255.0f;

    float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

    float max = max_f(r, g, b);
    float min = min_f(r, g, b);

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    dst_h = (unsigned char)(h / 2);   // dst_h : 0-180
    dst_s = (unsigned char)(s * 255); // dst_s : 0-255
    dst_v = (unsigned char)(v * 255); // dst_v : 0-255
}

void hsv2rgb(const unsigned char &src_h, const unsigned char &src_s, const unsigned char &src_v, unsigned char &dst_r, unsigned char &dst_g, unsigned char &dst_b)
{
    float h = src_h *   2.0f; // 0-360
    float s = src_s / 255.0f; // 0.0-1.0
    float v = src_v / 255.0f; // 0.0-1.0

    float r, g, b; // 0.0-1.0

    int   hi = (int)(h / 60.0f) % 6;
    float f  = (h / 60.0f) - hi;
    float p  = v * (1.0f - s);
    float q  = v * (1.0f - s * f);
    float t  = v * (1.0f - s * (1.0f - f));

    switch(hi) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    dst_r = (unsigned char)(r * 255); // dst_r : 0-255
    dst_g = (unsigned char)(g * 255); // dst_r : 0-255
    dst_b = (unsigned char)(b * 255); // dst_r : 0-255
}

unsigned long BitRotateColor(unsigned long v)
  {
  unsigned long carry = ((v << 4) & 0x0F000000) >> 24;
  unsigned long value = ((v << 4) & 0x00FFFFFF) | carry;
  return value;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#if ENABLE_NEOPIXEL
#include <Adafruit_NeoPixel.h>
static Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+0, NEO_GRB + NEO_KHZ800);
#if ENABLE_MULTISTRIP
static Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+1, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+2, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+3, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+4, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+5, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+6, NEO_GRB + NEO_KHZ800);
static Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN+7, NEO_GRB + NEO_KHZ800);
#endif
void neopixelSetup()
{
  strip0.begin();
  strip0.setBrightness(25);
#if ENABLE_MULTISTRIP  
  strip1.begin();
  strip1.setBrightness(25);
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
#endif  
}
void neopixelSetBrightness(unsigned char brightness)
{
  strip0.setBrightness(brightness);
  strip0.show();
#if ENABLE_MULTISTRIP  
  strip1.setBrightness(brightness);
  strip1.show();
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
#endif  
}
void neopixelSetPalette(int slot, uint32_t *palette, int paletteIndex)
{  
  uint32_t offset = paletteIndex;
  unsigned char r,g,b;
  unsigned char h,s,v;
  for(uint16_t i=0; i<strip0.numPixels(); i++)
  {
    if (offset >= strip0.numPixels())
     offset=0;    
    switch (slot)
    {
      case 0: strip0.setPixelColor(offset, palette[i]); break;
#if ENABLE_MULTISTRIP  
      case 1: strip1.setPixelColor(offset, palette[i]); break;
      case 2: strip2.setPixelColor(offset, palette[i]); break;
      case 3: strip3.setPixelColor(offset, palette[i]); break;
      case 4: strip4.setPixelColor(offset, palette[i]); break;
      case 5: strip5.setPixelColor(offset, palette[i]); break;
      case 6: strip6.setPixelColor(offset, palette[i]); break;
      case 7: strip7.setPixelColor(offset, palette[i]); break;
#endif      
    }
    offset++;    
  }
  strip0.show();
#if ENABLE_MULTISTRIP  
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
  strip7.show();
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
