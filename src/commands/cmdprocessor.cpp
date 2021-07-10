#include "cmdprocessor.h"
#include "cmds.h"
#include "settings/settings.h"
#include "clock/systemclock.h"
#include "channels/channelsmanager.h"

#include <WiFi.h>

CmdProcessor cmdprocessor;

CmdProcessor::CmdProcessor(/* args */)
{
}

CmdProcessor::~CmdProcessor()
{
}

String CmdProcessor::process(const String& payload, size_t length) {
  String output = "";
  
  StaticJsonDocument <16> filter;
  filter["cmd"] = true;
  
  StaticJsonDocument<32> req;
  DeserializationError e = deserializeJson(req, payload.c_str(), DeserializationOption::Filter(filter));
  if(e != DeserializationError::Ok) {
    return output;
  }
  
  uint8_t cmd = req["cmd"].as<uint8_t>();
  Serial.printf("%d: ", cmd);
  switch (cmd)
  {
    case CommandType::REQUEST_DEVICE_SETTINGS: {
      Serial.println("REQUEST_DEVICE_SETTINGS");
      StaticJsonDocument<1024> resp;
      resp["cmd"] = RESPONSE_DEVICE_SETTINGS;

      JsonObject device = resp.createNestedObject("device");
      device["name"] = settings.device.name;
      device["serial"] = settings.device.serialNum();
      device["type"] = DEVICE_TYPE;
      device["version"] = VERSION;
      
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
      ap["mac"] = WiFi.softAPmacAddress();
      ap["ch"] = WiFi.channel();
      


      JsonObject wifi = resp.createNestedObject("wifi");
      wifi["ssid"] = WiFi.SSID();
      wifi["ip"] = WiFi.localIP().toString();
      wifi["rssi"] = WiFi.RSSI();
      wifi["mac"] = WiFi.macAddress();
      wifi["ch"] = WiFi.channel();

      serializeJson(resp, output);      
      break;
    }
    case CommandType::REQUEST_CHANNELS: {

      File file = filesystem.open(DB_PATH + "/channels.json");
      if(!file) {
        return output;
      }

      output = "{ \"deviceId\": \"" + settings.device.serialNum() + "\",\"channels\":" + file.readString() + "}";
      file.close(); 
      break;
    }
    case CommandType::REQUEST_SENSORS_TYPES: {
      File file = filesystem.open(DB_PATH + "/types.json");
      if(!file) {
        return output;
      }

      output = file.readString();
      file.close(); 
      break;
    }
    case CommandType::REQUEST_SENSORS_FUNCTIONS: {
      File file = filesystem.open(DB_PATH + "/functions.json");
      if(!file) {
        return output;
      }

      output = file.readString();
      file.close(); 
      break;
    }
    case CommandType::REQUEST_CLOUD_SETTINGS: {
      StaticJsonDocument<1024> resp;
      
      resp["type"] = (uint8_t) settings.cloud.type;
      resp["host"] = settings.cloud.host.c_str();
      resp["port"] = settings.cloud.port;
      resp["username"] = settings.cloud.username.c_str();
      resp["password"] = settings.cloud.password.c_str();
      resp["topic"] = settings.cloud.topic.c_str();

      serializeJson(resp, output);
      break;
    }

    case CommandType::REQUEST_SIGNIN: {
      StaticJsonDocument <16> dataFilter;
      dataFilter["data"] = true;

      StaticJsonDocument<256> doc;
      DeserializationError e = deserializeJson(doc, payload.c_str(), DeserializationOption::Filter(dataFilter));
      if(e != DeserializationError::Ok) {
        return output;
      }

      Serial.println(payload);

      JsonObject data = doc["data"].as<JsonObject>();
      const char* username = data["username"];
      const char* password = data["password"];

      Serial.printf("Username: %s\n", settings.security.username.c_str());
      Serial.printf("Password: %s\n", settings.security.password.c_str());

      if(settings.security.username.equalsIgnoreCase(username) && settings.security.password.equals(password)) {
        output = "true";
      } else {
        output = "false";
      }
      break;
    }
    case CommandType::REQUEST_SAVE_SECURITY_SETTINGS: {
      StaticJsonDocument <16> dataFilter;
      dataFilter["data"] = true;

      StaticJsonDocument<256> doc;
      DeserializationError e = deserializeJson(doc, payload.c_str(), DeserializationOption::Filter(dataFilter));
      if(e != DeserializationError::Ok) {
        return output;
      }

      JsonObject data = doc["data"].as<JsonObject>();
      settings.security.username = data["username"].as<String>();
      settings.security.password = data["password"].as<String>();
      
      if(settings.security.save()) {
        serializeJson(doc, output);
      }
      break;
    }
    case CommandType::REQUEST_RESET_SECURITY_SETTINGS: {
      settings.security.username = DEFAULT_USERNAME;
      settings.security.password = DEFAULT_PASSWORD;
      
      if(settings.security.save()) {
        output = "true";
      } else {
        output = "false";
      }
      break;
    }

    case CommandType::REQUEST_SAVE_WIFI_SETTINGS: {
      StaticJsonDocument <16> dataFilter;
      dataFilter["data"] = true;

      StaticJsonDocument<192> doc;
      DeserializationError e = deserializeJson(doc, payload.c_str(), DeserializationOption::Filter(dataFilter));
      if(e != DeserializationError::Ok) {
        return output;
      }

      JsonObject data = doc["data"].as<JsonObject>();
      strcpy(settings.network.ssid, data["ssid"]);
      strcpy(settings.network.password, data["password"]);
      if(settings.network.save()) {
        serializeJson(doc, output);
      }
      break;
    }
    case CommandType::REQUEST_SAVE_AP_SETTINGS: {
      StaticJsonDocument <16> dataFilter;
      dataFilter["data"] = true;

      StaticJsonDocument<96> doc;
      DeserializationError e = deserializeJson(doc, payload.c_str(), DeserializationOption::Filter(dataFilter));
      if(e != DeserializationError::Ok) {
        return output;
      }

      JsonObject data = doc["data"].as<JsonObject>();
      strcpy(settings.network.passphrase, data["password"]);
      if(settings.network.save()) {
        serializeJson(doc, output);
      }
      break;
    }
    case CommandType::REQUEST_SAVE_DEVICE_CHANNELS: {
      StaticJsonDocument <16> dataFilter;
      dataFilter["data"] = true;

      const size_t capacity = JSON_ARRAY_SIZE(MAX_CHANNELS) + MAX_CHANNELS*(JSON_ARRAY_SIZE(MAX_SENSOR_TYPES_X_CHANNELS) +  + 10*JSON_OBJECT_SIZE(9));
      DynamicJsonDocument doc(capacity);
      DeserializationError e = deserializeJson(doc, payload.c_str(), DeserializationOption::Filter(dataFilter));
      if(e != DeserializationError::Ok) {
        return output;
      }
      
      if(filesystem.exists(DB_PATH + "/channels.json")) {
        filesystem.remove(DB_PATH + "/channels.json");
      }

      File file = filesystem.open(DB_PATH + "/channels.json", "w");
      if(!file) {
        Serial.println("Error opening faild");
        return output;
      }

      serializeJson(doc["data"], file);
      doc.clear();
      
      file.close();
      if(file = filesystem.open(DB_PATH + "/channels.json")) {
        output = file.readString();
        file.close();
      }

      break;
    }
    case CommandType::REQUEST_SAVE_CLOUD_SETTINGS: {
      StaticJsonDocument <16> dataFilter;
      dataFilter["data"] = true;

      StaticJsonDocument<1024> doc;
      DeserializationError e = deserializeJson(doc, payload.c_str(), DeserializationOption::Filter(dataFilter));
      if(e != DeserializationError::Ok) {
        return output;
      }

      JsonObject data = doc["data"].as<JsonObject>();

      settings.cloud.type = (CloudProtocolType) data["type"].as<uint8_t>();
      settings.cloud.host = data["host"] | "";
      settings.cloud.port = data["port"].as<uint16_t>();
      settings.cloud.username = data["username"] | "";
      settings.cloud.password = data["password"] | "";
      settings.cloud.topic = data["topic"] | "";

      if(settings.cloud.save()) {
        serializeJson(doc, output);
      }

      break;
    }
    case CommandType::REQUEST_SYNC_DATETIME: {
      StaticJsonDocument <16> dataFilter;
      dataFilter["data"] = true;

      StaticJsonDocument<64> doc;
      DeserializationError e = deserializeJson(doc, payload.c_str(), DeserializationOption::Filter(dataFilter));
      if(e != DeserializationError::Ok) {
        return output;
      }

      uint64_t time = doc["data"].as<uint64_t>();
      systemclock.setDateTime(time);

      serializeJson(doc, output);

      break;
    }
    
    default: break;
  }

  return output;
}
