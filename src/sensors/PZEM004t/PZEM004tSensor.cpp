#include "PZEM004tSensor.h"

PZEM004tSensor::PZEM004tSensor(/* args */)
  : Sensor()
{
}

PZEM004tSensor::~PZEM004tSensor()
{
}

void PZEM004tSensor::setup()
{
}

void PZEM004tSensor::loop()
{
}

void PZEM004tSensor::loop(JsonObject& doc)
{
  JsonArray values = doc.createNestedArray("values");
  for(int i = 0; i < 7; i++) {
    values.add<float>((float)i + 1.0f);
  }
}
