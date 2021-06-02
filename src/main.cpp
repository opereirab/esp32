#include <Arduino.h>

#include "clock/systemclock.h"
#include "filesystem/filesystem.h"
#include "settings/settings.h"

#include "network/network.h"
#include "webserver/webserver.h"
#include "channels/channelsmanager.h"


void setup() {

  Serial.begin(115200);

  systemclock.setup();
  filesystem.setup();
  settings.setup();
  network.setup();
  webserver.setup();
  mng.setup();
}

void loop() {
  network.loop();

  StaticJsonDocument<64> doc;
  doc["cmd"] = 0;
  doc["time"] = systemclock.getTime();
  webserver.sendEvent(CommandType::UNKNOW, doc);

  mng.loop();

  yield();
}
