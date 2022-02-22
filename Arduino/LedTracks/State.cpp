#include "Config.h"
#include "Devices.h"
#include "State.h"
#include "FxCore.h"
#include "Fx.h"
#include "Track.h"

void State_Poll_TestPattern(FxController &fxc)
{
    FxEventProcess(fxc, fx_palette_drb);
    fxc.paletteDirection = 1;
    fxc.paletteSpeed = 1;
    fxc.fxPaletteUpdateType = FxPaletteUpdateType::Always;
}

#if ENABLE_IMU
void State_Poll_IMU(FxController &fxc)
{
      byte r = (float)((float)127.0f-(float)getAccelX()*120.0f);
      byte g = (float)((float)127.0f-(float)getAccelY()*120.0f);
      byte b = (float)((float)127.0f-(float)getAccelZ()*120.0f);

      //byte r = (float)((float)127.0f-(float)getGyroX()*1.0f);
      //byte g = (float)((float)127.0f-(float)getGyroY()*1.0f);
      //byte b = (float)((float)127.0f-(float)getGyroZ()*1.0f);

      float roll = 0.98 * getGyroX() + 0.02 * getAccelX();
      float pitch = 0.98 * getGyroY() + 0.02 * getAccelY();
      Serial.print(F(" roll "));
      Serial.print(roll);
      Serial.print(F(" "));
      Serial.print(pitch);
      //r = (byte)( 0   );
      //g = (byte)( roll * 255);
      //b = (byte)( pitch * 255);

      //for (int i=0;i<NUM_LEDS;i++)
      fxc.palette[fxc.paletteIndex] = LEDRGB(r,g,b);
      //rotPalette(fxc.palette);
      fxc.paletteDirection = 1;
      fxc.paletteSpeed = 1;
      fxc.fxPaletteUpdateType = FxPaletteUpdateType::Once;
}
#endif

void State_Poll_Play(FxController &fxc, unsigned long timecode)
{
  unsigned long finalTimeCode = GetFinalTimeCodeEntry();
  if (GetTime() > finalTimeCode)
  {
    Serial.print(F("Done playing, time = "));
    Serial.print(GetTime());
    Serial.print(F(", restart = "));
    Serial.print(finalTimeCode);
    Serial.print(F(" "));

    switch (fxc.fxTrackEndAction) 
    {
      case FxTrackEndAction::StopAtEnd:
        Serial.println(F("StopAtEnd"));
        fxc.fxState = FxState_Default;    
        break;
      case FxTrackEndAction::LoopAtEnd:
        Serial.println(F("LoopAtEnd"));
        //trackStart(fxc, 0, timecode, fxc.trackEndAction); break;
        trackStart(fxc, 0, (unsigned long)(millis() - (signed long)TRACK_START_DELAY), FxTrackEndAction::LoopAtEnd);         
        timecode = GetTime();
        break;
    }
  }
  
  int match = GetCurrentTimeCodeMatch(timecode);
  int nextmatch = GetNextTimeCodeMatch(match);
  unsigned long matchedTimecode = SongTrack_timecode(match);
  unsigned long nextMatchedTimecode = SongTrack_timecode(nextmatch);

  if (matchedTimecode > getTimecodeLastMatched())
  {
    if (fxc.transitionType >= Transition_TimedWipePos         
        && fxc.transitionType <= Transition_TimedWipeInOut)
    {
      CopyPalette(fxc.palette, fxc.nextPalette);
    }
    //fxc.transitionType = Transition_Instant;
    fxc.fxPaletteUpdateType = FxPaletteUpdateType::Always;
    FxTrackSay(timecode, matchedTimecode, nextMatchedTimecode);
    /*Serial.print(((float)matchedTimecode / (float)1000.0f);
      Serial.print(F(" : next @ "));
      Serial.println((float)nextMatchedTimecode / (float)1000.0f);*/

    for (int i = 0; i < numSongTracks; i++)
      if (SongTrack_timecode(i) == matchedTimecode)
        FxEventProcess(fxc, SongTrack_event(i));

    setTimecodeLastMatched(timecode);//timeController.lastMatchedTimecode = timecode;
  }
  

  unsigned long totalSpan = nextMatchedTimecode - getTimecodeLastMatched();
  fxc.transitionMux = ((float)timecode - (float)getTimecodeLastMatched() ) / (float)totalSpan;

  if (fxc.transitionType == Transition_TimedFade)
  {
    //Interpolate initial palette to next palette, based on transition (0 to 1)
    for (int i = 0; i < NUM_LEDS; i++)
      fxc.palette[i] = LerpRGB(fxc.transitionMux,fxc.initialPalette[i],fxc.nextPalette[i]);
  }
  if (fxc.transitionType == Transition_TimedWipePos)
  {
    float mux = (1 - fxc.transitionMux);
    int limit = mux * (NUM_LEDS );
    for (int i = NUM_LEDS - 1; i >= limit; i--)
      fxc.palette[i] = fxc.nextPalette[i];
    fxc.paletteIndex = 0;
    fxc.paletteSpeed = 0;
    fxc.paletteDirection = 0;
  }
  if (fxc.transitionType == Transition_TimedWipeNeg)
  {
    float mux = (fxc.transitionMux);
    int limit = mux * (NUM_LEDS -1);
    for (int i = 0;i < limit; i++)
      fxc.palette[i] = fxc.nextPalette[i];
    fxc.paletteIndex = 0;
    fxc.paletteSpeed = 0;
    fxc.paletteDirection = 0;
  }
  if (fxc.transitionType == Transition_TimedWipeOutIn)
  {
    float mux = (fxc.transitionMux);
    int limit = mux * (NUM_LEDS/2);
    for (int i = 0;i < limit; i++)
      fxc.palette[i] = fxc.nextPalette[i];

    for (int i = NUM_LEDS-1;i > NUM_LEDS-limit; i--)
      fxc.palette[i] = fxc.nextPalette[i];
    
    fxc.paletteIndex = 0;
    fxc.paletteSpeed = 0;
    fxc.paletteDirection = 0;
    
  }
  if (fxc.transitionType == Transition_TimedWipeInOut)
  {
    float mux = (fxc.transitionMux);
    int limit = mux * (NUM_LEDS/2);
    for (int i = NUM_LEDS/2;i>=NUM_LEDS/2-limit;i--)
      fxc.palette[i] = fxc.nextPalette[i];

    for (int i = NUM_LEDS/2;i<NUM_LEDS/2+limit; i++)
      fxc.palette[i] = fxc.nextPalette[i];
    
    fxc.paletteIndex = 0;
    fxc.paletteSpeed = 0;
    fxc.paletteDirection = 0;
  }
}

void State_Poll(FxController &fxc)
{
#if ENABLE_IMU
  if (fxc.fxState == FxState_IMU)
    State_Poll_IMU(fxc);
#endif

  if (fxc.fxState == FxState_TestPattern)
    State_Poll_TestPattern(fxc);

  if (fxc.fxState == FxState_PlayingTrack)
    State_Poll_Play(fxc, GetTime());
}
