#ifndef _PZEM004t_SENSOR_H_
#define _PZEM004t_SENSOR_H_

#include "sensors/Sensor.h"

class PZEM004tSensor : public Sensor
{
private:
  /* data */
public:
  PZEM004tSensor(/* args */);
  virtual ~PZEM004tSensor();

public:
  virtual void setup();
  virtual void loop();
  virtual void loop(JsonObject& doc);
};

#endif
