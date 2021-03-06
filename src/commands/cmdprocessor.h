#ifndef _CMDPROCESSOR_H_
#define _CMDPROCESSOR_H_

#include "definitions/constants.h"

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
