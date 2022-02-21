#ifndef CMD_DEF
#define CMD_DEF
struct FxController;

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

  Cmd_Brightness_VeryHigh,
  Cmd_Brightness_High,
  Cmd_Brightness_Normal,
  Cmd_Brightness_Low,

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

void UserCommandExecute(FxController &fxc, int cmd);
void UserCommandInput(FxController &fxc, int data);

#endif
