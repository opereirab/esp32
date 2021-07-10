#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <Arduino.h>

#ifndef ARDUINOJSON_USE_LONG_LONG
#define ARDUINOJSON_USE_LONG_LONG 1
#endif

#include <ArduinoJson.h>

#define VERSION "1.0.0"

#include "logger/logger.h"

#define DEVICE_TYPE String("ESP32")

#define DEVICE_PREFIX String("ESP32_")

#define DB_PATH String("/db")

#define DEFAULT_USERNAME  "admin"
#define DEFAULT_PASSWORD  "admin"

#define DEFAULT_STA_WIFI_SSID "TP-Link_D9F8"
#define DEFAULT_STA_WIFI_PASSWORD "67974962"
#define DEFAULT_AP_WIFI_PASSWORD ""

#define DEFAULT_DNSSERVER_PORT 53

#define DEFAULT_HTTP_PORT 80

#define MAX_SENSORS_TYPES 10
#define MAX_CHANNELS 10
#define MAX_SENSOR_TYPES_X_CHANNELS 5

#endif
