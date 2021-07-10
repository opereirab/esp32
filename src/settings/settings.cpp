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
}

void Settings::loop()
{
  
}
