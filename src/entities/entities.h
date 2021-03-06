#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include "definitions/constants.h"
#include "definitions/protocols.h"
#include "filesystem/filesystem.h"
#include <ArduinoJson.h>
#include <WiFi.h>

struct DeviceSettings {

  String name;

  String serialNum() {
    uint64_t chipid = ESP.getEfuseMac();
    String serialNum  = String((uint16_t)(chipid>>32), HEX) + String((uint32_t)chipid, HEX);
    serialNum.toUpperCase();
    return serialNum;
  }

  bool load() {
    bool result = false;
    if(!filesystem.exists(DB_PATH + "/device.json")) {
      name = (String("ESP32-") + serialNum());
      return result;
    }
      
          
    File file = filesystem.open(DB_PATH + "/device.json");
    if (file) {
      StaticJsonDocument<255> doc;
      DeserializationError e = deserializeJson(doc, file);
      if(e == DeserializationError::Ok) {
        name = doc["name"] | (String("ESP32-") + serialNum()).c_str();
        result = true;
      } else {
        name = (String("ESP32-") + serialNum());
        result = false;
      }
      file.close();      
    }
    return result;
  }

  bool save() {
    bool result = false;
    if(filesystem.exists(DB_PATH + "/device.json")) {
      filesystem.remove(DB_PATH + "/device.json");
    }
    if (File file = filesystem.open(DB_PATH + "/device.json", "w")) {
      StaticJsonDocument<255> doc;
      
      doc["name"] = name.c_str();
      
      size_t size = serializeJson(doc, file);
      file.close();
      result = (size > 0);
    }
    return result;
  }

};

struct NetworkSettings {
  char ssid[33] = { '\0' };
  char password[64] = { '\0' };
  char passphrase[64] = { '\0' };

  IPAddress staIP() {
    return WiFi.localIP();
  }

  IPAddress staMask() {
    return WiFi.subnetMask();
  }

  IPAddress staGateway() {
    return WiFi.gatewayIP();
  }

  String staMacAddress() {
    return WiFi.macAddress();
  }
  
  int8_t staRSSI() {
    return WiFi.RSSI();
  }
  
  uint32_t staChannel() {    
    return WiFi.channel();
  }

  String apSSID() {
    uint64_t chipid = ESP.getEfuseMac();
    String serialNum  = String((uint16_t)(chipid>>32), HEX) + String((uint32_t)chipid, HEX);
    serialNum.toUpperCase();
    return DEVICE_TYPE + "-" + serialNum + "-AP";
  }

  IPAddress apIP() {
    return WiFi.softAPIP();
  }

  IPAddress apMask() {
    return IPAddress(255, 255, 255, 0);
  }

  IPAddress apGateway() {
    return WiFi.softAPIP();
  }

  String apMacAddress() {
    return WiFi.softAPmacAddress();
  }

  bool load() {
    bool result = false;
    if(!filesystem.exists(DB_PATH + "/network.json"))
      return result;
          
    File file = filesystem.open(DB_PATH + "/network.json");
    if (file) {
      StaticJsonDocument<256> doc;
      DeserializationError e = deserializeJson(doc, file);
      if(e == DeserializationError::Ok) {
        strcpy(ssid, doc["ssid"] | DEFAULT_STA_WIFI_SSID);
        strcpy(password, doc["password"] | DEFAULT_STA_WIFI_PASSWORD);
        strcpy(passphrase, doc["passphrase"] | DEFAULT_AP_WIFI_PASSWORD);        
        result = true;
      } else {
        strcpy(ssid, DEFAULT_STA_WIFI_SSID);
        strcpy(password, DEFAULT_STA_WIFI_PASSWORD);
        strcpy(passphrase, DEFAULT_AP_WIFI_PASSWORD); 
        result = false;
      }
      file.close();      
    }
    return result;
  }

  bool save() {
    bool result = false;
    if(filesystem.exists(DB_PATH + "/network.json")) {
      filesystem.remove(DB_PATH + "/network.json");
    }
    if (File file = filesystem.open(DB_PATH + "/network.json", "w")) {
      StaticJsonDocument<256> doc;
      doc["ssid"] = ssid;
      doc["password"] = password;
      doc["passphrase"] = passphrase;
      
      size_t size = serializeJson(doc, file);
      file.close();
      result = (size > 0);
    }
    return result;
  }
};

struct SecuritySettings {
  String username;
  String password;

  bool load() {
    bool result = false;
    if(!filesystem.exists(DB_PATH + "/security.json")) {
      username = DEFAULT_USERNAME;
      password = DEFAULT_PASSWORD;
      return result;
    }
      

    File file = filesystem.open(DB_PATH + "/security.json");
    if (file) {
      StaticJsonDocument<256> doc;
      DeserializationError e = deserializeJson(doc, file);
      if(e == DeserializationError::Ok) {
        username = doc["username"] | DEFAULT_USERNAME;
        password = doc["password"] | DEFAULT_PASSWORD;
        result = true;
      } else {
        result = false;
      }
      file.close();      
    }
    return result;  
  } 

  bool save() {
    bool result = false;
    if(filesystem.exists(DB_PATH + "/security.json")) {
      filesystem.remove(DB_PATH + "/security.json");
    }
    if (File file = filesystem.open(DB_PATH + "/security.json", "w")) {
      StaticJsonDocument<256> doc;
      doc["username"] = username;
      doc["password"] = password;
      
      size_t size = serializeJson(doc, file);
      file.close();
      result = (size > 0);
    }
    return result;
  }
};

struct CloudSettings {
  CloudProtocolType type;
  
  String host = "";
  uint16_t port = 0;
  
  String username = "";
  String password = "";

  String topic = "";

  bool load() {
    bool result = false;
    if(!filesystem.exists(DB_PATH + "/cloud.json"))
      return result;
          
    File file = filesystem.open(DB_PATH + "/cloud.json");
    if (file) {
      StaticJsonDocument<1024> doc;
      DeserializationError e = deserializeJson(doc, file);
      if(e == DeserializationError::Ok) {
        type = (CloudProtocolType) doc["type"].as<uint8_t>();
        host = doc["host"] | "";
        port = doc["port"].as<uint16_t>();      
        username = doc["username"] | "";
        password = doc["password"] | "";
        topic = doc["topic"] | "";
        result = true;
      } else {
        result = false;
      }
      file.close();      
    }
    return result;
  }

  bool save() {
    bool result = false;
    if(filesystem.exists(DB_PATH + "/cloud.json")) {
      filesystem.remove(DB_PATH + "/cloud.json");
    }
    if (File file = filesystem.open(DB_PATH + "/cloud.json", "w")) {
      StaticJsonDocument<1024> doc;
      
      doc["type"] = (uint8_t) type;
      doc["host"] = host.c_str();
      doc["port"] = port;
      doc["username"] = username.c_str();
      doc["password"] = password.c_str();
      doc["topic"] = topic.c_str();
      
      size_t size = serializeJson(doc, file);
      file.close();
      result = (size > 0);
    }
    return result;
  }
};

#endif
