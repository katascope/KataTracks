#ifndef STATUS_DEF
#define STATUS_DEF

#include "Config.h"

#if ENABLE_STATUS
struct FxController;
void FxDisplayStatus(FxController &fxc);
#endif

#endif
