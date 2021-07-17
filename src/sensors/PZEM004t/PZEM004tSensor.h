#ifndef _PZEM004t_SENSOR_H_
#define _PZEM004t_SENSOR_H_

#include "sensors/Sensor.h"
#include <PZEM004Tv30.h>

#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#endif

#if !defined(PZEM_SERIAL)
#define PZEM_SERIAL Serial2
#endif

class PZEM004tSensor : public Sensor
{
private:
  PZEM004Tv30 pzem;

public:
  PZEM004tSensor(/* args */);
  virtual ~PZEM004tSensor();

public:
  virtual void setup();
  virtual void loop();
  virtual void loop(JsonObject& doc);
};

#endif
