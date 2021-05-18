#include "systemclock.h"

SystemClock systemclock;

SystemClock::SystemClock(/* args */)
{  
}

SystemClock::~SystemClock()
{
}

String SystemClock::getTime()
{
  return rtc.getTime("%d/%m/%Y %H:%M:%S");
}
