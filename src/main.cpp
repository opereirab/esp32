#include <Arduino.h>

#include "clock/systemclock.h"
#include "filesystem/filesystem.h"
#include "settings/settings.h"

#include "network/network.h"
#include "webserver/webserver.h"
#include "websockets/WebSocketServer.h"
#include "websockets/WebSocketClient.h"
#include "channels/channelsmanager.h"

#include "display/LCDDisplay128x64.h"

TaskHandle_t task;

void loop1(void*) {

	while(true) {

    mng.loop();
    // display128x64.loop();

    // TODO: Read config settings
    delay(900);
	}

}

void setup() {

  display128x64.setup();
  
  Serial.begin(115200);
  systemclock.setup();
  filesystem.setup();
  settings.setup();
  network.setup();
  webserver.setup();
  wss.setup();
  // wsc.setup();
  mng.setup();
  
  xTaskCreatePinnedToCore(
    loop1,
    "loop1",
    10000,
    NULL,
    1,
    &task,
    0
  );
}

void loop() {
  wss.loop();	  
  // wsc.loop();
  display128x64.loop();
  yield();
}
