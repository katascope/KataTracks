#include "Config.h"
#include <Arduino.h>
#include <avr/pgmspace.h> 
#include "Fx.h"
#include "Track.h"
#include "FxCore.h"

unsigned long SongTrack_timecode(int i) { return pgm_read_dword(&(SongTrack[i*2+0])); } 
unsigned long SongTrack_event(int i) {  return pgm_read_dword(&(SongTrack[i*2+1])); }

unsigned long GetFinalTimeCodeEntry() { return SongTrack_timecode(numSongTracks-1); }
int GetNextTimeCodeMatch(int currentMatch) { 
  unsigned long tc = SongTrack_timecode(currentMatch); 
  for (int i=0;i<numSongTracks;i++) if (SongTrack_timecode(i) > tc) return i; return 0; 
}
int GetCurrentTimeCodeMatch(unsigned long timecode) { int match = 0; for (int i=0;i<numSongTracks;i++) { if (SongTrack_timecode(i) <= timecode) match = i; } return match; }
int GetPreviousTimeCodeMatch(unsigned long timecode) { int match = 0; for (int i=0;i<numSongTracks;i++) { if (SongTrack_timecode(i) < timecode) match = i; } return match; }

void FxTrackSay(unsigned long timecode, unsigned long matchedTimecode,unsigned long nextMatchedTimecode)
{
    float tc = (float)matchedTimecode;// / (float)1000.0f;
    Serial.print(tc);
    Serial.print(F(" :"));
    for (int i=0;i<numSongTracks;i++)
    {
      if (SongTrack_timecode(i) == matchedTimecode)
      {
        Serial.print(F(" "));
        PrintFxEventName(SongTrack_event(i));
      }
    }
    Serial.print(F(", next("));
    Serial.print(nextMatchedTimecode);
    Serial.print(F(")= "));
    for (int i=0;i<numSongTracks;i++)
    {
      if (SongTrack_timecode(i) == nextMatchedTimecode)
      {
          Serial.print(F(" "));
          Serial.print(SongTrack_event(i));
          PrintFxEventName(SongTrack_event(i));
      }
    }
    float timeUntil = (float)(nextMatchedTimecode - (float)timecode) / 1000.0f;
    Serial.print(F(" in "));
    Serial.print(timeUntil);
    Serial.print(F("s"));
    Serial.println();
}


void trackStart(FxController &fxc,unsigned long tc, unsigned long tcOffset, FxTrackEndAction trackEndAction)
{
  fxc.fxState = FxState_PlayingTrack;

  for (int strip=0;strip<NUM_STRIPS;strip++)
  {    
    fxc.strip[strip]->paletteSpeed = 0;
    fxc.strip[strip]->paletteDirection = 1;
    fxc.strip[strip]->transitionType = Transition_Instant;
    fxc.strip[strip]->fxPaletteUpdateType = FxPaletteUpdateType::Once;    
  }
  fxc.transitionMux = 0;
  fxc.fxTrackEndAction = trackEndAction;
  setTimecodeLastMatched(tc);
  setTimecodeTimeOffset((unsigned long)(millis() - (signed long)TRACK_START_DELAY));
  Serial.print(F("Playing Track"));
  Serial.print(F(", Time Offset = "));
  Serial.println(getTimecodeTimeOffset());
}

void trackStop(FxController &fxc)
{
  fxc.fxState = FxState_Default;
  for (int strip=0;strip<NUM_STRIPS;strip++)
  {    
    fxc.strip[strip]->fxPaletteUpdateType = FxPaletteUpdateType::None; 
    fxc.strip[strip]->SetParticlesRunning(false);
  }
  fxc.stripMask = 0xFF;
  //Serial.println(F("Stopping Track"));
}
