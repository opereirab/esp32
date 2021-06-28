#include "channel.h"

#include "sensors/DS18B20/DS18B20Sensor.h"
#include "sensors/PZEM004/PZEM004Sensor.h"
#include "sensors/PZEM004t/PZEM004tSensor.h"

Channel::Channel()
  : ch(255), 
    pin(255), 
    /*dev(0),*/ 
    type(SensorType::SENSOR_TYPE_UNDEFINED), 
    ptl(ProtocolType::PROTOCOL_TYPE_NONE), 
    id(""),
    sensor(NULL) 
{
}

// Channel::Channel(String _id, uint8_t _ch, uint8_t _pin, /*uint64_t _dev,*/ SensorType _type, ProtocolType _ptl)
//   : ch(_ch), 
//     pin(_pin), 
//     /*dev(_dev),*/ 
//     type(_type), 
//     ptl(_ptl), 
//     id(_id)
// {
// }

Channel::~Channel()
{
}

// void Channel::setChannel(uint8_t _ch) 
// {
//   ch = _ch;
// }

// void Channel::setPin(uint8_t _pin)
// {
//   pin = _pin;
// }

// void Channel::setDev(uint64_t _dev) 
// {
//   dev = _dev;
// }

// void Channel::setType(SensorType _type)
// {
//   type = _type;
// }

// void Channel::setProtocol(ProtocolType _ptl)
// {
//   ptl = _ptl;
// }

// void Channel::setId(String _id)
// {
//   id = _id;
// }

void Channel::setup(String _id, uint8_t _ch, uint8_t _pin, SensorType _type, ProtocolType _ptl)
{
  id = _id;
  ch = _ch;
  pin = _pin;
  type = _type;
  ptl = _ptl;

  switch (type)
  {
    case SensorType::SENSOR_TYPE_DS18B20: {
      sensor = new DS18B20Sensor();
      break;
    }
    case SensorType::SENSOR_TYPE_PZEM004: {
      sensor = new PZEM004Sensor();
      break;
    }
    case SensorType::SENSOR_TYPE_PZEM004t: {
      sensor = new PZEM004tSensor();
      break;
    }
    default:
      break;
  }

}

void Channel::loop()
{
  if(!sensor) return;
  sensor->loop();
}

void Channel::loop(JsonArray& array)
{
  if(!sensor) return;

  JsonObject doc = array.createNestedObject();
  doc["id"] = id;
  sensor->loop(doc);
}
