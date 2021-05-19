#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "filesystem/filesystem.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class Webserver
{
private:
  AsyncWebServer server;
  AsyncWebSocket ws; // access at ws://[esp ip]/ws
  AsyncEventSource events; // event source (Server-Sent events)

public:
  Webserver(/* args */);
  virtual ~Webserver();

private:
  static void onRequest(AsyncWebServerRequest *request);
  static void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
  static void onUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
  static void onWebSocketEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);

private:
  void routes();

public:
  void setup();
  void loop();
};

extern Webserver webserver;

#endif
