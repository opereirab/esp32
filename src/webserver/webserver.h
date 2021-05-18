#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "filesystem/filesystem.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws
AsyncEventSource events("/events"); // event source (Server-Sent events)

void onRequest(AsyncWebServerRequest *request){
  //Handle Unknown Request
  if (request->method() == HTTP_OPTIONS) {
    request->send(200);
  } else {
    request->send(404);
  }
}

void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total){
  //Handle body
}

void onUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
  //Handle upload
}

void onWebSocketEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  //Handle WebSocket event
}

void routes() {
  server.on("/command", HTTP_POST, [](AsyncWebServerRequest * request) { }, NULL, 
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    static String payload = "";
    for(size_t i = 0; i < len; i++) {
      payload += (char)data[i];  
    }
    if(payload.length() < total) return;
    Serial.println(payload);
    request->send(200, "application/json", "{}");   
  });
}

void setupWebServer() {

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials", "true");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

  // attach AsyncWebSocket
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);

  // attach AsyncEventSource
  server.addHandler(&events);

  routes();

  // attach filesystem root at URL /fs
  server.serveStatic("/", SPIFFS, "/www/").setIsDir(true).setDefaultFile("index.html");
  
  // Catch-All Handlers
  // Any request that can not find a Handler that canHandle it
  // ends in the callbacks below.
  server.onNotFound(onRequest);
  server.onFileUpload(onUpload);
  server.onRequestBody(onBody);

  server.begin();
}

#endif
