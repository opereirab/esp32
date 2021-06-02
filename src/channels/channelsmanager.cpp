#include "channelsmanager.h"

ChannelsManager mng;

ChannelsManager::ChannelsManager(/* args */)
  : channels(NULL), count(0)
{
}

ChannelsManager::~ChannelsManager()
{
  if(channels) {
    delete [] channels;
  }
  channels = NULL;
  count = 0;
}

void ChannelsManager::setup()
{
  for(size_t i = 0; i < count; i++) {
    channels[i].setup();
  }
}

void ChannelsManager::loop()
{
  for (size_t i = 0; i < count; i++)
  {
    channels[i].setup();
  }
  
}
