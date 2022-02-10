using System;
using System.Collections.Generic;
using System.Text;

namespace KataTracks
{
    //List of possible Fx events
    enum FxEvent
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

        fx_transition_fast = 30,
        fx_transition_timed_fade = 31,
        fx_transition_timed_wipe_pos = 32,
        fx_transition_timed_wipe_neg = 33,

        fx_palette_lead = 40,
        fx_palette_follow = 41,

        fx_track_begin = 50,
        fx_track_stop = 51,

        fx_palette_lava = 91,
        fx_palette_cloud = 92,
        fx_palette_ocean = 93,
        fx_palette_forest = 94,
        fx_palette_rainbow = 95,
        fx_palette_rainbowstripe = 96,
        fx_palette_party = 97,
        fx_palette_heat = 98,

        fx_palette_dark = 101,
        fx_palette_white = 102,
        fx_palette_red = 103,
        fx_palette_yellow = 104,
        fx_palette_green = 105,
        fx_palette_cyan = 106,
        fx_palette_blue = 107,
        fx_palette_magenta = 108,
        fx_palette_orange = 109,

        fx_palette_dw = 119,
        fx_palette_dr = 120,
        fx_palette_dy = 121,
        fx_palette_dg = 122,
        fx_palette_dc = 123,
        fx_palette_db = 124,
        fx_palette_dm = 125,
        fx_palette_wr = 130,
        fx_palette_wy = 131,
        fx_palette_wg = 132,
        fx_palette_wc = 133,
        fx_palette_wb = 134,
        fx_palette_wm = 135,
        fx_palette_ry = 141,
        fx_palette_rg = 142,
        fx_palette_rc = 143,
        fx_palette_rb = 144,
        fx_palette_rm = 145,
        fx_palette_yg = 152,
        fx_palette_yc = 153,
        fx_palette_yb = 154,
        fx_palette_ym = 155,
        fx_palette_gc = 163,
        fx_palette_gb = 164,
        fx_palette_gm = 165,
        fx_palette_cb = 174,
        fx_palette_cm = 175,
        fx_palette_bm = 185,

        fx_palette_wry = 201,
        fx_palette_wrg = 202,
        fx_palette_wrc = 203,
        fx_palette_wrb = 204,
        fx_palette_wrm = 205,
        fx_palette_wyg = 206,
        fx_palette_wyc = 207,
        fx_palette_wyb = 208,
        fx_palette_wym = 209,
        fx_palette_wgc = 210,
        fx_palette_wgb = 211,
        fx_palette_wgm = 212,
        fx_palette_wcb = 213,
        fx_palette_wcm = 214,
        fx_palette_wbm = 215,

        fx_palette_dry = 221,
        fx_palette_drg = 222,
        fx_palette_drc = 223,
        fx_palette_drb = 224,
        fx_palette_drm = 225,
        fx_palette_dyg = 226,
        fx_palette_dyc = 227,
        fx_palette_dyb = 228,
        fx_palette_dym = 229,
        fx_palette_dgc = 230,
        fx_palette_dgb = 231,
        fx_palette_dgm = 232,
        fx_palette_dcb = 233,
        fx_palette_dcm = 234,
        fx_palette_dbm = 235,

        fx_palette_rgb = 240,
        fx_palette_cmy = 241,

        fx_nothing = 255
    };

    class MainTrack
    {
        public static ulong[] SongTrack =
{
    //Basic setup, fade in to blue
      1,(ulong)FxEvent.fx_palette_dark,
      1,(ulong)FxEvent.fx_speed_0,
      1,(ulong)FxEvent.fx_speed_pos,
  
    //Lead CrossStep
      2500,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      2500,(ulong)FxEvent.fx_palette_blue,
    //Follow CrossStep
      4800,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      4800,(ulong)FxEvent.fx_palette_red,
    //Lead CrossStep
      7300,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      7300,(ulong)FxEvent.fx_palette_blue,
    //Follow CrossStep
      9700,(ulong)FxEvent.fx_transition_timed_fade,
      9700,(ulong)FxEvent.fx_palette_rb,

    //March together
    //Arms up
  
    //Circles around each other
      14400,(ulong)FxEvent.fx_transition_timed_fade,
      14400,(ulong)FxEvent.fx_palette_magenta,

    //Build2
      16800,(ulong)FxEvent.fx_transition_timed_fade,
      16800,(ulong)FxEvent.fx_palette_rb,

    //Coast2
      19200,(ulong)FxEvent.fx_transition_timed_fade,
      19200,(ulong)FxEvent.fx_palette_cyan,

      24200,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      24200,(ulong)FxEvent.fx_palette_white,
      26500,(ulong)FxEvent.fx_transition_timed_fade,
      26500,(ulong)FxEvent.fx_palette_db,
      28900,(ulong)FxEvent.fx_transition_timed_fade,
      28900,(ulong)FxEvent.fx_palette_dr,

      //Paso Spins
      38700,(ulong)FxEvent.fx_transition_timed_fade,
      38700,(ulong)FxEvent.fx_palette_red,
      /*39000,(ulong)FxEvent.fx_transition_timed_fade,
      39000,(ulong)FxEvent.fx_transition_timed_fade,
      39000,(ulong)FxEvent.fx_palette_cyan,
      39300,(ulong)FxEvent.fx_transition_timed_fade,
      39300,(ulong)FxEvent.fx_palette_red,
      39500,(ulong)FxEvent.fx_transition_timed_fade,
      39500,(ulong)FxEvent.fx_palette_cyan,
      39900,(ulong)FxEvent.fx_transition_timed_fade,
      39900,(ulong)FxEvent.fx_palette_red,*/

      43300,(ulong)FxEvent.fx_transition_timed_fade,
      43300,(ulong)FxEvent.fx_palette_yellow,
      /*43600,(ulong)FxEvent.fx_transition_timed_fade,
      43600,(ulong)FxEvent.fx_palette_cyan,
      43900,(ulong)FxEvent.fx_transition_timed_fade,
      43900,(ulong)FxEvent.fx_palette_yellow,
    */
      47100,(ulong)FxEvent.fx_transition_timed_fade,
      47100,(ulong)FxEvent.fx_palette_green,

      50400,(ulong)FxEvent.fx_transition_timed_fade,
      50400,(ulong)FxEvent.fx_palette_ocean,
      53300,(ulong)FxEvent.fx_transition_timed_fade,
      53300,(ulong)FxEvent.fx_palette_magenta,
  
      //coasting orange 
      54600,(ulong)FxEvent.fx_speed_1,
      54600,(ulong)FxEvent.fx_transition_timed_fade,
      54600,(ulong)FxEvent.fx_palette_heat,

      60000,(ulong)FxEvent.fx_palette_heat,
    //CHAPTER 2
    /*
      60000,(ulong)FxEvent.fx_transition_timed_fade,
      60000,(ulong)FxEvent.fx_palette_cyan,
      62500,(ulong)FxEvent.fx_transition_timed_fade,
      62500,(ulong)FxEvent.fx_palette_magenta,
      64800,(ulong)FxEvent.fx_transition_timed_fade,
      64800,(ulong)FxEvent.fx_palette_cyan,
      67500,(ulong)FxEvent.fx_transition_timed_fade,
      67500,(ulong)FxEvent.fx_palette_magenta,
      70000,(ulong)FxEvent.fx_transition_timed_fade,
      70000,(ulong)FxEvent.fx_palette_cyan,*/
      72700,(ulong)FxEvent.fx_speed_0,

    //descents
      72700,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      72700,(ulong)FxEvent.fx_palette_blue,
      74300,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      74300,(ulong)FxEvent.fx_palette_red,
      75900,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      75900,(ulong)FxEvent.fx_palette_blue,
      77200,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      77200,(ulong)FxEvent.fx_palette_red,
      78800,(ulong)FxEvent.fx_transition_timed_wipe_pos,
      78800,(ulong)FxEvent.fx_palette_blue,

      80400,(ulong)FxEvent.fx_transition_timed_fade,
      80400,(ulong)FxEvent.fx_palette_yellow,
      81800,(ulong)FxEvent.fx_transition_timed_fade,
      81800,(ulong)FxEvent.fx_palette_white,

      99000,(ulong)FxEvent.fx_transition_timed_fade,
      99000,(ulong)FxEvent.fx_palette_red,

    //CHAPTER 3
      108900,(ulong)FxEvent.fx_transition_timed_fade,
      108900,(ulong)FxEvent.fx_palette_cyan,

      125000,(ulong)FxEvent.fx_transition_timed_fade,
      125000,(ulong)FxEvent.fx_palette_dark,
      //the end
      127000,(ulong)FxEvent.fx_palette_dark,

      327000,(ulong)FxEvent.fx_nothing
    };

    }


    class Fx 
    {
        public ulong _timecode = 0;
        public ulong _event = 0;

        public static String FxEventName(FxEvent e)
        {
            switch (e)
            {
                case FxEvent.fx_speed_0: return "x0"; 
                case FxEvent.fx_speed_1: return "x1"; 
                case FxEvent.fx_speed_2: return "x2"; 
                case FxEvent.fx_speed_3: return "x3"; 
                case FxEvent.fx_speed_4: return "x4"; 
                case FxEvent.fx_speed_5: return "x5"; 
                case FxEvent.fx_speed_6: return "x6"; 
                case FxEvent.fx_speed_7: return "x7"; 
                case FxEvent.fx_speed_8: return "x8"; 
                case FxEvent.fx_speed_9: return "x9"; 
                case FxEvent.fx_speed_10: return "x10"; 
                case FxEvent.fx_speed_11: return "x11"; 
                case FxEvent.fx_speed_12: return "x12"; 
                case FxEvent.fx_speed_13: return "x13"; 
                case FxEvent.fx_speed_14: return "x14"; 
                case FxEvent.fx_speed_15: return "x15"; 
                case FxEvent.fx_speed_16: return "x16"; 
                case FxEvent.fx_speed_17: return "x17"; 
                case FxEvent.fx_speed_18: return "x18"; 
                case FxEvent.fx_speed_32: return "x32"; 

                case FxEvent.fx_speed_pos: return "speed pos"; 
                case FxEvent.fx_speed_neg: return "speed neg"; 
                case FxEvent.fx_speed_inc: return "speed inc"; 
                case FxEvent.fx_speed_dec: return "speed dec"; 

                case FxEvent.fx_transition_fast: return "t-fast";
                case FxEvent.fx_transition_timed_fade: return "t-timed-fade"; 
                case FxEvent.fx_transition_timed_wipe_pos: return "t-timed-wipe-pos";
                case FxEvent.fx_transition_timed_wipe_neg: return "t-timed-wipe-neg";

                case FxEvent.fx_palette_lead: return "lead"; 
                case FxEvent.fx_palette_follow: return "follow"; 

                case FxEvent.fx_palette_lava: return "lava"; 
                case FxEvent.fx_palette_cloud: return "cloud";
                case FxEvent.fx_palette_ocean: return "ocean";
                case FxEvent.fx_palette_forest: return "forest";
                case FxEvent.fx_palette_rainbow: return "rainbow";
                case FxEvent.fx_palette_rainbowstripe: return "rainbowstripe";
                case FxEvent.fx_palette_party: return "party"; 
                case FxEvent.fx_palette_heat: return "heat";
                     
                case FxEvent.fx_palette_dark: return "dark"; 
                case FxEvent.fx_palette_white: return "white"; 
                case FxEvent.fx_palette_red: return "red"; 
                case FxEvent.fx_palette_yellow: return "yellow"; 
                case FxEvent.fx_palette_green: return "green"; 
                case FxEvent.fx_palette_cyan: return "cyan"; 
                case FxEvent.fx_palette_blue: return "blue"; 
                case FxEvent.fx_palette_magenta: return "magenta";
                case FxEvent.fx_palette_orange: return "orange"; 
                     
                case FxEvent.fx_palette_dw: return "dark-white"; 
                case FxEvent.fx_palette_dr: return "dark-red"; 
                case FxEvent.fx_palette_dy: return "dark-yellow"; 
                case FxEvent.fx_palette_dg: return "dark-green"; 
                case FxEvent.fx_palette_dc: return "dark-cyan"; 
                case FxEvent.fx_palette_db: return "dark-blue"; 
                case FxEvent.fx_palette_dm: return "dark-magenta"; 
                case FxEvent.fx_palette_wr: return "white-red"; 
                case FxEvent.fx_palette_wy: return "white-yellow"; 
                case FxEvent.fx_palette_wg: return "white-green"; 
                case FxEvent.fx_palette_wc: return "white-cyan"; 
                case FxEvent.fx_palette_wb: return "white-blue"; 
                case FxEvent.fx_palette_wm: return "white-magenta";
                case FxEvent.fx_palette_ry: return "red-yellow";
                case FxEvent.fx_palette_rg: return "red-green"; 
                case FxEvent.fx_palette_rc: return "red-cyan"; 
                case FxEvent.fx_palette_rb: return "red-blue"; 
                case FxEvent.fx_palette_rm: return "red-magenta"; 
                case FxEvent.fx_palette_yg: return "yellow-green"; 
                case FxEvent.fx_palette_yc: return "yellow-cyan"; 
                case FxEvent.fx_palette_yb: return "yellow-blue"; 
                case FxEvent.fx_palette_ym: return "yellow-magenta";
                case FxEvent.fx_palette_gc: return "green-cyan"; 
                case FxEvent.fx_palette_gb: return "green-blue"; 
                case FxEvent.fx_palette_gm: return "green-magenta";
                case FxEvent.fx_palette_cb: return "cyan-blue"; 
                case FxEvent.fx_palette_cm: return "cyan-magenta"; 
                case FxEvent.fx_palette_bm: return "blue-magenta"; 
                     
                case FxEvent.fx_palette_wry: return "wry";
                case FxEvent.fx_palette_wrg: return "wrg";
                case FxEvent.fx_palette_wrc: return "wrc";
                case FxEvent.fx_palette_wrb: return "wrb";
                case FxEvent.fx_palette_wrm: return "wrm";
                case FxEvent.fx_palette_wyg: return "wyg";
                case FxEvent.fx_palette_wyc: return "wyc";
                case FxEvent.fx_palette_wyb: return "wyb";
                case FxEvent.fx_palette_wym: return "wym";
                case FxEvent.fx_palette_wgc: return "wgc";
                case FxEvent.fx_palette_wgb: return "wgb";
                case FxEvent.fx_palette_wgm: return "wgm";
                case FxEvent.fx_palette_wcb: return "wcb";
                case FxEvent.fx_palette_wcm: return "wcm";
                case FxEvent.fx_palette_wbm: return "wbm";

                case FxEvent.fx_palette_dry: return "dry";
                case FxEvent.fx_palette_drg: return "drg";
                case FxEvent.fx_palette_drc: return "drc";
                case FxEvent.fx_palette_drb: return "drb";
                case FxEvent.fx_palette_drm: return "drm";
                case FxEvent.fx_palette_dyg: return "dyg";
                case FxEvent.fx_palette_dyc: return "dyc";
                case FxEvent.fx_palette_dyb: return "dyb";
                case FxEvent.fx_palette_dym: return "dym";
                case FxEvent.fx_palette_dgc: return "dgc";
                case FxEvent.fx_palette_dgb: return "dgb";
                case FxEvent.fx_palette_dgm: return "dgm";
                case FxEvent.fx_palette_dcb: return "dcb";
                case FxEvent.fx_palette_dcm: return "dcm";
                case FxEvent.fx_palette_dbm: return "dbm";
                     
                case FxEvent.fx_palette_rgb: return "dgb";
                case FxEvent.fx_palette_cmy: return "cmy";
                     
                case FxEvent.fx_nothing: return "nothing";
            }
            return "unk";
        }

        public static string Get()
        {
            int count = 0;
            string str = "";
            while (MainTrack.SongTrack[count*2+1] != (ulong)FxEvent.fx_nothing)
            {
                ulong ms = MainTrack.SongTrack[count * 2 + 0];
                ulong evt = MainTrack.SongTrack[count * 2 + 1];
                str += ms + " : " + FxEventName((FxEvent)evt) + "\n";
                count++;
            }
            return str;
        }
    };


}
