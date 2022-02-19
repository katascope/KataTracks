#include "IMU.h"
#include <Arduino_LSM9DS1.h>


void imuSetup()
{
  if ( !IMU.begin() )
  {
    Serial.print( "Failed to initialize IMU!" );
    while ( 1 );
  }
  Serial.print( "Accelerometer sample rate = " );
  Serial.print( String(IMU.accelerationSampleRate()) );
  Serial.print( " Hz" );
}
