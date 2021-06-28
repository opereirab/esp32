#include <Arduino.h>

#include "clock/systemclock.h"
#include "filesystem/filesystem.h"
#include "settings/settings.h"

#include "network/network.h"
#include "webserver/webserver.h"
#include "channels/channelsmanager.h"

#include <U8g2lib.h>
// #include <SPI.h>
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* CS=*/ 15);

TaskHandle_t task;

void loop1(void*) {

	while(true) {

    mng.loop();
    
    String datetime = systemclock.getTime();
		
    // uint64_t time = systemclock.Epoch64Time();    
    // char* payload = new char[40] { '\0' };
    // sprintf(payload, "%llu", time);		
		// webserver.sendEvent(CommandType::UNKNOW, payload);
    // delete [] payload;
    // payload = NULL;
    
    u8g2.clearBuffer();					// clear the internal memory

    u8g2.setFont(u8g2_font_u8glib_4_tf);
    u8g2.drawStr(113, 63, VERSION);

    u8g2.setFont(u8g2_font_5x7_tf);

    if(WiFi.isConnected()) {      
      u8g2.drawStr(0, 6, WiFi.localIP().toString().c_str());
    } else {
      u8g2.drawStr(0, 6, WiFi.softAPIP().toString().c_str());
    }
    
    u8g2.drawStr(0, 64, datetime.c_str());	// write something to the internal memory
    u8g2.sendBuffer();

		
		// TODO: Read config settings
		delay(900);
    // yield();
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

  u8g2.begin();
  u8g2.clearBuffer();
}

void loop() {	
  // network.loop();
  // mng.loop();
  yield();
}
