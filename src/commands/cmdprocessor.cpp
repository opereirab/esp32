#include "cmdprocessor.h"
#include "cmds.h"
#include "settings/settings.h"

#include <WiFi.h>
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
  
  uint8_t cmd = req["cmd"].as<uint8_t>();
  Serial.printf("%d: ", cmd);
  switch (cmd)
  {
    case CommandType::REQUEST_DEVICE_SETTINGS: {
      Serial.println("REQUEST_DEVICE_SETTINGS");
      StaticJsonDocument<385> resp;
      resp["cmd"] = RESPONSE_DEVICE_SETTINGS;
      
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
    case CommandType::REQUEST_NETWORK_SETTINGS: {
      Serial.println("REQUEST_NETWORK_SETTINGS");

      WiFi.scanNetworks(true);

      StaticJsonDocument<300> resp;
      resp["cmd"] = RESPONSE_NETWORK_SETTINGS;

      JsonObject ap = resp.createNestedObject("ap");
      ap["ssid"] = WiFi.softAPSSID();
      ap["ip"] = WiFi.softAPIP().toString();

      JsonObject wifi = resp.createNestedObject("wifi");
      wifi["ssid"] = WiFi.SSID();
      wifi["ip"] = WiFi.localIP().toString();
      wifi["rssi"] = WiFi.RSSI();

      serializeJson(resp, output);      
      break;
    }
    default:
      break;
  }

  return output;
}
