#include "Config.h"
#if ENABLE_STATUS
#include "Status.h"
#include "Fx.h"
#include "Track.h"
#include "Timecode.h"

static unsigned long lastTimeDisplay = 0;
void FxDisplayStatus(FxController &fxc)
{
    unsigned long t =  millis();
    if (t - lastTimeDisplay > 1000)//delay to let bluetooth get data
    {      
      Serial.print(GetTime());
      Serial.print(F(":"));
      Serial.print(getTimecodeSongOffset());
      Serial.print(F(":"));
      Serial.print(getTimecodeTimeOffset());
      Serial.print(F("["));
      PrintFxStateName(fxc.fxState);
      Serial.print(F("-"));
      PrintFxTransitionName(fxc.transitionType);
      Serial.print(F("]"));
      if (fxc.fxState == FxState_PlayingTrack)
      {
        int match = GetCurrentTimeCodeMatch(GetTime());
        Serial.print(F("="));
        PrintFxEventName(SongTrack_event(match));
        Serial.print(F(" "));
        Serial.print(SongTrack_timecode(match));
      }

#if ENABLE_IMU
      Serial.print(F(" IMU:"));
      Serial.print(getAccelX());
      Serial.print(F(" "));
      Serial.print(getAccelY());
      Serial.print(F(" "));
      Serial.print(getAccelZ());
      Serial.print(F(" "));
      Serial.print(getGyroX());
      Serial.print(F(" "));
      Serial.print(getGyroY());
      Serial.print(F(" "));
      Serial.print(getGyroZ());
#endif      
      
      Serial.println(F(""));      
      lastTimeDisplay = t;
    }
}

#endif
