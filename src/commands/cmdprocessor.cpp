#include "cmdprocessor.h"

#include "WiFi.h"
#include <ArduinoJson.h>

CmdProcessor cmdprocessor;

CmdProcessor::CmdProcessor(/* args */)
{
}

CmdProcessor::~CmdProcessor()
{
}

String CmdProcessor::process(const String& payload, size_t length) {
  String output = "";
  
  StaticJsonDocument<32> req;
  DeserializationError e = deserializeJson(req, payload.c_str());
  if(e != DeserializationError::Ok) {
    return output;
  }
  
  int8_t cmd = req["cmd"];
  switch (cmd)
  {
    case 1: 
    {
      StaticJsonDocument<256> resp;
      
      JsonObject wifi = resp.createNestedObject("wifi");
      wifi["connected"] = WiFi.isConnected();
      if(WiFi.isConnected()) {
        wifi["ssid"] = WiFi.SSID();
        wifi["rssi"] = WiFi.RSSI();
        wifi["ip"] = WiFi.localIP().toString();
      }

      JsonObject ap = resp.createNestedObject("ap");
      ap["ssid"] = WiFi.softAPSSID();
      ap["ip"] = WiFi.softAPIP().toString();
      ap["num"] = WiFi.softAPgetStationNum();

      serializeJson(resp, output);
      break;
    }
    default:
      break;
  }

  return output;
}
