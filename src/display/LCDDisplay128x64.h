#ifndef _LCD_DISPLAY_128_X_64_H_
#define _LCD_DISPLAY_128_X_64_H_

#include <U8g2lib.h>
// #include <SPI.h>

class LCDDisplay128x64
{
private:
    U8G2_ST7920_128X64_F_SW_SPI u8g2;

public:
    LCDDisplay128x64(/* args */);
    virtual ~LCDDisplay128x64();

public:
    void setup();
    void loop();

private:
    String _voltage;
    String _current;
    String _power;
    String _pf;
    String _frequency;
    String _energy;

public:
    void drawPZEM004t(float voltage, float current, float power, float pf, float frequency, float energy);
};

extern LCDDisplay128x64 display128x64;


#endif
