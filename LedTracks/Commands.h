#if !defined USER_COMMAND_DEF
#define USER_COMMAND_DEF

enum CaptureTextMode
{
  CaptureNone,
  CaptureColorCode,
  CaptureTimeCode
};

enum UserCommand
{
  Cmd_Unk,
  Cmd_Help,

  Cmd_State_Default,
  Cmd_State_Test,
  Cmd_State_IMU,
  
  Cmd_PlayFromStart,
  Cmd_PlayFrom,
  Cmd_PlayStop,
  
  Cmd_ColorDark,
  Cmd_ColorWhite,
  Cmd_ColorRed,
  Cmd_ColorYellow,
  Cmd_ColorGreen,
  Cmd_ColorCyan,
  Cmd_ColorBlue,
  Cmd_ColorMagenta,
  Cmd_ColorOrange,
  Cmd_ColorHalf,

  Cmd_ColorLava,
  Cmd_ColorCloud,
  Cmd_ColorOcean,
  Cmd_ColorForest,
  Cmd_ColorRainbow,
  Cmd_ColorRainbowstripe,
  Cmd_ColorParty,
  Cmd_ColorHeat,

  Cmd_SpeedNeg,
  Cmd_SpeedPos,
  Cmd_SpeedDec,
  Cmd_SpeedInc,
  Cmd_SpeedRst  
};


#endif
