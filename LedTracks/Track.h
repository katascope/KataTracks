#ifndef TRACK_DEF
#define TRACK_DEF
#include "Config.h"
#include <avr/pgmspace.h> 
#include "FxCore.h"

//#define TRACK_FOLLOW    0
#if ENABLE_TEST_TRACK
#define TRACK_TEST      1
#else
#define TRACK_LEAD      1
#endif

// Main Track set to 'The Game Has Changed'
//#define TRACK_START_DELAY    1800  // Delay time from start until track should truly 'start'
//#define TRACK_START_DELAY    2500  // Delay time from start until track should truly 'start'
#define TRACK_START_DELAY    0  // Delay time from start until track should truly 'start'

#if TRACK_LEAD 
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
  4800,fx_transition_timed_wipe_neg,
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

  43300,fx_transition_timed_fade,
  43300,fx_palette_yellow,
  47100,fx_transition_timed_fade,
  47100,fx_palette_green,
  
  50400,fx_transition_timed_fade,
  50400,fx_palette_ocean,
  53300,fx_transition_timed_fade,
  53300,fx_palette_magenta,
  
  //coasting orange 
  54600,fx_speed_1,
  54600,fx_transition_timed_fade,
  54600,fx_palette_orange,

  60000,fx_speed_1,
  60000,fx_speed_neg,
  60000,fx_palette_heat,
//CHAPTER 2
  72700,fx_speed_0,
  72700,fx_transition_timed_fade,
  72700,fx_palette_dark,

//descents
  73000,fx_transition_timed_wipe_pos,
  73000,fx_palette_magenta,
  74000,fx_transition_timed_fade,
  74000,fx_palette_cyan,
  75000,fx_transition_timed_wipe_pos,
  75000,fx_palette_magenta,
  76000,fx_transition_timed_fade,
  76000,fx_palette_cyan,
  77000,fx_transition_timed_wipe_pos,
  77000,fx_palette_magenta,
  78000,fx_transition_timed_fade,
  78000,fx_palette_cyan,
  79000,fx_transition_timed_wipe_pos,
  79000,fx_palette_magenta,

  80400,fx_transition_timed_fade,
  80400,fx_palette_cyan,
  81800,fx_transition_timed_fade,
  81800,fx_palette_blue,

  95000,fx_transition_timed_fade,
  95000,fx_palette_cyan,

  98500,fx_transition_timed_fade,
  98500,fx_palette_dark,

  //99500,fx_transition_timed_fade,
  //99000,fx_palette_red,
  100300,fx_transition_timed_fade,
  100300,fx_palette_red,
  
//CHAPTER 3
  108900,fx_transition_timed_fade,
  108900,fx_palette_white,
  
  125000,fx_transition_timed_fade,
  125000,fx_palette_dark,
  //the end
  127000,fx_palette_dark
};
#endif

#if TRACK_FOLLOW
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
  13000,fx_transition_timed_fade,
  13000,fx_palette_white,

//placeholder
  80500,fx_transition_timed_fade,
  80500, fx_palette_dark,

  //the end
  205000, fx_palette_dark
};
#endif

#if TRACK_TEST
const unsigned long SongTrack[] PROGMEM = 
{
//Basic setup, fade in to blue
  1,fx_palette_dark,
  1,fx_speed_0,  
  1,fx_speed_pos,
  
  1000,fx_transition_fast,
  1000,fx_palette_white,  
  1500,fx_palette_red,  
  2000,fx_palette_yellow,
  2500,fx_palette_green,  
  3000,fx_palette_cyan,
  3500,fx_palette_blue,
  4000,fx_palette_magenta,
  4500,fx_palette_orange,
  5000,fx_palette_half,
  5500,fx_palette_lowhalf,

  6000,fx_transition_timed_wipe_pos,
  6000,fx_palette_white,    
  6500,fx_palette_red,  
  7000,fx_palette_yellow,
  7500,fx_palette_green,  
  8000,fx_palette_cyan,
  8500,fx_palette_blue,
  9000,fx_palette_magenta,
  9500,fx_palette_orange,
  10000,fx_palette_half,
  10500,fx_palette_lowhalf,

  12000,fx_transition_timed_wipe_neg,
  12000,fx_palette_white,    
  12500,fx_palette_red,  
  13000,fx_palette_yellow,
  13500,fx_palette_green,  
  14000,fx_palette_cyan,
  14500,fx_palette_blue,
  15000,fx_palette_magenta,
  15500,fx_palette_orange,
  16000,fx_palette_half,
  16500,fx_palette_lowhalf,


  17000,fx_transition_timed_wipe_pos,
  17500,fx_palette_white,
  17500,fx_transition_timed_wipe_neg,
  18000,fx_palette_red,  
  18500,fx_transition_timed_fade,
  18500,fx_palette_yellow,
  19000,fx_transition_timed_wipe_neg,
  19000,fx_palette_green,  
  19500,fx_transition_timed_wipe_pos,
  19500,fx_palette_cyan,
  20000,fx_transition_timed_fade,
  20000,fx_palette_blue,
  20500,fx_transition_timed_wipe_pos,
  20500,fx_palette_magenta,
  21000,fx_transition_timed_fade,
  21000,fx_palette_orange,
  21500,fx_transition_timed_wipe_neg,
  21500,fx_palette_half,
  22000,fx_transition_timed_fade,
  22000,fx_palette_lowhalf,  
//  600000,fx_palette_magenta
  
//March together
//Arms up
  
/*
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

  43300,fx_transition_timed_fade,
  43300,fx_palette_yellow,
  47100,fx_transition_timed_fade,
  47100,fx_palette_green,
  
  50400,fx_transition_timed_fade,
  50400,fx_palette_ocean,
  53300,fx_transition_timed_fade,
  53300,fx_palette_magenta,
  
  //coasting orange 
  54600,fx_speed_1,
  54600,fx_transition_timed_fade,
  54600,fx_palette_orange,

  60000,fx_speed_1,
  60000,fx_speed_neg,
  60000,fx_palette_heat,
//CHAPTER 2
  72700,fx_speed_0,
  72700,fx_transition_timed_fade,
  72700,fx_palette_dark,

//descents
  73000,fx_transition_timed_wipe_pos,*/
};
#endif
const PROGMEM int numSongTracks = sizeof(SongTrack)/(sizeof(unsigned long)*2);

unsigned long SongTrack_timecode(int i);
unsigned long SongTrack_event(int i);

unsigned long GetFinalTimeCodeEntry();
int GetNextTimeCodeMatch(int currentMatch);
int GetCurrentTimeCodeMatch(unsigned long timecode);
int GetPreviousTimeCodeMatch(unsigned long timecode);

void FxTrackSay(unsigned long timecode, unsigned long matchedTimecode,unsigned long nextMatchedTimecode);
void trackStart(FxController &fxc,unsigned long tc, unsigned long tcOffset, FxTrackEndAction tae);
void trackStop(FxController &fxc);

#endif
