#include "logger.h"
#include "clock/systemclock.h"

Logger::Logger(/* args */)
{
}

Logger::~Logger()
{
}

void Logger::log(const char* message)
{
  Serial.printf("[%s] %s\n", systemclock.getTime().c_str(), message);
}
