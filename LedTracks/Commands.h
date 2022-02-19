#if !defined USER_COMMAND_DEF
#define USER_COMMAND_DEF

#include "Fx.h"
#include "Log.h"
void SetPalette();
unsigned long GetTime();

enum CaptureTextMode
{
  CaptureNone,
  CaptureColorCode,
  CaptureTimeCode
};


static void DirectEvent(FxController &fxc, int event);
static void magicColors(FxController &fxc, int count, char *colors);
static void processCapturedText(FxController &fxc);

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

void UserCommandExecute(FxController &fxc, int cmd);
void UserCommandInput(FxController &fxc, int data);

void DisplayStatus(FxController &fxc);

#endif
