#include "Timecode.h"
static TimeCode timeController;
#include <avr/pgmspace.h> 

void setTimecodeLastMatched(unsigned long match)
{
  timeController.lastMatchedTimecode = match;
}

unsigned long getTimecodeLastMatched()
{
  return timeController.lastMatchedTimecode;
}

signed long getTimecodeTimeOffset()
{
  return timeController.timeOffset;
}

signed long getTimecodeSongOffset()
{
  return timeController.songOffset;
}

signed long setTimecodeTimeOffset(signed long tc)
{
  timeController.timeOffset = tc;  
}

signed long setTimecodeSongOffset(signed long tc)
{
  timeController.songOffset = tc;  
}


  