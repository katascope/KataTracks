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
