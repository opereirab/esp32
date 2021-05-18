#ifndef _SYSTEM_CLOCK_H_
#define _SYSTEM_CLOCK_H_

#include <ESP32Time.h>

class SystemClock
{
private:
  ESP32Time rtc;
  
public:
  SystemClock(/* args */);
  virtual ~SystemClock();

public:
  String getTime();

};

extern SystemClock systemclock;

#endif
