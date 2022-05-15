#ifndef TRACK_DEF
#define TRACK_DEF
#include "Config.h"
#include <avr/pgmspace.h>
#include "FxCore.h"

#define TRACK_LEAD      1
#define TRACK_FOLLOW    0

// Main Track set to 'The Game Has Changed'
#define TRACK_START_DELAY    0  // Delay time from start until track should truly 'start'

const unsigned long SongTrackSquid[] PROGMEM =
{
  //Basic setup, fade in to blue
  1, fx_strip_all,
  1, fx_palette_dark,
  1, fx_speed_0,
  1, fx_speed_pos,

  500, fx_transition_fast,
  500, fx_palette_half,

  750, fx_transition_timed_fade,
  750, fx_palette_blue,

  1000, fx_strip + (LEDS_0),
  1000, fx_palette_red,
  1250, fx_strip + (LEDS_1),
  1250, fx_palette_red,
  1500, fx_strip + (LEDS_2),
  1500, fx_palette_red,
  1750, fx_strip + (LEDS_3),
  1750, fx_palette_red,
  2000, fx_strip + (LEDS_4),
  2000, fx_palette_red,
  2250, fx_strip + (LEDS_5),
  2250, fx_palette_red,
  2500, fx_strip + (LEDS_6),
  2500, fx_palette_red,
  2750, fx_strip + (LEDS_7),
  2750, fx_palette_red,
  3000, fx_strip_all,
  3000, fx_transition_timed_fade,
  3000, fx_palette_dark,
  3500, fx_transition_timed_fade,
  3500, fx_palette_dark,
  
  4000, fx_strip_evens,
  4000, fx_speed_2,
  4000, fx_speed_pos,
  4000, fx_transition_fast,
  4000, fx_palette_pulse2_cyan,
  
  4000, fx_strip_odds,
  4000, fx_speed_2,
  4000, fx_speed_neg,
  4000, fx_transition_fast,
  4000, fx_palette_pulse2_magenta,
  4000, fx_strip_all,

  7000, fx_strip_all,
  7000, fx_transition_timed_fade,
  7000, fx_palette_dark,
  8000, fx_speed_rst,
  8000, fx_strip + (LEDS_4|LEDS_5),//arms
  8000, fx_transition_timed_wipe_pos,
  8000, fx_palette_magenta,

  10000, fx_speed_rst,
  10000, fx_strip + (LEDS_0|LEDS_1|LEDS_2|LEDS_3),//chest
  10000, fx_transition_timed_wipe_neg,
  10000, fx_palette_magenta,
    
  11000, fx_speed_rst,
  11000, fx_strip + (LEDS_6|LEDS_7),//legs
  11000, fx_transition_timed_wipe_neg,
  11000, fx_palette_magenta,

 //opposite arms
  13900, fx_strip_all,
  13900, fx_transition_fast,
  13900, fx_palette_dark,
  14000, fx_strip + (LEDS_4|LEDS_5),
  14000, fx_speed_rst,
  14000, fx_transition_fast,
  14000, fx_palette_pulse2_magenta,
  14000, fx_strip + (LEDS_4),
  14000, fx_speed_4,
  14000, fx_speed_pos,
  14000, fx_strip + (LEDS_5),
  14000, fx_speed_4,
  14000, fx_speed_neg,
  14000, fx_strip_all,

  17000, fx_strip + (LEDS_0),
  17000, fx_palette_red,
  17250, fx_strip + (LEDS_1),
  17250, fx_palette_yellow,
  17500, fx_strip + (LEDS_2),
  17500, fx_palette_green,
  17750, fx_strip + (LEDS_3),
  17750, fx_palette_cyan,
  18000, fx_strip + (LEDS_4),
  18000, fx_palette_blue,
  18250, fx_strip + (LEDS_5),
  18250, fx_palette_magenta,
  18500, fx_strip + (LEDS_6),
  18500, fx_palette_orange,
  18750, fx_strip + (LEDS_7),
  18750, fx_palette_half,
  19000, fx_strip_all,
  
  22000, fx_strip_all,
  22000, fx_transition_fast,
  22000, fx_palette_dark,
  22500, fx_palette_dark
};

const unsigned long SongTrack[] PROGMEM =
{
  //Basic setup, fade in to blue
  1, fx_strip_all,
  1, fx_palette_dark,
  1, fx_speed_0,
  1, fx_speed_pos,
  1, fx_speed_rst,

  //Lead CrossStep
  2500, fx_transition_fast,
  2500, fx_palette_half,
  2500, fx_transition_timed_wipe_pos,
  2500, fx_palette_blue,

  3650, fx_transition_timed_fade,
  3650, fx_palette_dark,

  //Follow CrossStep
  4800, fx_transition_fast,
  4800, fx_palette_half,
  4800, fx_transition_timed_wipe_pos,
  4800, fx_palette_red,

  5950, fx_transition_timed_fade,
  5950, fx_palette_dark,

  //Lead CrossStep
  7300, fx_transition_fast,
  7300, fx_palette_half,
  7300, fx_transition_timed_wipe_pos,
  7300, fx_palette_rb,

  8450, fx_transition_timed_fade,
  8450, fx_palette_dark,

  //Both CrossStep
  9700, fx_transition_fast,
  9700, fx_palette_half,
  9700, fx_transition_timed_fade,
  9700, fx_palette_rb,
  9700, fx_speed_1,
  9700, fx_speed_neg,

  //March together
  //Arms up
  10800,fx_transition_timed_fade,
  10800,fx_palette_blue,
  11200,fx_palette_red,
  11600,fx_palette_blue,
  12000,fx_palette_red,
  12400,fx_palette_blue,
  12800,fx_palette_red,
  13200,fx_palette_blue,
  13600,fx_palette_red,
  14000,fx_palette_blue,
  14400,fx_palette_red,

  //Circles around each other
  14600, fx_transition_fast, //timed_fade,
  14600, fx_palette_magenta,
  14600, fx_speed_0,
  14600, fx_transition_fast, //_timed_fade,
  14600, fx_palette_dark,

  //Build2
  16800, fx_transition_fast, //_timed_fade,
  16800, fx_palette_half,
  16800, fx_speed_2,
  16800, fx_speed_neg,
  16800, fx_transition_timed_fade,
  16800, fx_palette_cm,
    
  19200,fx_transition_timed_fade,
  19200,fx_palette_dark,

  //BEATS
  19600, fx_transition_fast,
  19600, fx_palette_half,
  19600, fx_transition_timed_wipe_pos,
  19600, fx_palette_red,
  20200, fx_palette_yellow,
  20800, fx_palette_wr,
  21400, fx_palette_ry,
  22000, fx_palette_wy,
  22600, fx_palette_wr,
  23200, fx_palette_ry,
  23700, fx_palette_dark,

  //calm/smooth in down
  24200, fx_transition_fast,
  24200, fx_palette_half,
  26500, fx_transition_fast,
  26500, fx_palette_db,
  28900, fx_transition_fast,
  28900, fx_palette_half,
  29000, fx_transition_timed_fade,
  29000, fx_palette_dr,

  //29400 beat
  //30400 beat
  //31500 beat
  //32800 beat
  //34000 beat
  //35100 beat
  //36400 beat
  //37600 beat
  29400, fx_transition_fast,
  29400, fx_palette_half,
  29400, fx_transition_timed_fade,
  29400, fx_palette_red,
  29790, fx_palette_green,
  30180, fx_palette_blue,
  30570, fx_palette_rg,
  30960, fx_palette_gb,
  31350, fx_palette_rb,
  31740, fx_palette_red,
  32130, fx_palette_green,
  32520, fx_palette_blue,
  32910, fx_palette_rg,
  33300, fx_palette_rb,
  33690, fx_palette_red,
  //33690,fx_transition_fast,
  34080, fx_speed_2,
  34080, fx_speed_neg,
  34080, fx_palette_green,
  34470, fx_palette_gb,
  34860, fx_palette_blue,
  35250, fx_palette_rb,
  35640, fx_palette_red,
  36030, fx_palette_rg,
  36420, fx_palette_green,
  36810, fx_palette_gb,
  37200, fx_palette_blue,
  37590, fx_palette_rb,

  //Paso Spins
  38700, fx_transition_timed_fade,
  38700, fx_palette_dr,
  39200, fx_palette_dr,

  43300, fx_speed_0,
  43300, fx_speed_neg,
  43300, fx_speed_rst,
  43300, fx_transition_timed_wipe_neg,
  43300, fx_palette_blue,
  47100, fx_transition_timed_fade,
  47100, fx_palette_red,

  50400, fx_transition_timed_fade,
  50400, fx_palette_half,
  53300, fx_transition_timed_fade,
  53300, fx_palette_magenta,

  //coasting orange
  54600, fx_speed_0,
  54600, fx_speed_pos,
  54600, fx_transition_timed_fade,
  54600, fx_palette_blue,

  57800, fx_transition_timed_fade,
  57800, fx_palette_pulse_dark,

  60000, fx_speed_3,
  60000, fx_speed_neg,
  60000, fx_transition_timed_fade,
  60000, fx_palette_pulse_magenta,

  //CHAPTER 2
  72000, fx_speed_0,
  72000, fx_speed_pos,
  72000, fx_transition_timed_fade,
  72000, fx_palette_magenta,

  //descents
  73000, fx_transition_timed_wipe_pos,
  73000, fx_palette_cyan,
  74000, fx_transition_timed_wipe_pos,
  74000, fx_palette_magenta,
  75000, fx_transition_timed_wipe_pos,
  75000, fx_palette_cyan,
  76000, fx_transition_timed_wipe_pos,
  76000, fx_palette_magenta,
  77000, fx_transition_timed_wipe_pos,
  77000, fx_palette_cyan,
  78000, fx_transition_timed_wipe_pos,
  78000, fx_palette_magenta,
  79000, fx_transition_timed_wipe_pos,
  79000, fx_palette_cyan,
  80000, fx_transition_timed_wipe_pos,
  80000, fx_palette_magenta,

  //  80400,fx_transition_timed_fade,
  //  80400,fx_palette_magenta,
  ///bwaaah
  81500, fx_speed_2,
  81500, fx_speed_neg,
  81500, fx_transition_timed_fade,
  81500, fx_palette_pulse_red,
  82800, fx_transition_timed_fade,
  82800, fx_palette_pulse_red,
  //end of bwaah

  88000, fx_transition_timed_fade,
  88000, fx_palette_rb,

  94000, fx_transition_timed_fade,
  94000, fx_palette_blue,
  94000, fx_transition_fast,
  94000, fx_palette_half,
  94000, fx_transition_timed_fade,
  94000, fx_palette_dark,

  //98 to 107 = the spin and recover

  //pulsy approach
  /*98500,fx_speed_3,
    98500,fx_speed_pos,
    98500,fx_transition_timed_fade,
    98500,fx_palette_pulse_white,*/
  //imu approach
  98500, fx_speed_2,
  98500, fx_speed_neg,
  98500, fx_transition_timed_fade,
  98500, fx_palette_pulse_magenta,

  104000, fx_speed_2,
  104000, fx_speed_neg,
  104000, fx_transition_timed_fade,
  104000, fx_palette_pulse_white,

  //CHAPTER 3
  //big march around
//  107900, fx_speed_0,
//  107900, fx_speed_pos,
  107900, fx_transition_timed_fade,
  107900, fx_palette_half,

  110000, fx_transition_timed_fade,
  110000, fx_palette_half,

  111000, fx_transition_timed_fade,
  111000, fx_palette_half,

  111000, fx_speed_1,
  111000, fx_speed_neg,
  111000, fx_transition_timed_fade,
  111000, fx_palette_cyan,
  118000, fx_transition_timed_fade,
  118000, fx_palette_magenta,
  119000, fx_transition_timed_fade,
  119000, fx_palette_red,
  119500, fx_transition_timed_fade,
  119500, fx_palette_blue,
  120000, fx_transition_timed_fade,
  120000, fx_palette_red,
  120500, fx_transition_timed_fade,
  120500, fx_palette_blue,
  121000, fx_speed_neg,
  121000, fx_speed_4,
  121000, fx_transition_timed_fade,
  121000, fx_palette_pulse2_white,
  121500, fx_transition_timed_fade,
  121500, fx_palette_pulse2_white,

  122100, fx_speed_8,
  122100, fx_transition_fast,
  122100, fx_palette_pulse_red,
  122200, fx_palette_pulse_yellow,
  122300, fx_palette_pulse_green,
  122400, fx_palette_pulse_cyan,
  122500, fx_palette_pulse_blue,
  122600, fx_palette_pulse_magenta,
  122700, fx_palette_pulse_white,
  122800, fx_palette_pulse_red,
  122900, fx_palette_pulse_yellow,
  123000, fx_palette_pulse_green,
  123100, fx_palette_pulse_cyan,
  123200, fx_palette_pulse_blue,
  123300, fx_palette_pulse_magenta,
  123400, fx_palette_pulse_white,
  123500, fx_speed_16,
  123500, fx_transition_fast,
  123500, fx_palette_pulse2_red,
  123600, fx_palette_pulse2_yellow,
  123700, fx_palette_pulse2_green,
  123800, fx_palette_pulse2_cyan,
  124900, fx_palette_pulse2_blue,
  124000, fx_palette_pulse2_magenta,
  124100, fx_palette_pulse2_white,  
  124200, fx_palette_pulse2_red,
  124300, fx_palette_pulse2_yellow,
  124400, fx_palette_pulse2_green,
  124500, fx_palette_pulse2_cyan,
  124600, fx_palette_pulse2_blue,
  124700, fx_palette_pulse2_magenta,
  124800, fx_palette_pulse2_white,  

  125000, fx_transition_timed_fade,
  125000, fx_palette_half,
  126000, fx_transition_timed_fade,
  126000, fx_palette_dark,

  //the end
  127000, fx_transition_timed_fade,
  127000, fx_palette_dark,
  129000, fx_transition_timed_fade,
  129000, fx_palette_dark
};

const PROGMEM int numSongTracks = sizeof(SongTrack) / (sizeof(unsigned long) * 2);

unsigned long SongTrack_timecode(int i);
unsigned long SongTrack_event(int i);

unsigned long GetFinalTimeCodeEntry();
int GetNextTimeCodeMatch(int currentMatch);
int GetCurrentTimeCodeMatch(unsigned long timecode);
int GetPreviousTimeCodeMatch(unsigned long timecode);

void trackStart(FxController &fxc, unsigned long tc, unsigned long tcOffset, FxTrackEndAction tae);
void trackStop(FxController &fxc);
void FxTrackSay(unsigned long timecode, unsigned long matchedTimecode,unsigned long nextMatchedTimecode);
#endif
