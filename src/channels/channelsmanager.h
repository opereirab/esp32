#ifndef _CHANNELS_MANAGER_H_
#define _CHANNELS_MANAGER_H_

#include "channel.h"

class ChannelsManager
{
private:
  Channel* channels;
  size_t count; 

public:
  ChannelsManager(/* args */);
  virtual ~ChannelsManager();

public:
  void setup();
  void loop();

};

extern ChannelsManager mng;

#endif
