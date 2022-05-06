using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KataTracks
{
    class TrackDecoder
    {
        enum Fx
        {
            fx_speed_0 = 0,
            fx_speed_1 = 1,
            fx_speed_2 = 2,
            fx_speed_3 = 3,
            fx_speed_4 = 4,
            fx_speed_5 = 5,
            fx_speed_6 = 6,
            fx_speed_7 = 7,
            fx_speed_8 = 8,
            fx_speed_9 = 9,
            fx_speed_10 = 10,
            fx_speed_11 = 11,
            fx_speed_12 = 12,
            fx_speed_13 = 13,
            fx_speed_14 = 14,
            fx_speed_15 = 15,
            fx_speed_16 = 16,
            fx_speed_17 = 17,
            fx_speed_18 = 18,
            fx_speed_32 = 19,

            fx_speed_pos = 20,
            fx_speed_neg = 21,
            fx_speed_inc = 22,
            fx_speed_dec = 23,
            fx_speed_rst = 24,

            fx_transition_fast,
            fx_transition_timed_fade,
            fx_transition_timed_wipe_pos,
            fx_transition_timed_wipe_neg,
            fx_transition_timed_wipe_outin,
            fx_transition_timed_wipe_inout,

            fx_palette_lead,
            fx_palette_follow,

            fx_track_begin,
            fx_track_stop,

            fx_palette_lava,
            fx_palette_cloud,
            fx_palette_ocean,
            fx_palette_forest,
            fx_palette_rainbow,
            fx_palette_rainbowstripe,
            fx_palette_party,
            fx_palette_heat,

            fx_palette_dark,
            fx_palette_white,
            fx_palette_red,
            fx_palette_yellow,
            fx_palette_green,
            fx_palette_cyan,
            fx_palette_blue,
            fx_palette_magenta,
            fx_palette_orange,
            fx_palette_half,
            fx_palette_lowhalf,

            fx_palette_pulse_dark,
            fx_palette_pulse_white,
            fx_palette_pulse_red,
            fx_palette_pulse_yellow,
            fx_palette_pulse_green,
            fx_palette_pulse_cyan,
            fx_palette_pulse_blue,
            fx_palette_pulse_magenta,
            fx_palette_pulse_orange,
            fx_palette_pulse_half,
            fx_palette_pulse_lowhalf,

            fx_palette_pulse2_dark,
            fx_palette_pulse2_white,
            fx_palette_pulse2_red,
            fx_palette_pulse2_yellow,
            fx_palette_pulse2_green,
            fx_palette_pulse2_cyan,
            fx_palette_pulse2_blue,
            fx_palette_pulse2_magenta,
            fx_palette_pulse2_orange,
            fx_palette_pulse2_half,
            fx_palette_pulse2_lowhalf,

            fx_palette_dw,
            fx_palette_dr,
            fx_palette_dy,
            fx_palette_dg,
            fx_palette_dc,
            fx_palette_db,
            fx_palette_dm,
            fx_palette_wr,
            fx_palette_wy,
            fx_palette_wg,
            fx_palette_wc,
            fx_palette_wb,
            fx_palette_wm,
            fx_palette_ry,
            fx_palette_rg,
            fx_palette_rc,
            fx_palette_rb,
            fx_palette_rm,
            fx_palette_yg,
            fx_palette_yc,
            fx_palette_yb,
            fx_palette_ym,
            fx_palette_gc,
            fx_palette_gb,
            fx_palette_gm,
            fx_palette_cb,
            fx_palette_cm,
            fx_palette_bm,

            fx_palette_wry,
            fx_palette_wrg,
            fx_palette_wrc,
            fx_palette_wrb,
            fx_palette_wrm,
            fx_palette_wyg,
            fx_palette_wyc,
            fx_palette_wyb,
            fx_palette_wym,
            fx_palette_wgc,
            fx_palette_wgb,
            fx_palette_wgm,
            fx_palette_wcb,
            fx_palette_wcm,
            fx_palette_wbm,

            fx_palette_dry,
            fx_palette_drg,
            fx_palette_drc,
            fx_palette_drb,
            fx_palette_drm,
            fx_palette_dyg,
            fx_palette_dyc,
            fx_palette_dyb,
            fx_palette_dym,
            fx_palette_dgc,
            fx_palette_dgb,
            fx_palette_dgm,
            fx_palette_dcb,
            fx_palette_dcm,
            fx_palette_dbm,

            fx_palette_accel,
            fx_palette_gyro,
            fx_palette_mic,

            fx_color1_dark,
            fx_color1_white,
            fx_color1_red,
            fx_color1_yellow,
            fx_color1_green,
            fx_color1_cyan,
            fx_color1_blue,
            fx_color1_magenta,
            fx_color1_orange,
            fx_color1_half,
            fx_color1_lowhalf,

            fx_color2_dark,
            fx_color2_white,
            fx_color2_red,
            fx_color2_yellow,
            fx_color2_green,
            fx_color2_cyan,
            fx_color2_blue,
            fx_color2_magenta,
            fx_color2_orange,
            fx_color2_half,
            fx_color2_lowhalf,

            fx_color3_dark,
            fx_color3_white,
            fx_color3_red,
            fx_color3_yellow,
            fx_color3_green,
            fx_color3_cyan,
            fx_color3_blue,
            fx_color3_magenta,
            fx_color3_orange,
            fx_color3_half,
            fx_color3_lowhalf,

            fx_colors1,
            fx_colors2,
            fx_colors3,
            fx_colors4,
            fx_colors5,
            fx_colors6,
            fx_colors7,
            fx_colors8,
            fx_colors9,
            fx_colors10,
            fx_colors11,
            fx_colors12,
            fx_colors13,
            fx_colors14,
            fx_colors15,
            fx_colors16,

            fx_nothing = 255
        };

        static List<ulong> track = new List<ulong>()
        {

  //Basic setup, fade in to blue
  1, (ulong)Fx.fx_palette_dark,
  1, (ulong)Fx.fx_speed_0,
  1, (ulong)Fx.fx_speed_pos,

  //Lead CrossStep
  2500, (ulong)Fx.fx_transition_fast,
  2500, (ulong)Fx.fx_palette_half,
  2500, (ulong)Fx.fx_transition_timed_wipe_pos,
  2500, (ulong)Fx.fx_palette_blue,

  3650, (ulong)Fx.fx_transition_timed_fade,
  3650, (ulong)Fx.fx_palette_dark,

  //Follow CrossStep
  4800, (ulong)Fx.fx_transition_fast,
  4800, (ulong)Fx.fx_palette_half,
  4800, (ulong)Fx.fx_transition_timed_wipe_pos,
  4800, (ulong)Fx.fx_palette_red,

  5950, (ulong)Fx.fx_transition_timed_fade,
  5950, (ulong)Fx.fx_palette_dark,

  //Lead CrossStep
  7300, (ulong)Fx.fx_transition_fast,
  7300, (ulong)Fx.fx_palette_half,
  7300, (ulong)Fx.fx_transition_timed_wipe_pos,
  7300, (ulong)Fx.fx_palette_magenta,

  8450, (ulong)Fx.fx_transition_timed_fade,
  8450, (ulong)Fx.fx_palette_dark,

  //Both CrossStep
  9700, (ulong)Fx.fx_transition_timed_fade,
  9700, (ulong)Fx.fx_palette_rb,
  9700, (ulong)Fx.fx_speed_1,
  9700, (ulong)Fx.fx_speed_neg,

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
  14600, (ulong)Fx.fx_transition_fast, //timed_fade,
  14600, (ulong)Fx.fx_palette_magenta,
  14600, (ulong)Fx.fx_speed_0,

  //Build2
  16800, (ulong)Fx.fx_transition_fast, //_timed_fade,
  16800, (ulong)Fx.fx_palette_cm,
  16800, (ulong)Fx.fx_speed_2,
  16800, (ulong)Fx.fx_speed_neg,

  //18600 beat
  /*18600,fx_transition_fast,
    18600,fx_palette_pulse_yellow,

    //Coast2
    19200,fx_transition_timed_fade,
    19200,fx_palette_pulse2_orange,*/

  //BEATS
  19600, (ulong)Fx.fx_transition_timed_wipe_pos,
  19600, (ulong)Fx.fx_palette_red,
  20200, (ulong)Fx.fx_palette_yellow,
  20800, (ulong)Fx.fx_palette_red,
  21400, (ulong)Fx.fx_palette_yellow,
  22000, (ulong)Fx.fx_palette_red,
  22600, (ulong)Fx.fx_palette_yellow,
  23200, (ulong)Fx.fx_palette_white,

  //calm/smooth in down
  24200, (ulong)Fx.fx_transition_timed_wipe_pos,
  24200, (ulong)Fx.fx_palette_red,
  26500, (ulong)Fx.fx_transition_timed_fade,
  26500, (ulong)Fx.fx_palette_db,
  28900, (ulong)Fx.fx_transition_fast,
  28900, (ulong)Fx.fx_palette_half,
  29000, (ulong)Fx.fx_transition_timed_fade,
  29000, (ulong)Fx.fx_palette_dr,

  //29400 beat
  //30400 beat
  //31500 beat
  //32800 beat
  //34000 beat
  //35100 beat
  //36400 beat
  //37600 beat
  29400, (ulong)Fx.fx_transition_timed_fade,
  29400, (ulong)Fx.fx_palette_red,
  29790, (ulong)Fx.fx_palette_green,
  30180, (ulong)Fx.fx_palette_blue,
  30570, (ulong)Fx.fx_palette_red,
  30960, (ulong)Fx.fx_palette_green,
  31350, (ulong)Fx.fx_palette_red,
  31740, (ulong)Fx.fx_palette_green,
  32130, (ulong)Fx.fx_palette_blue,
  32520, (ulong)Fx.fx_palette_red,
  32910, (ulong)Fx.fx_palette_green,
  33300, (ulong)Fx.fx_palette_blue,
  33690, (ulong)Fx.fx_palette_red,
  //33690,fx_transition_fast,
  34080, (ulong)Fx.fx_speed_2,
  34080, (ulong)Fx.fx_speed_neg,
  34080, (ulong)Fx.fx_palette_green,
  34470, (ulong)Fx.fx_palette_gb,
  34860, (ulong)Fx.fx_palette_blue,
  35250, (ulong)Fx.fx_palette_rb,
  35640, (ulong)Fx.fx_palette_red,
  36030, (ulong)Fx.fx_palette_rg,
  36420, (ulong)Fx.fx_palette_green,
  36810, (ulong)Fx.fx_palette_gb,
  37200, (ulong)Fx.fx_palette_blue,
  37590, (ulong)Fx.fx_palette_rb,

  //Paso Spins
  38700, (ulong)Fx.fx_transition_timed_fade,
  38700, (ulong)Fx.fx_palette_red,
  39200, (ulong)Fx.fx_palette_red,

  43300, (ulong)Fx.fx_speed_0,
  43300, (ulong)Fx.fx_speed_neg,
  43300, (ulong)Fx.fx_speed_rst,
  43300, (ulong)Fx.fx_transition_timed_wipe_pos,
  43300, (ulong)Fx.fx_palette_blue,
  47100, (ulong)Fx.fx_transition_timed_fade,
  47100, (ulong)Fx.fx_palette_red,

  50400, (ulong)Fx.fx_transition_timed_fade,
  50400, (ulong)Fx.fx_palette_half,
  53300, (ulong)Fx.fx_transition_timed_fade,
  53300, (ulong)Fx.fx_palette_magenta,

  //coasting orange
  54600, (ulong)Fx.fx_speed_0,
  54600, (ulong)Fx.fx_speed_pos,
  54600, (ulong)Fx.fx_transition_timed_fade,
  54600, (ulong)Fx.fx_palette_blue,

  57800, (ulong)Fx.fx_transition_timed_fade,
  57800, (ulong)Fx.fx_palette_pulse_dark,

  60000, (ulong)Fx.fx_speed_3,
  60000, (ulong)Fx.fx_speed_neg,
  60000, (ulong)Fx.fx_transition_timed_fade,
  60000, (ulong)Fx.fx_palette_pulse_magenta,

  //CHAPTER 2
  72000, (ulong)Fx.fx_speed_0,
  72000, (ulong)Fx.fx_speed_pos,
  72000, (ulong)Fx.fx_transition_timed_fade,
  72000, (ulong)Fx.fx_palette_magenta,

  //descents
  73000, (ulong)Fx.fx_transition_timed_wipe_pos,
  73000, (ulong)Fx.fx_palette_cyan,
  74000, (ulong)Fx.fx_transition_timed_wipe_pos,
  74000, (ulong)Fx.fx_palette_magenta,
  75000, (ulong)Fx.fx_transition_timed_wipe_pos,
  75000, (ulong)Fx.fx_palette_cyan,
  76000, (ulong)Fx.fx_transition_timed_wipe_pos,
  76000, (ulong)Fx.fx_palette_magenta,
  77000, (ulong)Fx.fx_transition_timed_wipe_pos,
  77000, (ulong)Fx.fx_palette_cyan,
  78000, (ulong)Fx.fx_transition_timed_wipe_pos,
  78000, (ulong)Fx.fx_palette_magenta,
  79000, (ulong)Fx.fx_transition_timed_wipe_pos,
  79000, (ulong)Fx.fx_palette_cyan,
  80000, (ulong)Fx.fx_transition_timed_wipe_pos,
  80000, (ulong)Fx.fx_palette_magenta,

  //  80400,fx_transition_timed_fade,
  //  80400,fx_palette_magenta,
  ///bwaaah
  81800, (ulong)Fx.fx_speed_2,
  81800, (ulong)Fx.fx_speed_neg,
  81800, (ulong)Fx.fx_transition_timed_fade,
  81800, (ulong)Fx.fx_palette_red,
  82800, (ulong)Fx.fx_transition_timed_fade,
  82800, (ulong)Fx.fx_palette_red,
  //end of bwaah

  88000, (ulong)Fx.fx_transition_timed_fade,
  88000, (ulong)Fx.fx_palette_rb,

  94000, (ulong)Fx.fx_transition_timed_fade,
  94000, (ulong)Fx.fx_palette_blue,
  94000, (ulong)Fx.fx_transition_fast,
  94000, (ulong)Fx.fx_palette_half,
  94000, (ulong)Fx.fx_transition_timed_fade,
  94000, (ulong)Fx.fx_palette_dark,

  //98 to 107 = the spin and recover

  //pulsy approach
  /*98500,fx_speed_3,
    98500,fx_speed_pos,
    98500,fx_transition_timed_fade,
    98500,fx_palette_pulse_white,*/
  //imu approach
  98500, (ulong)Fx.fx_speed_2,
  98500, (ulong)Fx.fx_speed_neg,
  98500, (ulong)Fx.fx_transition_timed_fade,
  98500, (ulong)Fx.fx_palette_pulse_magenta,

  104000, (ulong)Fx.fx_speed_2,
  104000, (ulong)Fx.fx_speed_neg,
  104000, (ulong)Fx.fx_transition_timed_fade,
  104000, (ulong)Fx.fx_palette_pulse_white,

  //CHAPTER 3
  //big march around
  107900, (ulong)Fx.fx_speed_0,
  107900, (ulong)Fx.fx_speed_pos,
  107900, (ulong)Fx.fx_transition_timed_fade,
  107900, (ulong)Fx.fx_palette_half,

  110000, (ulong)Fx.fx_transition_timed_fade,
  110000, (ulong)Fx.fx_palette_half,

  111000, (ulong)Fx.fx_transition_timed_fade,
  111000, (ulong)Fx.fx_palette_half,

  111000, (ulong)Fx.fx_speed_1,
  111000, (ulong)Fx.fx_speed_neg,
  111000, (ulong)Fx.fx_transition_timed_fade,
  111000, (ulong)Fx.fx_palette_cyan,
  118000, (ulong)Fx.fx_transition_timed_fade,
  118000, (ulong)Fx.fx_palette_magenta,
  119000, (ulong)Fx.fx_transition_timed_fade,
  119000, (ulong)Fx.fx_palette_red,
  119500, (ulong)Fx.fx_transition_timed_fade,
  119500, (ulong)Fx.fx_palette_blue,
  120000, (ulong)Fx.fx_transition_timed_fade,
  120000, (ulong)Fx.fx_palette_red,
  120500, (ulong)Fx.fx_transition_timed_fade,
  120500, (ulong)Fx.fx_palette_blue,
  121000, (ulong)Fx.fx_speed_neg,
  121000, (ulong)Fx.fx_speed_4,
  121000, (ulong)Fx.fx_transition_timed_fade,
  121000, (ulong)Fx.fx_palette_pulse2_white,
  121500, (ulong)Fx.fx_transition_timed_fade,
  121500, (ulong)Fx.fx_palette_pulse2_white,

  122100, (ulong)Fx.fx_speed_8,
  122100, (ulong)Fx.fx_transition_fast,
  122100, (ulong)Fx.fx_palette_pulse2_red,
  122200, (ulong)Fx.fx_palette_pulse2_yellow,
  122300, (ulong)Fx.fx_palette_pulse2_green,
  122400, (ulong)Fx.fx_palette_pulse2_cyan,
  122500, (ulong)Fx.fx_palette_pulse2_blue,
  122600, (ulong)Fx.fx_palette_pulse2_magenta,
  122700, (ulong)Fx.fx_palette_pulse2_white,
  122800, (ulong)Fx.fx_transition_fast,
  122800, (ulong)Fx.fx_palette_rainbow,

  124500, (ulong)Fx.fx_speed_16,
  124500, (ulong)Fx.fx_transition_fast,
  124500, (ulong)Fx.fx_palette_rainbow,

  125000, (ulong)Fx.fx_transition_timed_fade,
  125000, (ulong)Fx.fx_palette_white,
  126000, (ulong)Fx.fx_transition_timed_fade,
  126000, (ulong)Fx.fx_palette_dark,

  //the end
  127000, (ulong)Fx.fx_transition_timed_fade,
  127000, (ulong)Fx.fx_palette_dark,
  129000, (ulong)Fx.fx_transition_timed_fade,
  129000, (ulong)Fx.fx_palette_dark
        };
        

        public static void Decode(byte[] pixels)
        {
            byte r1, g1, b1;
            r1 = g1 = b1 = 0;
            byte r2, g2, b2;
            r2 = g2 = b2 = 0;
            ulong last = 0;

            for (int t = 0; t < track.Count/2-2; t+=2)
            {
                ulong tc = track[t * 2 + 0];
                Fx fx = (Fx)track[t * 2 + 1];

                if ( tc > last)
                {
                    for (ulong tx = last / 100; tx < tc / 100; tx++)
                    {
                        int plotX = (int)tx;
                        for (int y = 0; y < 4; y++)
                        {
                            pixels[y * 1300 * 4 + plotX * 4 + 0] = (byte)(b1 / 2);
                            pixels[y * 1300 * 4 + plotX * 4 + 1] = (byte)(g1 / 2);
                            pixels[y * 1300 * 4 + plotX * 4 + 2] = (byte)(r1 / 2);
                            pixels[y * 1300 * 4 + plotX * 4 + 3] = 127;
                        }
                        for (int y = 4; y < 8; y++)
                        {
                            pixels[y * 1300 * 4 + plotX * 4 + 0] = (byte)(b2 / 2);
                            pixels[y * 1300 * 4 + plotX * 4 + 1] = (byte)(g2 / 2);
                            pixels[y * 1300 * 4 + plotX * 4 + 2] = (byte)(r2 / 2);
                            pixels[y * 1300 * 4 + plotX * 4 + 3] = 127;
                        }
                    }
                    last = tc;
                }

                if (fx >= Fx.fx_palette_dark && fx <= Fx.fx_palette_lowhalf)
                {
                    switch (fx)
                    {
                        case Fx.fx_palette_dark: { r1 = 0; g1 = 0; } break;
                        case Fx.fx_palette_white: { r1 = g1 = b1 = 255; } break;
                        case Fx.fx_palette_red: { r1 = 255; g1 = 0; b1 = 0; } break;
                        case Fx.fx_palette_yellow: { r1 = 255; g1 = 255; b1 = 0; } break;
                        case Fx.fx_palette_green: { r1 = 0; g1 = 255; b1 = 0; } break;
                        case Fx.fx_palette_cyan: { r1 = 0; g1 = 255; b1 = 255; } break;
                        case Fx.fx_palette_blue: { r1 = 0; g1 = 0; b1 = 255; } break;
                        case Fx.fx_palette_magenta: { r1 = 255; g1 = 0; b1 = 255; } break;
                        case Fx.fx_palette_orange: { r1 = 255; g1 = 127; b1 = 0; } break;
                        case Fx.fx_palette_half: { r1 = 127; g1 = 127; b1 = 127; } break;
                        case Fx.fx_palette_lowhalf: { r1 = 63; g1 = 63; b1 = 63; } break;
                    }
                    r2 = r1;
                    g2 = g1;
                    b2 = b1;
                }
                if (fx >= Fx.fx_palette_dr && fx <= Fx.fx_palette_dbm)
                {
                    switch (fx)
                    {
                        case Fx.fx_palette_rb: { r1 = 255; g1 = 0;  r2 = 0; g2 = 0; b2 = 0; } break;
                        case Fx.fx_palette_cm: { r1 = g1 = 255; b1 = 255; r2 = 255; g2 = 0; b2 = 255; } break;
                        case Fx.fx_palette_rm: { r1 = 255; g1 = 0; b1 = 255; r2 = 255; g2 = 0; b2 = 255; } break;
                    }
                }
                if (fx >= Fx.fx_palette_pulse_dark && fx <= Fx.fx_palette_pulse_lowhalf)
                {
                    switch (fx)
                    {
                        case Fx.fx_palette_pulse_dark: { r1 = 0; g1 = 0; } break;
                        case Fx.fx_palette_pulse_white: { r1 = g1 = b1 = 255; } break;
                        case Fx.fx_palette_pulse_red: { r1 = 255; g1 = 0; b1 = 0; } break;
                        case Fx.fx_palette_pulse_yellow: { r1 = 255; g1 = 255; b1 = 0; } break;
                        case Fx.fx_palette_pulse_green: { r1 = 0; g1 = 255; b1 = 0; } break;
                        case Fx.fx_palette_pulse_cyan: { r1 = 0; g1 = 255; b1 = 255; } break;
                        case Fx.fx_palette_pulse_blue: { r1 = 0; g1 = 0; b1 = 255; } break;
                        case Fx.fx_palette_pulse_magenta: { r1 = 255; g1 = 0; b1 = 255; } break;
                        case Fx.fx_palette_pulse_orange: { r1 = 255; g1 = 127; b1 = 0; } break;
                        case Fx.fx_palette_pulse_half: { r1 = 127; g1 = 127; b1 = 127; } break;
                        case Fx.fx_palette_pulse_lowhalf: { r1 = 63; g1 = 63; b1 = 63; } break;
                    }
                    r2 = 0;
                    g2 = 0;
                    b2 = 0;
                }
                if (fx >= Fx.fx_palette_pulse2_dark && fx <= Fx.fx_palette_pulse2_lowhalf)
                {
                    switch (fx)
                    {
                        case Fx.fx_palette_pulse2_dark: { r1 = 0; g1 = 0; } break;
                        case Fx.fx_palette_pulse2_white: { r1 = g1 = b1 = 255; } break;
                        case Fx.fx_palette_pulse2_red: { r1 = 255; g1 = 0; b1 = 0; } break;
                        case Fx.fx_palette_pulse2_yellow: { r1 = 255; g1 = 255; b1 = 0; } break;
                        case Fx.fx_palette_pulse2_green: { r1 = 0; g1 = 255; b1 = 0; } break;
                        case Fx.fx_palette_pulse2_cyan: { r1 = 0; g1 = 255; b1 = 255; } break;
                        case Fx.fx_palette_pulse2_blue: { r1 = 0; g1 = 0; b1 = 255; } break;
                        case Fx.fx_palette_pulse2_magenta: { r1 = 255; g1 = 0; b1 = 255; } break;
                        case Fx.fx_palette_pulse2_orange: { r1 = 255; g1 = 127; b1 = 0; } break;
                        case Fx.fx_palette_pulse2_half: { r1 = 127; g1 = 127; b1 = 127; } break;
                        case Fx.fx_palette_pulse2_lowhalf: { r1 = 63; g1 = 63; b1 = 63; } break;
                    }
                    r2 = 0;
                    g2 = 0;
                    b2 = 0;
                }
            }
        }
    }
}
