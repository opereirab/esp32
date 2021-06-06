#ifndef _CHANNEL_FUNCTION_H_
#define _CHANNEL_FUNCTION_H_

#include <Arduino.h>

enum FunctionType {
  FUNCTION_TYPE_UNDEFINED                   = 0x00,
  FUNCTION_TYPE_INPUT                       = INPUT,
  FUNCTION_TYPE_OUTPUT                      = OUTPUT,
  FUNCTION_TYPE_PULLUP                      = PULLUP,
  FUNCTION_TYPE_INPUT_PULLUP                = INPUT_PULLUP,
  FUNCTION_TYPE_PULLDOWN                    = PULLDOWN,
  FUNCTION_TYPE_INPUT_PULLDOWN              = INPUT_PULLDOWN,
  FUNCTION_TYPE_OPEN_DRAIN                  = OPEN_DRAIN,
  FUNCTION_TYPE_OUTPUT_OPEN_DRAIN           = OUTPUT_OPEN_DRAIN,
  FUNCTION_TYPE_SPECIAL                     = SPECIAL,
  FUNCTION_TYPE_FUNCTION_1                  = FUNCTION_1,
  FUNCTION_TYPE_FUNCTION_2                  = FUNCTION_2,
  FUNCTION_TYPE_FUNCTION_3                  = FUNCTION_3,
  FUNCTION_TYPE_FUNCTION_4                  = FUNCTION_4,
  FUNCTION_TYPE_FUNCTION_5                  = FUNCTION_5,
  FUNCTION_TYPE_FUNCTION_6                  = FUNCTION_6,
  FUNCTION_TYPE_ANALOG                      = ANALOG
};

#endif
