#include "Config.h"
#if ENABLE_IMU
#include "IMU.h"
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
    Serial.print( "Failed to initialize IMU!" );
    while ( 1 );
  }
  Serial.print( "Accelerometer sample rate = " );
  Serial.print( String(IMU.accelerationSampleRate()) );
  Serial.print( " Hz" );
}
#endif
