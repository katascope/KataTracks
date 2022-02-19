#include "Log.h"
#include "Config.h"

void PrintLog(String str)
{
  Serial.print(str);
#if ENABLE_BLUETOOTH  
  bluetooth.print(str);
#endif  
}

void PrintLogln(String str)
{
  Serial.println(str);
#if ENABLE_BLUETOOTH  
  bluetooth.println(str);
#endif
}
