#include "Config.h"
#include <Arduino.h>
#include <avr/pgmspace.h> 
#include "Fx.h"
#include "Track.h"

unsigned long SongTrack_timecode(int i) { return pgm_read_dword(&(SongTrack[i*2+0])); } 
unsigned long SongTrack_event(int i) {  return pgm_read_dword(&(SongTrack[i*2+1])); }

unsigned long GetFinalTimeCodeEntry() { return SongTrack_timecode(numSongTracks-1); }
int GetNextTimeCodeMatch(int currentMatch) { unsigned long tc = SongTrack_timecode(currentMatch); for (int i=0;i<numSongTracks;i++) if (SongTrack_timecode(i) > tc) return i; return 0; }
int GetCurrentTimeCodeMatch(unsigned long timecode) { int match = 0; for (int i=0;i<numSongTracks;i++) { if (SongTrack_timecode(i) <= timecode) match = i; } return match; }
int GetPreviousTimeCodeMatch(unsigned long timecode) { int match = 0; for (int i=0;i<numSongTracks;i++) { if (SongTrack_timecode(i) < timecode) match = i; } return match; }

void FxTrackSay(unsigned long timecode, unsigned long matchedTimecode,unsigned long nextMatchedTimecode)
{
 /*   float tc = (float)matchedTimecode;// / (float)1000.0f;
    Serial.print(tc);
    Serial.print(F(" :"));
    for (int i=0;i<numSongTracks;i++)
    {
      if (SongTrack_timecode(i) == matchedTimecode)
      {
        Serial.print(F(" "));
        //Serial.print(FxEventName(SongTrack_event(i)));
        PrintFxEventName(SongTrack_event(i));
      }
    }
    Serial.print(F(", next = "));
    for (int i=0;i<numSongTracks;i++)
    {
      if (SongTrack_timecode(i) == nextMatchedTimecode)
      {
          Serial.print(F(" "));
          //Serial.print(FxEventName(SongTrack_event(i)));
          PrintFxEventName(SongTrack_event(i));
      }
    }

    float timeUntil = (float)(nextMatchedTimecode - (float)timecode) / 1000.0f;
    Serial.print(F(" in "));
    Serial.print(timeUntil);
    Serial.print(F("s"));
    Serial.println();*/
}

void trackStart(FxController &fxc,unsigned long tc, unsigned long tcOffset, FxTrackEndAction tae)
{
  fxc.fxState = FxState_PlayingTrack;
  fxc.paletteSpeed = 0;
  fxc.paletteDirection = 1;
  fxc.transitionType = Transition_Instant;
  fxc.fxTrackEndAction = tae;
  setTimecodeLastMatched(tc);
  setTimecodeTimeOffset((unsigned long)(millis() - (signed long)TRACK_START_DELAY));
  fxc.transitionMux = 0;
  Serial.print(F("Playing Track"));
  Serial.print(F(", Time Offset = "));
  Serial.println(getTimecodeTimeOffset());
}

void trackStop(FxController &fxc)
{
  fxc.fxState = FxState_Default;
  fxc.fxPaletteUpdateType = FxPaletteUpdateType::None;
  //Serial.println(F("Stopping Track"));
}
