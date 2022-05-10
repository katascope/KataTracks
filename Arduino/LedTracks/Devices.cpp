#include "Config.h"
#include "Fx.h"
#include "Devices.h"

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
void neopixelSetBrightness(int strip, unsigned char brightness)
{
  if (brightness > BRIGHTNESS_LIMIT)
    brightness = BRIGHTNESS_LIMIT;
    
  switch (strip)
  {
    case 0:
      strip0.setBrightness(brightness);
      strip0.show();
    break;
#if ENABLE_MULTISTRIP  
    case 1:
      strip1.setBrightness(brightness);
      strip1.show();
    break;
    case 2:
      strip2.setBrightness(brightness);
      strip2.show();
    break;
    case 3:
      strip3.setBrightness(brightness);
      strip3.show();
    break;
    case 4:
      strip4.setBrightness(brightness);
      strip4.show();
    break;
    case 5:
      strip5.setBrightness(brightness);
      strip5.show();
    break;
    case 6:
      strip6.setBrightness(brightness);
      strip6.show();
    break;
    case 7:
      strip7.setBrightness(brightness);
      strip7.show();
    break;
#endif  
  }
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
     uint32_t rgb = palette[i];
     byte r = (rgb >> 24)&0xFF;
     byte g = (rgb >> 16)&0xFF;
     byte b = (rgb >> 8)&0xFF;
     byte h,s,v;

#if ENABLE_MULTISTRIP  
    /*switch (slot)
    {
      case 0: rgb = LEDRGB(255,255,255);break;
      case 1: rgb = LEDRGB(255,0,0);break;
      case 2: rgb = LEDRGB(255,255,0);break;
      case 3: rgb = LEDRGB(0,255,0);break;
      case 4: rgb = LEDRGB(0,255,255);break;
      case 5: rgb = LEDRGB(0,0,255);break;
      case 6: rgb = LEDRGB(255,0,255);break;
      case 7: rgb = LEDRGB(255,127,0);break;
    }*/
#endif      
    switch (slot)
    {
      case 0: strip0.setPixelColor(offset, rgb); break;
#if ENABLE_MULTISTRIP  
      case 1: strip1.setPixelColor(offset, rgb); break;
      case 2: strip2.setPixelColor(offset, rgb); break;
      case 3: strip3.setPixelColor(offset, rgb); break;
      case 4: strip4.setPixelColor(offset, rgb); break;
      case 5: strip5.setPixelColor(offset, rgb); break;
      case 6: strip6.setPixelColor(offset, rgb); break;
      case 7: strip7.setPixelColor(offset, rgb); break;
#endif      
    }
    offset++;    
  }
    switch (slot)
    {
      case 0: strip0.show();break;
#if ENABLE_MULTISTRIP  
      case 1: strip1.show();break;
      case 2: strip2.show();break;
      case 3: strip3.show();break;
      case 4: strip4.show();break;
      case 5: strip5.show();break;
      case 6: strip6.show();break;
      case 7: strip7.show();break;
#endif  
    }
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
