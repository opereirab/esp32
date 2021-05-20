#include "network.h"
#include "settings/settings.h"
#include "webserver/webserver.h"

Network network;

Network::Network(/* args */)
{
}

Network::~Network()
{
}

void Network::onEvent(arduino_event_id_t event, arduino_event_info_t info)
{  
  switch (event)
  {
    case ARDUINO_EVENT_WIFI_READY: {
      Logger::log("ARDUINO_EVENT_WIFI_READY");
      break;
    }
    case ARDUINO_EVENT_WIFI_SCAN_DONE: {
      Logger::log("ARDUINO_EVENT_WIFI_SCAN_DONE");
      break;
    }
    case ARDUINO_EVENT_WIFI_STA_START: {
      Logger::log("ARDUINO_EVENT_WIFI_STA_START");
      break;
    }
    case ARDUINO_EVENT_WIFI_STA_STOP: {
      Logger::log("ARDUINO_EVENT_WIFI_STA_STOP");
      break;
    }
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED: {
      Logger::log("ARDUINO_EVENT_WIFI_STA_DISCONNECTED");
      WiFi.disconnect();
      break;
    }
    case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE: {
      Logger::log("ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE");
      break;
    }
    case ARDUINO_EVENT_WIFI_STA_GOT_IP: {
      Logger::log("ARDUINO_EVENT_WIFI_STA_GOT_IP");
      break;
    }
    case ARDUINO_EVENT_WIFI_STA_GOT_IP6: {
      Logger::log("ARDUINO_EVENT_WIFI_STA_GOT_IP6");
      break;
    }
    case ARDUINO_EVENT_WIFI_STA_LOST_IP: {
      Logger::log("ARDUINO_EVENT_WIFI_STA_LOST_IP");
      break;
    }
    case ARDUINO_EVENT_WIFI_AP_START: {
      Logger::log("ARDUINO_EVENT_WIFI_AP_START");
      break;
    }
    case ARDUINO_EVENT_WIFI_AP_STOP: {
      Logger::log("ARDUINO_EVENT_WIFI_AP_STOP");
      break;
    }
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED: {
      Logger::log("ARDUINO_EVENT_WIFI_AP_STACONNECTED");
      StaticJsonDocument<32> doc;
      doc["cmd"] = RESPONSE_SYSTEM_EVENT_AP_STACONNECTED;
      doc["data"] = WiFi.softAPgetStationNum();
      webserver.sendEvent(RESPONSE_SYSTEM_EVENT_AP_STACONNECTED, doc);
      break;
    }
    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED: {
      Logger::log("ARDUINO_EVENT_WIFI_AP_STADISCONNECTED");
      break;
    }
    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED: {
      Logger::log("ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED");
      StaticJsonDocument<32> doc;
      doc["cmd"] = RESPONSE_SYSTEM_EVENT_AP_STAIPASSIGNED;
      doc["data"] = WiFi.softAPgetStationNum();
      webserver.sendEvent(RESPONSE_SYSTEM_EVENT_AP_STAIPASSIGNED, doc);
      break;
    }
    case ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED: {
      Logger::log("ARDUINO_EVENT_WIFI_AP_PROBEREQRECVED");
      break;
    }
    case ARDUINO_EVENT_WIFI_AP_GOT_IP6: {
      Logger::log("ARDUINO_EVENT_WIFI_AP_GOT_IP6");
      break;
    }
    case ARDUINO_EVENT_ETH_START: {
      Logger::log("ARDUINO_EVENT_ETH_START");
      break;
    }
    case ARDUINO_EVENT_ETH_STOP: {
      Logger::log("ARDUINO_EVENT_ETH_STOP");
      break;
    }
    case ARDUINO_EVENT_ETH_CONNECTED: {
      Logger::log("ARDUINO_EVENT_ETH_CONNECTED");
      break;
    }
    case ARDUINO_EVENT_ETH_DISCONNECTED: {
      Logger::log("ARDUINO_EVENT_ETH_DISCONNECTED");
      break;
    }
    case ARDUINO_EVENT_ETH_GOT_IP: {
      Logger::log("ARDUINO_EVENT_ETH_GOT_IP");
      break;
    }
    case ARDUINO_EVENT_ETH_GOT_IP6: {
      Logger::log("ARDUINO_EVENT_ETH_GOT_IP6");
      break;
    }
    case ARDUINO_EVENT_WPS_ER_SUCCESS: {
      Logger::log("ARDUINO_EVENT_WPS_ER_SUCCESS");
      break;
    }
    case ARDUINO_EVENT_WPS_ER_FAILED: {
      Logger::log("ARDUINO_EVENT_WPS_ER_FAILED");
      break;
    }
    case ARDUINO_EVENT_WPS_ER_TIMEOUT: {
      Logger::log("ARDUINO_EVENT_WPS_ER_TIMEOUT");
      break;
    }
    case ARDUINO_EVENT_WPS_ER_PIN: {
      Logger::log("ARDUINO_EVENT_WPS_ER_PIN");
      break;
    }
    case ARDUINO_EVENT_WPS_ER_PBC_OVERLAP: {
      Logger::log("ARDUINO_EVENT_WPS_ER_PBC_OVERLAP");
      break;
    }
    case ARDUINO_EVENT_SC_SCAN_DONE: {
      Logger::log("ARDUINO_EVENT_SC_SCAN_DONE");
      break;
    }
    case ARDUINO_EVENT_PROV_INIT: {
      Logger::log("ARDUINO_EVENT_PROV_INIT");
      break;
    }
    case ARDUINO_EVENT_PROV_DEINIT: {
      Logger::log("ARDUINO_EVENT_PROV_DEINIT");
      break;
    }
    case ARDUINO_EVENT_PROV_START: {
      Logger::log("ARDUINO_EVENT_PROV_START");
      break;
    }
    case ARDUINO_EVENT_PROV_END: {
      Logger::log("ARDUINO_EVENT_PROV_END");
      break;
    }
    case ARDUINO_EVENT_PROV_CRED_RECV: {
      Logger::log("ARDUINO_EVENT_PROV_CRED_RECV");
      break;
    }
    case ARDUINO_EVENT_PROV_CRED_FAIL: {
      Logger::log("ARDUINO_EVENT_PROV_CRED_FAIL");
      break;
    }
    case ARDUINO_EVENT_PROV_CRED_SUCCESS: {
      Logger::log("ARDUINO_EVENT_PROV_CRED_SUCCESS");
      break;
    }
    case ARDUINO_EVENT_MAX: {
      Logger::log("ARDUINO_EVENT_MAX");
      break;
    }
    default: {
      Logger::log("ARDUINO_EVENT_UNDEFINED");
    }  
  }
}

void Network::setup()
{
  WiFi.onEvent(&Network::onEvent);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(settings.network.apSSID().c_str(), settings.network.passpharse);
  WiFi.begin(settings.network.ssid, settings.network.password);

  dns.setErrorReplyCode(DNSReplyCode::NoError);
  dns.start(DEFAULT_DNSSERVER_PORT, "*", WiFi.softAPIP());
  if(MDNS.begin("esp32")) {
    MDNS.addService("http", "tcp", DEFAULT_HTTP_PORT);
  }
}

void Network::loop()
{
  dns.processNextRequest();
}
