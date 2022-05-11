#include "Config.h"
#include "Devices.h"
#include "State.h"
#include "FxCore.h"
#include "Fx.h"
#include "Track.h"

void State_Poll_TestPattern(FxController &fxc)
{
    for (int strip=0;strip<NUM_STRIPS;strip++)
    {
      fxc.strip[strip].paletteDirection = 1;
      fxc.strip[strip].paletteSpeed = 1;
      fxc.strip[strip].fxPaletteUpdateType = FxPaletteUpdateType::Always;
    }

    FxEventProcess(fxc, fx_strip + LEDS_0);
    FxEventProcess(fxc, fx_palette_white);
#if !ENABLE_MULTISTRIP
    FxEventProcess(fxc, fx_palette_pulse2_white);
#endif    
    neopixelSetPalette(0, fxc.strip[0].palette, fxc.strip[0].paletteIndex);
    
#if ENABLE_MULTISTRIP    
    FxEventProcess(fxc, fx_strip + LEDS_1);
    FxEventProcess(fxc, fx_palette_pulse2_red);
    neopixelSetPalette(1, fxc.strip[1].palette, fxc.strip[1].paletteIndex);
    
    FxEventProcess(fxc, fx_strip + LEDS_2);
    FxEventProcess(fxc, fx_palette_pulse2_yellow);
    neopixelSetPalette(2, fxc.strip[2].palette, fxc.strip[2].paletteIndex);
    
    FxEventProcess(fxc, fx_strip + LEDS_3);
    FxEventProcess(fxc, fx_palette_pulse2_green);
    neopixelSetPalette(3, fxc.strip[3].palette, fxc.strip[3].paletteIndex);
    
    FxEventProcess(fxc, fx_strip + LEDS_4);
    FxEventProcess(fxc, fx_palette_pulse2_cyan);
    neopixelSetPalette(4, fxc.strip[4].palette, fxc.strip[4].paletteIndex);
    
    FxEventProcess(fxc, fx_strip + LEDS_5);
    FxEventProcess(fxc, fx_palette_pulse2_blue);
    neopixelSetPalette(5, fxc.strip[5].palette, fxc.strip[5].paletteIndex);
    
    FxEventProcess(fxc, fx_strip + LEDS_6);
    FxEventProcess(fxc, fx_palette_pulse2_magenta);
    neopixelSetPalette(6, fxc.strip[6].palette, fxc.strip[6].paletteIndex);
    
    FxEventProcess(fxc, fx_strip + LEDS_7);
    FxEventProcess(fxc, fx_palette_pulse2_orange);
    neopixelSetPalette(7, fxc.strip[7].palette, fxc.strip[7].paletteIndex);
#endif    
}

void CopyRange(FxController &fxc, int strip, int first, int last)
{
  if (first > 16 || last > 16) return;
  
      if (first < last)
        for (int i = first;i<last; i++)
          fxc.strip[strip].palette[i] = fxc.strip[strip].nextPalette[i];
      else
        for (int i = first;i>=last;i--)
          fxc.strip[strip].palette[i] = fxc.strip[strip].nextPalette[i];
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

  //FxTrackSay(timecode, matchedTimecode, nextMatchedTimecode);
    
  if (matchedTimecode > getTimecodeLastMatched())
  {
    for (int strip=0;strip<NUM_STRIPS;strip++)
    {
      if (fxc.strip[strip].transitionType >= Transition_TimedWipePos         
          && fxc.strip[strip].transitionType <= Transition_TimedWipeInOut)
      {
        CopyPalette(fxc.strip[strip].palette, fxc.strip[strip].nextPalette);
      }
      fxc.strip[strip].fxPaletteUpdateType = FxPaletteUpdateType::Always;
    }

    for (int i = 0; i < numSongTracks; i++)
      if (SongTrack_timecode(i) == matchedTimecode)
      {
        Serial.println();
        Serial.print(" @");
        Serial.print(GetTime());
        Serial.print(" ");
        Serial.print(matchedTimecode);
        Serial.print(" ");
        PrintFxEventName(SongTrack_event(i));        
        FxEventProcess(fxc, SongTrack_event(i));
        Serial.print(" : ");
        Serial.print(fxc.transitionMux);
        Serial.print(F(" "));
        for (int strip=0;strip<NUM_STRIPS;strip++)
        {
          PrintFxTransitionName(fxc.strip[strip].transitionType);
          Serial.print(F(", "));
        }
        Serial.print(F(" => "));
      }
      
    setTimecodeLastMatched(timecode);//timeController.lastMatchedTimecode = timecode;
  }

  unsigned long totalSpan = nextMatchedTimecode - getTimecodeLastMatched();
  fxc.transitionMux = ((float)timecode - (float)getTimecodeLastMatched() ) / (float)totalSpan;
  //Serial.print(F("Mux="));
  //Serial.println(fxc.transitionMux);

  for (int strip=0;strip<NUM_STRIPS;strip++)
  {
    if (fxc.stripMask & (1<<strip))
    {    
      if (fxc.strip[strip].transitionType == Transition_TimedFade)
      {
        for (int i = 0; i < NUM_LEDS; i++)
          fxc.strip[strip].palette[i] = LerpRGB(fxc.transitionMux,fxc.strip[strip].initialPalette[i],fxc.strip[strip].nextPalette[i]);
      }
      if (fxc.strip[strip].transitionType == Transition_TimedWipePos)
      {
        int limit = fxc.transitionMux * (NUM_LEDS -1);
        CopyRange(fxc, strip, NUM_LEDS - 1, NUM_LEDS -1 - limit);      
      }
      if (fxc.strip[strip].transitionType == Transition_TimedWipeNeg)
      {
        int limit = fxc.transitionMux * (NUM_LEDS -1);
        CopyRange(fxc,strip, 0,limit);
      }
      if (fxc.strip[strip].transitionType == Transition_TimedWipeOutIn)
      {
        int limit = fxc.transitionMux * (NUM_LEDS/2);
        CopyRange(fxc,strip, 0,limit);
        CopyRange(fxc,strip, NUM_LEDS-1,NUM_LEDS-limit);
      }
      if (fxc.strip[strip].transitionType == Transition_TimedWipeInOut)
      {
        int limit = fxc.transitionMux * (NUM_LEDS/2);
        CopyRange(fxc,strip, NUM_LEDS/2,NUM_LEDS/2-limit);
        CopyRange(fxc,strip, NUM_LEDS/2,NUM_LEDS/2+limit);
      }
    }
    
  }
}

void State_Poll(FxController &fxc)
{
  if (fxc.fxState == FxState_TestPattern)
    State_Poll_TestPattern(fxc);

  if (fxc.fxState == FxState_PlayingTrack)
    State_Poll_Play(fxc, GetTime());
}
