#include "LCDDisplay128x64.h"
#include <WiFi.h>
#include "definitions/constants.h"
#include "clock/systemclock.h"

LCDDisplay128x64 display128x64;

LCDDisplay128x64::LCDDisplay128x64(/* args */)
    : u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 13, /* CS=*/ 15)
{
  _voltage = String(0.00f, 2) + "V";
  _current = String(0.00f, 2) + "A";
  _power = String(0.00f, 2) + "W";
  _pf = String(0.00f, 2) + "Pf";
  _frequency = String(0.0f, 1) + "Hz";
  _energy = String(0.000f, 3) + "kW/h";
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
    u8g2.setColorIndex(0);        
    u8g2.drawBox(0, 0, 128, 6);
    u8g2.setColorIndex(1);
    u8g2.setFont(u8g2_font_5x7_tf);
    if(WiFi.isConnected()) {      
      u8g2.drawStr(0, 6, WiFi.localIP().toString().c_str());
    } else {
      u8g2.drawStr(0, 6, WiFi.softAPIP().toString().c_str());
    }

    /*-------------------------------*/
    u8g2.setColorIndex(0);
    u8g2.drawBox(0, 7, 128, 50);
    
    u8g2.setColorIndex(1);
    u8g2.setFont(u8g2_font_profont15_tf);
    u8g2.drawStr(0, 21, _voltage.c_str());
    u8g2.drawStr(0, 37, _current.c_str());
    u8g2.drawStr(0, 53, _power.c_str());

    u8g2.drawStr(64, 21, _pf.c_str());
    u8g2.drawStr(64, 37, _frequency.c_str());
    u8g2.drawStr(64, 53, _energy.c_str());
    /*-------------------------------*/
    
    String datetime = systemclock.getTime();
    u8g2.setColorIndex(0);        
    u8g2.drawBox(0, 58, 128, 64);
    u8g2.setColorIndex(1);
    u8g2.setFont(u8g2_font_5x7_tf);
    u8g2.drawStr(0, 64, datetime.c_str());	// write something to the internal memory
    
    u8g2.setFont(u8g2_font_u8glib_4_tf);    
    u8g2.drawStr(113, 63, VERSION);
    
    u8g2.sendBuffer();
    
}

void LCDDisplay128x64::drawPZEM004t(float voltage, float current, float power, float pf, float frequency, float energy)
{
  _voltage = String(voltage, 2) + "V";
  _current = String(current, 2) + "A";
  _power = String(power, 2) + "W";
  _pf = String(pf, 2) + "Pf";
  _frequency = String(frequency, 1) + "Hz";
  _energy = String(energy, 3) + "kW/h";
}
