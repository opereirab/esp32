#include "systemclock.h"

#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire rtcWire(25, 26, 27); // IO, SCLK, CE
RtcDS1302<ThreeWire> hardRtc(rtcWire);
#define countof(a) (sizeof(a) / sizeof(a[0]))

SystemClock systemclock;

SystemClock::SystemClock(/* args */)
{  
}

SystemClock::~SystemClock()
{
}

void SystemClock::printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

  snprintf_P(datestring, 
    countof(datestring),
    PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
    dt.Day(),
    dt.Month(),
    dt.Year(),
    dt.Hour(),
    dt.Minute(),
    dt.Second());
  Serial.println(datestring);
}

String SystemClock::getTime()
{
  RtcDateTime hardNow = hardRtc.GetDateTime();
  if (hardNow.IsValid())
  {
    char datestring[20];

    snprintf_P(datestring, 
      countof(datestring),
      PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
      hardNow.Day(),
      hardNow.Month(),
      hardNow.Year(),
      hardNow.Hour(),
      hardNow.Minute(),
      hardNow.Second());

    return String(datestring);
  }
  Serial.println("RTC lost confidence in the DateTime!");
  return softRtc.getTime("%d/%m/%Y %H:%M:%S");
}

String SystemClock::getCompilationTime() {
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

  char datestring[20];

  snprintf_P(datestring, 
    countof(datestring),
    PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
    compiled.Day(),
    compiled.Month(),
    compiled.Year(),
    compiled.Hour(),
    compiled.Minute(),
    compiled.Second()
  );

  return String(datestring);
}

uint64_t SystemClock::Epoch64Time() {
  RtcDateTime hardNow = hardRtc.GetDateTime();
  if(hardNow.IsValid()) {
    return hardNow.Epoch64Time();
  }
  return softRtc.getEpoch();
}

void SystemClock::setDateTime(uint64_t time)
{
  RtcDateTime compiled;
  compiled.InitWithEpoch64Time(time);
  hardRtc.SetDateTime(compiled);
  softRtc.setTime(compiled.Epoch64Time());
}

void SystemClock::setup()
{
  softRtc.getEpoch();

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  hardRtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
	printDateTime(compiled);
	Serial.println();

	if (!hardRtc.IsDateTimeValid()) 
	{
		// Common Causes:
		//    1) first time you ran and the device wasn't running yet
		//    2) the battery on the device is low or even missing

		Serial.println("RTC lost confidence in the DateTime!");
		hardRtc.SetDateTime(compiled);
	}

	if (hardRtc.GetIsWriteProtected())
	{
		Serial.println("RTC was write protected, enabling writing now");
		hardRtc.SetIsWriteProtected(false);
	}

	if (!hardRtc.GetIsRunning())
	{
		Serial.println("RTC was not actively running, starting now");
		hardRtc.SetIsRunning(true);
	}

  RtcDateTime now = hardRtc.GetDateTime();  
  softRtc.setTime(now.Epoch64Time());
	if (now < compiled) 
	{
		Serial.println("RTC is older than compile time!  (Updating DateTime)");
		hardRtc.SetDateTime(compiled);
    softRtc.setTime(compiled.Epoch64Time());
	}
	else if (now > compiled) 
	{
		Serial.println("RTC is newer than compile time. (this is expected)");
	}
	else if (now == compiled) 
	{
		Serial.println("RTC is the same as compile time! (not expected but all is fine)");
	}
}

void SystemClock::loop()
{
  RtcDateTime hardNow = hardRtc.GetDateTime();
  String softNow = softRtc.getTime("%d/%m/%Y %H:%M:%S");
  Serial.println("Soft Clock: " + softNow);
  Serial.print("Hard Clock: ");  
  printDateTime(hardNow);

  Serial.println(hardNow.Epoch64Time());
  Serial.println(softRtc.getEpoch());
  if (!hardNow.IsValid())
  {
    // Common Causes:
    //    1) the battery on the device is low or even missing and the power line was disconnected
    Serial.println("RTC lost confidence in the DateTime!");
  }
}
