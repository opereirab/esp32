#include "settings.h"

Settings settings;

Settings::Settings(/* args */)
{
}

Settings::~Settings()
{
}

void Settings::setup()
{
  security.load();
  device.load();
  network.load();
  cloud.load();
}

void Settings::loop()
{
  
}
