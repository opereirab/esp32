#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <ArduinoJson.h>

class Sensor
{
private:
  /* data */
public:
  Sensor(/* args */);
  virtual ~Sensor();

public:
  virtual void setup() = 0;
  virtual void loop() = 0;
  virtual void loop(JsonObject& doc) = 0;

};

#endif
