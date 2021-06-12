#include <Arduino.h>

#include "clock/systemclock.h"
#include "filesystem/filesystem.h"
#include "settings/settings.h"

#include "network/network.h"
#include "webserver/webserver.h"
#include "channels/channelsmanager.h"

TaskHandle_t task;

void loop1(void*) {

	while(true) {
		// uint64_t time = systemclock.Epoch64Time();
    // char* payload = new char[40] { '\0' };
    // sprintf(payload, "%llu", time);		
		// webserver.sendEvent(CommandType::UNKNOW, payload);
    // delete [] payload;
    // payload = NULL;

		mng.loop();
		systemclock.loop();	
		delay(1000);
	}

}

void setup() {

  Serial.begin(115200);
  systemclock.setup();
  filesystem.setup();
  settings.setup();
  network.setup();
  webserver.setup();
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
  // network.loop();
  yield();
}
