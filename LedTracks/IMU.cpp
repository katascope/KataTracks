#include "IMU.h"
#include "Log.h"
#include <Arduino_LSM9DS1.h>

void imuSetup()
{
  if ( !IMU.begin() )
  {
    PrintLogln( "Failed to initialize IMU!" );
    while ( 1 );
  }
  PrintLog( "Accelerometer sample rate = " );
  PrintLog( String(IMU.accelerationSampleRate()) );
  PrintLogln( " Hz" );
}
