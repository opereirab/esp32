#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "definitions/constants.h"
#include "definitions/functions.h"
#include "definitions/types.h"
#include "definitions/protocols.h"
#include "filesystem/filesystem.h"

#include <ArduinoJson.h>

class Channel
{
public:
  uint8_t ch;
  uint8_t pin;
  uint64_t dev;

  SensorType type;
  ProtocolType ptl;

  String id = "";
  
public:
  Channel(/* args */);
  virtual ~Channel();

public:
  virtual void setup() {} /*= 0*/;
  virtual void loop() {} /*= 0*/;

};

#endif
