#include "webserver.h"
#include "settings/settings.h"
#include "commands/cmdprocessor.h"

Webserver webserver;

Webserver::Webserver(/* args */) 
  : server(DEFAULT_HTTP_PORT)
{
}

Webserver::~Webserver()
{
}

void Webserver::onRequest(AsyncWebServerRequest *request)
{
  //Handle Unknown Request
  if (request->method() == HTTP_OPTIONS) {
    request->send(200);
  } else {
    request->send(404);
  }
}

void Webserver::onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
{
  //Handle body
}

void Webserver::onUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
  //Handle upload
}

void Webserver::routes() {
  server.on("/command", HTTP_POST, [](AsyncWebServerRequest * request) { }, NULL, 
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    static String payload = "";
    for(size_t i = 0; i < len; i++) {
      payload += (char)data[i];  
    }
    if(payload.length() < total) return;
    // Serial.println(payload);
    String resp = cmdprocessor.process(payload, total);
    payload.clear();
    // Serial.println(resp);
    request->send(200, "application/json", resp);   
  });
}

void Webserver::setup()
{
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Credentials", "true");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
  
  routes();

  // attach filesystem root at URL /fs
  server
    .serveStatic("/", SD, "/www/")
    .setIsDir(true)
    .setDefaultFile("index.html");
  
  // Catch-All Handlers
  // Any request that can not find a Handler that canHandle it
  // ends in the callbacks below.
  server.onNotFound(&Webserver::onRequest);
  server.onFileUpload(&Webserver::onUpload);
  server.onRequestBody(&Webserver::onBody);

  server.begin();
}

void Webserver::loop()
{  
}
