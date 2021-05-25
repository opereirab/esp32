#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#include "definitions/constants.h"
#include "filesystem/filesystem.h"
#include <ArduinoJson.h>
#include <WiFi.h>

struct DeviceSettings {
  String serialNum() {
    uint64_t chipid = ESP.getEfuseMac();
    String serialNum  = String((uint16_t)(chipid>>32), HEX) + String((uint32_t)chipid, HEX);
    serialNum.toUpperCase();
    return serialNum;
  }
};

struct NetworkSettings
{
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
    if (File file = filesystem.open(DB_PATH + "/network.json")) {
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


#endif
