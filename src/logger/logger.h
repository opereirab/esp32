#ifndef _LOGGER_H_
#define _LOGGER_H_

class Logger
{
private:
  /* data */
public:
  Logger(/* args */);
  ~Logger();

public:
  static void log(const char* message);

};


#endif
