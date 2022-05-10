#include "Config.h"
#include "Devices.h"
#include "State.h"
#include "FxCore.h"
#include "Fx.h"
#include "Track.h"

void State_Poll_TestPattern(FxController &fxc)
{
    FxEventProcess(fxc, fx_palette_rainbow);
    fxc.paletteDirection = 1;
    fxc.paletteSpeed = 1;
    fxc.fxPaletteUpdateType = FxPaletteUpdateType::Always;
}

void CopyRange(FxController &fxc,int first, int last)
{
  if (first < last)
    for (int i = first;i<last; i++)
      fxc.palette[i] = fxc.nextPalette[i];
  else
    for (int i = first;i>=last;i--)
      fxc.palette[i] = fxc.nextPalette[i];
}

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

  //for (int strip=0;strip<NUM_STRIPS;strip++)
  //{
    unsigned long totalSpan = nextMatchedTimecode - getTimecodeLastMatched();
    fxc.transitionMux = ((float)timecode - (float)getTimecodeLastMatched() ) / (float)totalSpan;
  
    if (fxc.transitionType == Transition_TimedFade)
    {
      for (int i = 0; i < NUM_LEDS; i++)
        fxc.palette[i] = LerpRGB(fxc.transitionMux,fxc.initialPalette[i],fxc.nextPalette[i]);
    }
    if (fxc.transitionType == Transition_TimedWipePos)
    {
      int limit = fxc.transitionMux * (NUM_LEDS -1);
      CopyRange(fxc, NUM_LEDS - 1, NUM_LEDS -1 - limit);      
    }
    if (fxc.transitionType == Transition_TimedWipeNeg)
    {
      int limit = fxc.transitionMux * (NUM_LEDS -1);
      CopyRange(fxc,0,limit);
    }
    if (fxc.transitionType == Transition_TimedWipeOutIn)
    {
      int limit = fxc.transitionMux * (NUM_LEDS/2);
      CopyRange(fxc,0,limit);
      CopyRange(fxc,NUM_LEDS-1,NUM_LEDS-limit);
    }
    if (fxc.transitionType == Transition_TimedWipeInOut)
    {
      int limit = fxc.transitionMux * (NUM_LEDS/2);
      CopyRange(fxc,NUM_LEDS/2,NUM_LEDS/2-limit);
      CopyRange(fxc,NUM_LEDS/2,NUM_LEDS/2+limit);
    }
  //}
}

void State_Poll(FxController &fxc)
{
  if (fxc.fxState == FxState_TestPattern)
    State_Poll_TestPattern(fxc);

  if (fxc.fxState == FxState_PlayingTrack)
    State_Poll_Play(fxc, GetTime());
}
