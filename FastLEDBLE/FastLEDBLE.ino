//nRF52840 
#define NRF52_SERIES 1
//#include <Adafruit_NeoPixel.h>
#include <ArduinoBLE.h>
//#include <Arduino_LSM9DS1.h>

#include <FastLED.h>
#define LED_PIN     3 // 3, 5 for some, should be 3 
#define NUM_LEDS    310
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin( 9600 );
  Serial.println("Ready"); 
}

void loop()
{
}
