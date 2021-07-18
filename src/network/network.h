#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>

#include "definitions/constants.h"

class Network
{
private:
  uint16_t aviableNetworks;

public:
  Network();
  virtual ~Network();

private:
  static void onEvent(system_event_id_t event, system_event_info_t info);

public:
  void setup();
  void loop();

public:
    

};

extern Network network;

#endif
