#ifndef _SYSTEM_CLOCK_H_
#define _SYSTEM_CLOCK_H_

#include <ESP32Time.h>

class SystemClock
{
private:
  ESP32Time softRtc;  
  
public:
  SystemClock(/* args */);
  virtual ~SystemClock();

private:
  void printDateTime(const class RtcDateTime& dt);

public:
  String getTime();
  String getCompilationTime();
  uint64_t Epoch64Time();
  void setDateTime(uint64_t time);
  
public:
  void setup();
  void loop();
};

extern SystemClock systemclock;

#endif
