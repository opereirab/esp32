#include <Arduino.h>

#include "filesystem/filesystem.h"
#include "settings/settings.h"

#include "network/network.h"
#include "webserver/webserver.h"

void setup() {

  Serial.begin(115200);

  filesystem.setup();
  settings.setup();
  network.setup();
  setupWebServer();
}

void loop() {
  // filesystem.loop();
  // settings.loop();
  network.loop();
  yield();
}
