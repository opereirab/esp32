#include <Arduino.h>

#include "clock/systemclock.h"
#include "filesystem/filesystem.h"
#include "settings/settings.h"

#include "network/network.h"
#include "webserver/webserver.h"


void setup() {

  Serial.begin(115200);

  systemclock.setup();
  filesystem.setup();
  settings.setup();
  network.setup();
  webserver.setup();
}

void loop() {
  network.loop();
  yield();
}
