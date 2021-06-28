#ifndef _PZEM004_SENSOR_H_
#define _PZEM004_SENSOR_H_

#include "sensors/Sensor.h"

class PZEM004Sensor : public Sensor
{
private:
  /* data */
public:
  PZEM004Sensor(/* args */);
  virtual ~PZEM004Sensor();

public:
  virtual void setup();
  virtual void loop();
  virtual void loop(JsonObject& doc);
};

#endif
