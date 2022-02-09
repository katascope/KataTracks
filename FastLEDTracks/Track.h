#if !defined TRACK_DEF
#define TRACK_DEF
#include <avr/pgmspace.h> 

#define LEAD      1                // Set 1 for Dance lead, 0 for Dance follow

// Main Track set to 'The Game Has Changed'
//#define TRACK_START_DELAY    1800  // Delay time from start until track should truly 'start'
//#define TRACK_START_DELAY    2500  // Delay time from start until track should truly 'start'
#define TRACK_START_DELAY    0  // Delay time from start until track should truly 'start'
#if LEAD 
const unsigned long SongTrack[] PROGMEM = 
{
//Basic setup, fade in to blue
  1,fx_palette_dark,
  1,fx_speed_0,  
  1,fx_speed_pos,
  
//Lead CrossStep
  2500,fx_transition_timed_wipe_pos,
  2500,fx_palette_blue,
//Follow CrossStep
  4800,fx_transition_timed_wipe_pos,
  4800,fx_palette_red,
//Lead CrossStep
  7300,fx_transition_timed_wipe_pos,
  7300,fx_palette_blue,
//Follow CrossStep
  9700,fx_transition_timed_fade,
  9700,fx_palette_rb,

//March together
//Arms up
  
//Circles around each other
  14400,fx_transition_timed_fade, 
  14400,fx_palette_magenta,

//Build2
  16800,fx_transition_timed_fade, 
  16800,fx_palette_rb,

//Coast2
  19200,fx_transition_timed_fade,
  19200,fx_palette_cyan,
  
  24200,fx_transition_timed_wipe_pos,
  24200,fx_palette_white,    
  26500,fx_transition_timed_fade,    
  26500,fx_palette_db,
  28900,fx_transition_timed_fade,    
  28900,fx_palette_dr,

  //Paso Spins
  38700,fx_transition_timed_fade,
  38700,fx_palette_red,
  /*39000,fx_transition_timed_fade,
  39000,fx_transition_timed_fade,
  39000,fx_palette_cyan,
  39300,fx_transition_timed_fade,
  39300,fx_palette_red,
  39500,fx_transition_timed_fade,
  39500,fx_palette_cyan,
  39900,fx_transition_timed_fade,
  39900,fx_palette_red,*/

  43300,fx_transition_timed_fade,
  43300,fx_palette_yellow,
  /*43600,fx_transition_timed_fade,
  43600,fx_palette_cyan,
  43900,fx_transition_timed_fade,
  43900,fx_palette_yellow,
*/
  47100,fx_transition_timed_fade,
  47100,fx_palette_green,
  
  50400,fx_transition_timed_fade,
  50400,fx_palette_ocean,
  53300,fx_transition_timed_fade,
  53300,fx_palette_magenta,
  
  //coasting orange 
  54600,fx_speed_1,
  54600,fx_transition_timed_fade,
  54600,fx_palette_heat,

  60000,fx_palette_heat,
//CHAPTER 2
/*
  60000,fx_transition_timed_fade,
  60000,fx_palette_cyan,
  62500,fx_transition_timed_fade,
  62500,fx_palette_magenta,
  64800,fx_transition_timed_fade,
  64800,fx_palette_cyan,
  67500,fx_transition_timed_fade,
  67500,fx_palette_magenta,
  70000,fx_transition_timed_fade,
  70000,fx_palette_cyan,*/
  72700,fx_speed_0,

//descents
  72700,fx_transition_timed_wipe_pos,
  72700,fx_palette_blue,  
  74300,fx_transition_timed_wipe_pos,
  74300,fx_palette_red,
  75900,fx_transition_timed_wipe_pos,
  75900,fx_palette_blue,
  77200,fx_transition_timed_wipe_pos,
  77200,fx_palette_red,
  78800,fx_transition_timed_wipe_pos,
  78800,fx_palette_blue,

  80400,fx_transition_timed_fade,
  80400,fx_palette_yellow,
  81800,fx_transition_timed_fade,
  81800,fx_palette_white,

  99000,fx_transition_timed_fade,
  99000,fx_palette_red,

//CHAPTER 3
  108900,fx_transition_timed_fade,
  108900,fx_palette_cyan,
  
  125000,fx_transition_timed_fade,
  125000,fx_palette_dark,
  //the end
  127000,fx_palette_dark
};
#else //Follow
const unsigned long SongTrack[] PROGMEM = 
{
//Setup 
  1,fx_palette_dark,

  //1000,fx_transition_timed_wipe_pos,
  500,fx_palette_dark,

  1000,fx_transition_timed_wipe_neg,
  1000,fx_palette_blue,

  4000,fx_transition_timed_wipe_neg,
  4000,fx_palette_magenta,
  
  7000,fx_transition_timed_wipe_neg,
  7000,fx_palette_red,

  10000,fx_transition_timed_fade,
  10000,fx_palette_green,
  /*
  13000,fx_transition_timed_fade,
  13000,fx_palette_dark,

  15000,fx_transition_timed_wipe_pos,
  15000,fx_palette_rgb,*/
  13000,fx_transition_timed_fade,
  13000,fx_palette_white,

//placeholder
  80500,fx_transition_timed_fade,
  80500, fx_palette_dark,

  //the end
  205000, fx_palette_dark
};
#endif
const PROGMEM int numSongTracks = sizeof(SongTrack)/(sizeof(unsigned long)*2);

static unsigned long SongTrack_timecode(int i) { return pgm_read_dword(&(SongTrack[i*2+0])); } 
static unsigned long SongTrack_event(int i) {  return pgm_read_dword(&(SongTrack[i*2+1])); }

static int GetNextTimeCodeMatch(int currentMatch) { unsigned long tc = SongTrack_timecode(currentMatch); for (int i=0;i<numSongTracks;i++) if (SongTrack_timecode(i) > tc) return i; return 0; }
static int GetCurrentTimeCodeMatch(unsigned long timecode) { int match = 0; for (int i=0;i<numSongTracks;i++) { if (SongTrack_timecode(i) <= timecode) match = i; } return match; }
static int GetPreviousTimeCodeMatch(unsigned long timecode) { int match = 0; for (int i=0;i<numSongTracks;i++) { if (SongTrack_timecode(i) < timecode) match = i; } return match; }

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
        Serial.print(FxEventName(SongTrack_event(i)));
      }
    }
    Serial.print(F(", next = "));  
    for (int i=0;i<numSongTracks;i++)
    {
      if (SongTrack_timecode(i) == nextMatchedTimecode)
      {
          Serial.print(F(" "));
          Serial.print(FxEventName(SongTrack_event(i)));
      }
    }
  
    float timeUntil = (float)(nextMatchedTimecode - (float)timecode) / 1000.0f;
    Serial.print(F(" in "));
    Serial.print(timeUntil);
    Serial.print(F("s"));
    Serial.println();
}

#endif
