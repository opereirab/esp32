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

};

extern LCDDisplay128x64 display128x64;


#endif
