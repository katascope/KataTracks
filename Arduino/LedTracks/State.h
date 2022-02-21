#ifndef STATE_TEST_PATTERN_DEF
#define STATE_TEST_PATTERN_DEF

struct FxController;

void State_Poll_TestPattern(FxController &fxc);
void State_Poll_IMU(FxController &fxc);
void State_Poll_Play(FxController &fxc, unsigned long timecode);

void State_Poll(FxController &fxc);

#endif
