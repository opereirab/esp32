#include "DS18B20Sensor.h"

DS18B20Sensor::DS18B20Sensor(/* args */)
  : Sensor()
{
}

DS18B20Sensor::~DS18B20Sensor()
{
}

void DS18B20Sensor::setup()
{
}

void DS18B20Sensor::loop()
{
}

void DS18B20Sensor::loop(JsonObject& doc)
{
  JsonArray values = doc.createNestedArray("values");
  values.add<float>(25.8f);
}
