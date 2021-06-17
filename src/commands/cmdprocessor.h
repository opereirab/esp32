#ifndef _CMDPROCESSOR_H_
#define _CMDPROCESSOR_H_

#define ARDUINOJSON_USE_LONG_LONG 1
#include <Arduino.h>

class CmdProcessor
{
private:
  /* data */
public:
  CmdProcessor(/* args */);
  virtual ~CmdProcessor();

public:
  String process(const String& payload, size_t length);

};

extern CmdProcessor cmdprocessor;

#endif
