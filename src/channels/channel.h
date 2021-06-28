#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "definitions/constants.h"
#include "definitions/functions.h"
#include "definitions/types.h"
#include "definitions/protocols.h"
#include "filesystem/filesystem.h"

#include "sensors/Sensor.h"

class Channel
{
private:
  uint8_t ch;
  uint8_t pin;
  // uint64_t dev;

  SensorType type;
  ProtocolType ptl;

  String id = "";

  Sensor* sensor;
  
public:
  Channel();
  // Channel(String id, uint8_t ch, uint8_t pin, /*uint64_t dev,*/ SensorType type, ProtocolType ptl);
  virtual ~Channel();

public:
  // void setChannel(uint8_t ch);
  // void setPin(uint8_t pin);
  // void setDev(uint64_t);
  // void setType(SensorType type);
  // void setProtocol(ProtocolType ptl);
  // void setId(String id);


public:
  void setup(String id, uint8_t ch, uint8_t pin, SensorType type, ProtocolType ptl = ProtocolType::PROTOCOL_TYPE_NONE);
  void loop();
  void loop(JsonArray& array);

};

#endif
