#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "entities/entities.h"

class Settings
{
public:
  DeviceSettings device;
  NetworkSettings network;


public:
  Settings(/* args */);
  virtual ~Settings();

public:
  void setup();
  void loop();

};

extern Settings settings;

#endif
