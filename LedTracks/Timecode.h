#if !defined TIMECODE_DEF
#define TIMECODE_DEF
#include <avr/pgmspace.h> 

struct TimeCode
{
 signed long timeOffset = 0;
 signed long songOffset = 0;
 unsigned long lastMatchedTimecode = 0;
};

signed long getTimecodeTimeOffset();
signed long getTimecodeSongOffset();

signed long setTimecodeTimeOffset(signed long tc);
signed long setTimecodeSongOffset(signed long tc);

void setTimecodeLastMatched(unsigned long match);
unsigned long getTimecodeLastMatched();

#endif
