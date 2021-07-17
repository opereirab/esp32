#include "LCDDisplay128x64.h"
#include <WiFi.h>
#include "definitions/constants.h"
#include "clock/systemclock.h"

LCDDisplay128x64 display128x64;

LCDDisplay128x64::LCDDisplay128x64(/* args */)
    : u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* CS=*/ 15)
{
}

LCDDisplay128x64::~LCDDisplay128x64()
{
}

void LCDDisplay128x64::setup()
{
    u8g2.begin();
    u8g2.clearBuffer();					// clear the internal memory
}

void LCDDisplay128x64::loop()
{
    String datetime = systemclock.getTime();
    
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

		
    
}
