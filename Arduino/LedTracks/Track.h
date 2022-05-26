#ifndef TRACK_DEF
#define TRACK_DEF
#include "Config.h"
#include <avr/pgmspace.h>
#include "FxCore.h"

#if LEAD
#define COLOR_ALPHA fx_palette_red
#define COLOR_BETA  fx_palette_blue
#define COLOR_THETA  fx_palette_cyan
#define COLOR_DELTA  fx_palette_magenta
#elif FOLLOW
#define COLOR_ALPHA fx_palette_blue
#define COLOR_BETA  fx_palette_red
#define COLOR_THETA fx_palette_magenta
#define COLOR_DELTA  fx_palette_cyan
#endif

// Main Track set to 'The Game Has Changed'
#define TRACK_START_DELAY    0  // Delay time from start until track should truly 'start'

#define __TRACK_BEGIN \
  1, fx_strip_all, \
  1, fx_palette_dark, \
  1, fx_speed_rst, \
  1, fx_speed_0, \
  1, fx_speed_pos, \

#define __TRACK_END(I) \
  I, fx_strip_all, \
  I, fx_transition_timed_fade, \
  I, fx_palette_dark, \
  I + 1000, fx_transition_fast,\
  I + 1000, fx_palette_dark,

#define __FADE_TO(I, FXRGB) \
  I, fx_transition_timed_fade, \
  I, FXRGB,

#define __FLASH_WHITE(I) \
  I, fx_strip_all, \
  I, fx_transition_fast, \
  I, fx_palette_half, \
  I, fx_speed_rst,

#define __FLASH(I, FXRGB) \
  I, fx_strip_all, \
  I, fx_transition_fast, \
  I, FXRGB, \
  I, fx_speed_rst,

#define __WIPE_UP(I,FXRGB) \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, 

 #define __WIPE_DN(I,FXRGB) \
  I, fx_speed_rst, \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, 

#define __PLASMA(I,FXRGB) \
  I, fx_speed_2, \
  I, fx_speed_neg, \
  I, fx_transition_timed_fade, \
  I, FXRGB, 

#define __PLASMA_FAST(I,FXRGB) \
  I, fx_speed_3, \
  I, fx_speed_neg, \
  I, fx_transition_timed_fade, \
  I, FXRGB,

#define __PLASMA_OPPOSING(I,FXRGB1, FXRGB2) \
  I, fx_strip_evens, \
  I, fx_speed_2, \
  I, fx_speed_pos, \
  I, fx_transition_timed_fade, \
  I, FXRGB1, \
  I, fx_strip_odds, \
  I, fx_speed_2, \
  I, fx_speed_neg, \
  I, fx_transition_timed_fade, \
  I, FXRGB2, \
  I, fx_strip_all,  

  
#define __STROBE_COLORS(I,FXRGB1,FXRGB2) \
  I, fx_transition_timed_fade, \
  I, fx_palette_blue, \
  I+400, fx_palette_red, \
  I+800, fx_palette_blue, \
  I+1200, fx_palette_red, \
  I+1600, fx_palette_blue, \
  I+2000, fx_palette_red, \
  I+2400, fx_palette_blue, \
  I+2800, fx_palette_red, \
  I+3200, fx_palette_blue, \
  I+3600, fx_palette_red, \
  I+3600, fx_speed_0, \
  //I+4000, fx_transition_timed_fade, \
  //I+4000, fx_palette_dark,

#define __FIRE_EFFECT(I, FXRGB1, FXRGB2, FXRGB3, FXRGB4, FXRGB5) \
  I, fx_speed_rst, \
  I, fx_speed_3, \
  I, fx_speed_neg, \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB1, \
  I+600, FXRGB2, \
  I+1200, FXRGB3, \
  I+1800, FXRGB4, \
  I+2400, FXRGB5, \
  I+3000, FXRGB3, \
  I+3600, FXRGB4, \
  I+4200, FXRGB5,

//break up into legs in chest in arms in segments

#define __COLOR_FROM_FEET(I, FXRGB) \
  I, fx_strip + (LEDS_6|LEDS_7), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, 

#define __COLOR_FROM_NECK(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEDS_0|LEDS_1|LEDS_2|LEDS_3), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define __COLOR_FROM_SHOULDERS_TO_WRISTS(I, FXRGB) \
  I, fx_strip + (LEDS_4|LEDS_5), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define __COLOR_FROM_SHOULDERS_TO_CENTER(I, FXRGB) \
  I, fx_strip + (LEDS_0|LEDS_1|LEDS_2|LEDS_3), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \


#define __COLOR_FROM_WAIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEDS_6|LEDS_7), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, 

#define __COLOR_FROM_BELLY(I, FXRGB) \
  I, fx_strip + (LEDS_0|LEDS_1|LEDS_2|LEDS_3), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define __COLOR_FROM_WRISTS(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_ARM|LEFT_ARM), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define __COLOR_FROM_RIGHT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_ARM), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define __COLOR_FROM_LEFT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_ARM), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define __COLOR_TO_RIGHT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_ARM), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define __COLOR_TO_LEFT_WRIST(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_ARM), \
  I, fx_transition_timed_wipe_neg, \
  I, FXRGB, \

#define __COLOR_FROM_RIGHT_SHOULDER_TO_CENTER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_CHEST_A|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define __COLOR_FROM_LEFT_SHOULDER_TO_CENTER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_CHEST_A|LEFT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define __COLOR_FROM_CENTER_TO_LEFT_SHOULDER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (LEFT_CHEST_A|LEFT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \

#define __COLOR_FROM_CENTER_TO_RIGHT_SHOULDER(I, FXRGB) \
  I, fx_speed_rst, \
  I, fx_strip + (RIGHT_CHEST_A|RIGHT_CHEST_B), \
  I, fx_transition_timed_wipe_pos, \
  I, FXRGB, \


//Multistrip
const unsigned long SongTrack[] PROGMEM =
{
  __TRACK_BEGIN

  //Lead CrossStep
  __FLASH_WHITE(2500)
  __COLOR_FROM_FEET(2500, COLOR_ALPHA)
  __COLOR_FROM_BELLY(2900, COLOR_ALPHA)
  __COLOR_FROM_SHOULDERS_TO_WRISTS(3300, COLOR_ALPHA)
  3650, fx_strip_all,
  __FADE_TO(3650, fx_palette_dark)
  
  //Follow CrossStep
  __FLASH_WHITE(4800)
  __COLOR_FROM_FEET(4800, COLOR_BETA)
  __COLOR_FROM_BELLY(5200, COLOR_BETA)
  __COLOR_FROM_SHOULDERS_TO_WRISTS(5600, COLOR_BETA)
  5950, fx_strip_all,
  __FADE_TO(5950, fx_palette_dark)
  
  //Lead CrossStep
  __FLASH_WHITE(7300)
  __COLOR_FROM_FEET(7300, fx_palette_rb)
  __COLOR_FROM_BELLY(7700, fx_palette_rb)
  __COLOR_FROM_SHOULDERS_TO_WRISTS(8100, fx_palette_rb)  
  8450, fx_strip_all,
  __FADE_TO(8450, fx_palette_dark)
  
  //March together
  __FLASH_WHITE(9700)
  __PLASMA(9700, fx_palette_rb)
  
  //Arms up & Circles around each other
  __STROBE_COLORS(10800,COLOR_ALPHA, COLOR_BETA)
  //__FADE_TO(14800, fx_palette_dark)
  //__COLOR_FROM_WRISTS(14800, fx_palette_magenta)
#if LEAD  
  __COLOR_FROM_RIGHT_WRIST(14800, fx_palette_magenta)
  __COLOR_FROM_RIGHT_SHOULDER_TO_CENTER(15200, fx_palette_magenta)
  __COLOR_FROM_CENTER_TO_LEFT_SHOULDER(15600, fx_palette_magenta)
  __COLOR_FROM_WAIST(16000, fx_palette_magenta)
  __COLOR_TO_LEFT_WRIST(16400, fx_palette_magenta)
#elif FOLLOW
  __COLOR_FROM_RIGHT_WRIST(14800, fx_palette_magenta)
  __COLOR_FROM_RIGHT_SHOULDER_TO_CENTER(15200, fx_palette_magenta)
  __COLOR_FROM_CENTER_TO_LEFT_SHOULDER(15600, fx_palette_magenta)
  __COLOR_FROM_WAIST(16000, fx_palette_magenta)
  __COLOR_TO_LEFT_WRIST(16400, fx_palette_magenta)
/*  __COLOR_FROM_LEFT_WRIST(14800, fx_palette_magenta`)
  __COLOR_FROM_LEFT_SHOULDER_TO_CENTER(15200, fx_palette_magenta)
  __COLOR_FROM_CENTER_TO_RIGHT_SHOULDER(15600, fx_palette_magenta)
  __COLOR_FROM_WAIST(16000, fx_palette_magenta)
  __COLOR_TO_RIGHT_WRIST(16400, fx_palette_magenta)*/
#endif  

  //Build2
  __FLASH_WHITE(16800)
  __PLASMA_FAST(16800, fx_palette_cm)
  //__FADE_TO(19200, fx_palette_dark)
  
  //BEATS
  __FLASH_WHITE(19600)
  __FIRE_EFFECT(19600, fx_palette_red, fx_palette_blue, fx_palette_rb, fx_palette_pulse2_blue, fx_palette_pulse2_red)

  //calm/smooth in down
  __FLASH_WHITE(24500)

  __COLOR_FROM_FEET(24500, COLOR_ALPHA)
  __COLOR_FROM_BELLY(25250, COLOR_ALPHA)
  __COLOR_FROM_SHOULDERS_TO_WRISTS(26000, COLOR_ALPHA)

  __FLASH_WHITE(26500)
  //__COLOR_FROM_WRISTS(26900, fx_palette_dark)
  //__COLOR_FROM_NECK(27650, fx_palette_dark)
  //__COLOR_FROM_WAIST(28400, fx_palette_dark)

//Reachout?
  __COLOR_FROM_WRISTS(26900, fx_palette_magenta)
  __COLOR_FROM_SHOULDERS_TO_CENTER(27400, fx_palette_magenta)
  __COLOR_FROM_WAIST(27900, fx_palette_magenta)

  __FLASH_WHITE(29000)
  //Take them to crazytown.. we came together, so purple again?
/*  
  __FADE_TO(29000, fx_palette_dr)
  29400, fx_transition_fast,
  29400, fx_palette_half,*/
  29000, fx_transition_timed_fade,
  29000, fx_palette_blue,
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
  __COLOR_FROM_FEET(34080, COLOR_BETA)
  __COLOR_FROM_BELLY(34470, fx_palette_rb)
  __COLOR_FROM_SHOULDERS_TO_WRISTS(34860, COLOR_ALPHA)
  __COLOR_FROM_FEET(35250, fx_palette_rb)
  __COLOR_FROM_BELLY(35640, COLOR_ALPHA)
  __COLOR_FROM_SHOULDERS_TO_WRISTS(36030, COLOR_BETA)
  __COLOR_FROM_FEET(36420, COLOR_ALPHA)
  __COLOR_FROM_BELLY(36810, COLOR_BETA)
  __COLOR_FROM_SHOULDERS_TO_WRISTS(37200, fx_palette_rb)
  37590, fx_strip_all,
  37590, fx_transition_timed_fade,
  37590, fx_palette_red,

  //Paso Spins
  __FADE_TO(38700, fx_palette_dr)
  __FADE_TO(39200, fx_palette_dr)

  __FADE_TO(41300, fx_palette_dark)
    //__WIPE_UP(43300, fx_palette_blue)
  43300, fx_speed_rst,
  43300, fx_transition_timed_fade,
  43300, fx_strip + (LEDS_2),
  43300, fx_palette_red,
  43775, fx_strip + (LEDS_1),
  43775, fx_palette_red,
  44250, fx_strip + (LEDS_0),
  44250, fx_palette_red,
  44725, fx_strip + (LEDS_3),
  44725, fx_palette_red,
  45200, fx_strip + (LEDS_4),
  45200, fx_palette_red,
  45675, fx_strip + (LEDS_6),
  45675, fx_palette_red,
  46150, fx_strip + (LEDS_5),
  46150, fx_palette_red,
  46625, fx_strip + (LEDS_7),
  46625, fx_palette_red,
  47100, fx_strip_all,
  47100, fx_speed_2,
  47100, fx_speed_neg,
  __FADE_TO(47100, fx_palette_pulse2_red)
  __FADE_TO(48100, fx_palette_pulse2_red)
//primetime
  __FLASH_WHITE(50400)

//blue fire
  __FIRE_EFFECT(50600, fx_palette_pulse2_blue, fx_palette_pulse2_cyan, fx_palette_pulse2_white, fx_palette_blue, fx_palette_cyan)
  __FIRE_EFFECT(55000, fx_palette_pulse2_blue, fx_palette_pulse2_magenta, fx_palette_db, fx_palette_dm, fx_palette_dbm)
  
  __FADE_TO(57200, fx_palette_magenta)
  __FADE_TO(59600, fx_palette_pulse_dark)

  __PLASMA_OPPOSING(60000, fx_palette_pulse2_cyan, fx_palette_pulse2_magenta)

  //CHAPTER 2
  72000, fx_speed_0,
  72000, fx_speed_pos,
  __FADE_TO(72000, fx_palette_magenta)

  //Side-Kicks
  __WIPE_UP(73000, COLOR_THETA)
  __WIPE_UP(74000, COLOR_DELTA)
  __WIPE_UP(75000, COLOR_THETA)
  __WIPE_UP(76000, COLOR_DELTA)
  __WIPE_UP(77000, COLOR_THETA)
  __WIPE_UP(78000, COLOR_DELTA)
  __WIPE_UP(79000, COLOR_THETA)
  __WIPE_UP(80000, COLOR_DELTA)

  ///bwaaah, into the sss...qqs's
  81500, fx_speed_2,
  81500, fx_speed_neg,
  __FADE_TO(81500, fx_palette_pulse2_red)
  __FADE_TO(82800, fx_palette_pulse2_red)
  //end of bwaah

  __FADE_TO(88000, fx_palette_rb)
  __FLASH(94000, fx_palette_magenta)
  //__FADE_TO(96000, fx_palette_magenta)

  //98 to 107 = the spin and recover
  //pulsy approach  
 // 98500, fx_speed_2,
  //98500, fx_speed_neg,
  //__FADE_TO(98500, fx_palette_pulse_magenta)
#if LEAD
//  100000, fx_strip_all,
  __FADE_TO(100000, fx_palette_dark)
  //pickup from spinning
  __COLOR_FROM_WRISTS(101000, fx_palette_magenta)
  __COLOR_FROM_NECK(102000, fx_palette_magenta)
  __COLOR_FROM_WAIST(103000, fx_palette_magenta)
#elif FOLLOW  
  __FADE_TO(103000, fx_palette_magenta)//redundant
#endif  
  104000, fx_strip_all,  
  104000, fx_speed_2,
  104000, fx_speed_neg,
  __FADE_TO(104000, fx_palette_pulse2_magenta)
 // __FADE_TO(105000, fx_palette_dark)

  //CHAPTER 3
  //big march around
  __FADE_TO(107900, fx_palette_half)
  __FADE_TO(108900, COLOR_ALPHA)

  //__FADE_TO(111000, fx_palette_red)
  __FADE_TO(118000, fx_palette_blue)
  __FADE_TO(119000, fx_palette_red)
  __FADE_TO(119500, fx_palette_blue)
  __FADE_TO(120000, fx_palette_red)
  __FADE_TO(120500, fx_palette_magenta)

  121000, fx_speed_neg,
  121000, fx_speed_4,
  __FADE_TO(121000, fx_palette_pulse2_white)
  __FADE_TO(121500, fx_palette_pulse2_white)

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

  __FADE_TO(125000, fx_palette_magenta)
  __FADE_TO(126000, fx_palette_dark)

  //the end
  __TRACK_END(127000)
};

#if 0
//Single strip
const unsigned long SongTrackDanceSingle[] PROGMEM =
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
#endif

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
