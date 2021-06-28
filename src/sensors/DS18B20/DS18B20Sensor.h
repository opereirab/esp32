#ifndef _DS18B20_SENSOR_H_
#define _DS18B20_SENSOR_H_

#include "sensors/Sensor.h"

class DS18B20Sensor : public Sensor
{
private:
  /* data */
public:
  DS18B20Sensor(/* args */);
  virtual ~DS18B20Sensor();

public:
  virtual void setup();
  virtual void loop();
  virtual void loop(JsonObject& doc);

};

#endif
