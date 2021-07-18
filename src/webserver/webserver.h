#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "definitions/constants.h"
#include "filesystem/filesystem.h"
#include "commands/cmds.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class Webserver
{
private:
  AsyncWebServer server;

public:
  Webserver(/* args */);
  virtual ~Webserver();

private:
  static void onRequest(AsyncWebServerRequest *request);
  static void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
  static void onUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);

private:
  void routes();

public:
  void sendEvent(CommandType cmd, JsonDocument& doc);
  void sendEvent(CommandType cmd, const char* payload);

public:
  void setup();
  void loop();
};

extern Webserver webserver;

#endif
