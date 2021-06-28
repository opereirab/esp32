#include "PZEM004Sensor.h"

PZEM004Sensor::PZEM004Sensor(/* args */)
  : Sensor()
{
}

PZEM004Sensor::~PZEM004Sensor()
{
}

void PZEM004Sensor::setup()
{
}

void PZEM004Sensor::loop()
{
}

void PZEM004Sensor::loop(JsonObject& doc)
{
  JsonArray values = doc.createNestedArray("values");
  for(int i = 0; i < 4; i++) {
    values.add<float>((float)i + 1.0f);
  }
}
