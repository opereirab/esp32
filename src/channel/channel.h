#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "definitions/constants.h"
#include "definitions/types.h"
#include "definitions/protocols.h"
#include "filesystem/filesystem.h"

#include <ArduinoJson.h>

class Channel
{
  public:
    uint8_t ch;
    uint8_t pin;
    uint8_t mul;
    SensorType type;
    ProtocolType ptl;
    uint64_t devId;

    char* id;
    char* name;
    char* ip;
  
  public:
    Channel();
    virtual ~Channel();
};

#endif
