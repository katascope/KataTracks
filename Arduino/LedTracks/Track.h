#ifndef TRACK_DEF
#define TRACK_DEF
#include "Config.h"
#include <avr/pgmspace.h>
#include "FxCore.h"

//#define TRACK_FOLLOW    0
#if ENABLE_TEST_TRACK
//#define TRACK_TEST_TRANSITIONS      1
#define TRACK_TEST_FULL      1
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
  1, fx_palette_dark,
  1, fx_speed_0,
  1, fx_speed_pos,
  1, fx_strips_all,
  1, fx_stripmask_0 + (LEDS_0|LEDS_2|LEDS_3|LEDS_4),

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
  7300, fx_palette_magenta,

  8450, fx_transition_timed_fade,
  8450, fx_palette_dark,

  //Both CrossStep
  9700, fx_transition_timed_fade,
  9700, fx_palette_rb,
  9700, fx_speed_1,
  9700, fx_speed_neg,

  //March together
  //Arms up
  /*10800,fx_transition_timed_fade,
    10800,fx_palette_blue,
    11200,fx_palette_red,
    11600,fx_palette_blue,
    12000,fx_palette_red,
    12400,fx_palette_blue,
    12800,fx_palette_red,
    13200,fx_palette_blue,
    13600,fx_palette_red,
    14000,fx_palette_blue,
    14400,fx_palette_red,*/

  //Circles around each other
  14600, fx_transition_fast, //timed_fade,
  14600, fx_palette_magenta,
  14600, fx_speed_0,

  //Build2
  16800, fx_transition_fast, //_timed_fade,
  16800, fx_palette_cm,
  16800, fx_speed_2,
  16800, fx_speed_neg,

  //18600 beat
  /*18600,fx_transition_fast,
    18600,fx_palette_pulse_yellow,

    //Coast2
    19200,fx_transition_timed_fade,
    19200,fx_palette_pulse2_orange,*/

  //BEATS
  19600, fx_transition_timed_wipe_pos,
  19600, fx_palette_red,
  20200, fx_palette_yellow,
  20800, fx_palette_red,
  21400, fx_palette_yellow,
  22000, fx_palette_red,
  22600, fx_palette_yellow,
  23200, fx_palette_white,

  //calm/smooth in down
  24200, fx_transition_timed_wipe_pos,
  24200, fx_palette_red,
  26500, fx_transition_timed_fade,
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
  29400, fx_transition_timed_fade,
  29400, fx_palette_red,
  29790, fx_palette_green,
  30180, fx_palette_blue,
  30570, fx_palette_red,
  30960, fx_palette_green,
  31350, fx_palette_red,
  31740, fx_palette_green,
  32130, fx_palette_blue,
  32520, fx_palette_red,
  32910, fx_palette_green,
  33300, fx_palette_blue,
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
  38700, fx_palette_red,
  39200, fx_palette_red,

  43300, fx_speed_0,
  43300, fx_speed_neg,
  43300, fx_speed_rst,
  43300, fx_transition_timed_wipe_pos,
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
  81800, fx_speed_2,
  81800, fx_speed_neg,
  81800, fx_transition_timed_fade,
  81800, fx_palette_red,
  82800, fx_transition_timed_fade,
  82800, fx_palette_red,
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
  107900, fx_speed_0,
  107900, fx_speed_pos,
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
  122100, fx_palette_pulse2_red,
  122200, fx_palette_pulse2_yellow,
  122300, fx_palette_pulse2_green,
  122400, fx_palette_pulse2_cyan,
  122500, fx_palette_pulse2_blue,
  122600, fx_palette_pulse2_magenta,
  122700, fx_palette_pulse2_white,
  122800, fx_transition_fast,
  122800, fx_palette_rainbow,

  124500, fx_speed_16,
  124500, fx_transition_fast,
  124500, fx_palette_rainbow,

  125000, fx_transition_timed_fade,
  125000, fx_palette_white,
  126000, fx_transition_timed_fade,
  126000, fx_palette_dark,

  //the end
  127000, fx_transition_timed_fade,
  127000, fx_palette_dark,
  129000, fx_transition_timed_fade,
  129000, fx_palette_dark
};
#endif

#if TRACK_FOLLOW
const unsigned long SongTrack[] PROGMEM =
{
  //Setup
  1, fx_palette_dark,
  250, fx_transition_fast,
  250, fx_palette_dark,

  2000, fx_transition_timed_wipe_neg,
  2000, fx_palette_red,

  3000, fx_transition_timed_wipe_neg,
  3000, fx_palette_yellow,

  4000, fx_transition_timed_wipe_neg,
  4000, fx_palette_green,

  5000, fx_transition_timed_fade,
  5000, fx_palette_cyan,

  6000, fx_transition_timed_fade,
  6000, fx_palette_green,

  7000, fx_transition_timed_fade,
  7000, fx_palette_blue,

  8000, fx_transition_timed_fade,
  8000, fx_palette_magenta,

  9000, fx_transition_timed_fade,
  9000, fx_palette_orange,

  10000, fx_transition_timed_fade,
  10000, fx_palette_dark,
};
#endif

#if TRACK_TEST_TRANSITIONS
const unsigned long SongTrack[] PROGMEM =
{
  1, fx_palette_dark,
  1, fx_speed_0,
  1, fx_speed_pos,

  1000, fx_transition_fast,
  1000, fx_palette_white,
  1250, fx_palette_red,
  1500, fx_palette_yellow,
  1750, fx_palette_green,
  2000, fx_palette_cyan,
  2250, fx_palette_blue,
  2500, fx_palette_magenta,
  2750, fx_palette_orange,
  3000, fx_palette_half,
  3250, fx_palette_lowhalf,

  3500, fx_transition_timed_wipe_pos,
  3750, fx_palette_white,
  4000, fx_palette_red,
  4250, fx_palette_yellow,
  4500, fx_palette_green,
  4750, fx_palette_cyan,
  5000, fx_palette_blue,
  5250, fx_palette_magenta,
  5500, fx_palette_orange,
  5750, fx_palette_half,
  6000, fx_palette_lowhalf,

  //7000,fx_palette_lowhalf,

  6250, fx_transition_timed_wipe_neg,
  6500, fx_palette_white,
  6750, fx_palette_red,
  7000, fx_palette_yellow,
  7250, fx_palette_green,
  7500, fx_palette_cyan,
  7750, fx_palette_blue,
  8000, fx_palette_magenta,
  8250, fx_palette_orange,
  8500, fx_palette_half,
  8750, fx_palette_lowhalf,

  9000, fx_transition_timed_wipe_outin,
  9000, fx_palette_white,
  11000, fx_transition_timed_wipe_inout,
  11000, fx_palette_red,
  12000, fx_transition_timed_wipe_outin,
  12000, fx_palette_yellow,
  13000, fx_transition_timed_wipe_inout,
  13000, fx_palette_green,
  14000, fx_transition_timed_wipe_outin,
  14000, fx_palette_cyan,
  15000, fx_transition_timed_wipe_inout,
  15000, fx_palette_blue,
  16000, fx_transition_timed_wipe_outin,
  16000, fx_palette_magenta,
  17000, fx_transition_timed_wipe_inout,
  17000, fx_palette_orange,
  18000, fx_transition_timed_wipe_outin,
  18000, fx_palette_half,
  19000, fx_transition_timed_wipe_inout,
  19000, fx_palette_lowhalf,

  /*
    20000,fx_transition_timed_wipe_pos,
    20000,fx_palette_white,
    21000,fx_transition_timed_wipe_neg,
    21000,fx_palette_red,
    22000,fx_transition_timed_fade,
    22000,fx_palette_yellow,
    23000,fx_transition_timed_wipe_neg,
    23000,fx_palette_green,
    24000,fx_transition_timed_wipe_pos,
    24000,fx_palette_cyan,
    25000,fx_transition_timed_fade,
    25000,fx_palette_blue,
    26000,fx_transition_timed_wipe_pos,
    26000,fx_palette_magenta,
    27000,fx_transition_timed_fade,
    27000,fx_palette_orange,
    28000,fx_transition_timed_wipe_neg,
    28000,fx_palette_half,
    29000,fx_transition_timed_fade,*
    29000,fx_palette_lowhalf,  */

};
#endif

#if TRACK_TEST_FULL
const unsigned long SongTrack[] PROGMEM =
{
  //Basic setup, fade in to blue
  1, fx_palette_dark,
  1, fx_speed_0,
  1, fx_speed_pos,

  1000, fx_transition_fast,
  1000, fx_palette_white,
  1250, fx_palette_red,
  1500, fx_palette_yellow,
  1750, fx_palette_green,
  2000, fx_palette_cyan,
  2250, fx_palette_blue,
  2500, fx_palette_magenta,
  2750, fx_palette_orange,
  3000, fx_palette_half,
  3250, fx_palette_lowhalf,

  3500, fx_transition_timed_wipe_pos,
  3750, fx_palette_white,
  4000, fx_palette_red,
  4250, fx_palette_yellow,
  4500, fx_palette_green,
  4750, fx_palette_cyan,
  5000, fx_palette_blue,
  5250, fx_palette_magenta,
  5500, fx_palette_orange,
  5750, fx_palette_half,
  6000, fx_palette_lowhalf,

  6250, fx_transition_timed_wipe_neg,
  6500, fx_palette_white,
  6750, fx_palette_red,
  7000, fx_palette_yellow,
  7250, fx_palette_green,
  7500, fx_palette_cyan,
  7750, fx_palette_blue,
  8000, fx_palette_magenta,
  8250, fx_palette_orange,
  8500, fx_palette_half,
  8750, fx_palette_lowhalf,


  9000, fx_transition_timed_wipe_pos,
  9000, fx_palette_white,
  11000, fx_transition_timed_wipe_neg,
  11000, fx_palette_red,
  12000, fx_transition_timed_fade,
  12000, fx_palette_yellow,
  13000, fx_transition_timed_wipe_neg,
  13000, fx_palette_green,
  14000, fx_transition_timed_wipe_pos,
  14000, fx_palette_cyan,
  15000, fx_transition_timed_fade,
  15000, fx_palette_blue,
  16000, fx_transition_timed_wipe_pos,
  16000, fx_palette_magenta,
  17000, fx_transition_timed_fade,
  17000, fx_palette_orange,
  18000, fx_transition_timed_wipe_neg,
  18000, fx_palette_half,
  19000, fx_transition_timed_fade,
  19000, fx_palette_lowhalf,

  20000, fx_palette_pulse_dark,
  20000, fx_speed_1,
  20000, fx_speed_pos,
  21000, fx_palette_pulse_white,
  22000, fx_palette_pulse_red,
  23000, fx_palette_pulse_yellow,
  24000, fx_palette_pulse_green,

  25000, fx_speed_1,
  25000, fx_speed_neg,
  25000, fx_palette_pulse_cyan,
  26000, fx_palette_pulse_blue,
  27000, fx_palette_pulse_magenta,
  28000, fx_palette_pulse_orange,
  29000, fx_palette_pulse_lowhalf,

  30000, fx_palette_lava,
  32000, fx_palette_cloud,
  34000, fx_palette_ocean,
  36000, fx_palette_forest,
  38000, fx_palette_rainbow,
  40000, fx_palette_rainbowstripe,
  42000, fx_palette_party,
  44000, fx_palette_heat,

  45000, fx_transition_fast,
  45000, fx_speed_0,
  45000, fx_palette_dw,
  45500, fx_palette_dr,
  46000, fx_palette_dy,
  46500, fx_palette_dg,
  47000, fx_palette_dc,
  47500, fx_palette_db,
  48000, fx_palette_dm,
  48500, fx_palette_wr,
  49000, fx_palette_wy,
  49500, fx_palette_wg,
  50000, fx_palette_wc,
  50500, fx_palette_wb,
  51000, fx_palette_wm,
  51500, fx_palette_ry,
  52000, fx_palette_rg,
  52500, fx_palette_rc,
  53000, fx_palette_rb,
  53500, fx_palette_rm,
  54000, fx_palette_yg,
  54500, fx_palette_yc,
  55000, fx_palette_yb,
  55500, fx_palette_ym,
  56000, fx_palette_gc,
  56500, fx_palette_gb,
  57000, fx_palette_gm,
  57500, fx_palette_cb,
  58000, fx_palette_cm,
  58500, fx_palette_bm,


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
const PROGMEM int numSongTracks = sizeof(SongTrack) / (sizeof(unsigned long) * 2);

unsigned long SongTrack_timecode(int i);
unsigned long SongTrack_event(int i);

unsigned long GetFinalTimeCodeEntry();
int GetNextTimeCodeMatch(int currentMatch);
int GetCurrentTimeCodeMatch(unsigned long timecode);
int GetPreviousTimeCodeMatch(unsigned long timecode);

void FxTrackSay(unsigned long timecode, unsigned long matchedTimecode, unsigned long nextMatchedTimecode);
void trackStart(FxController &fxc, unsigned long tc, unsigned long tcOffset, FxTrackEndAction tae);
void trackStop(FxController &fxc);

#endif
