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

void Network::onEvent(system_event_id_t event, system_event_info_t info)
{  
  switch (event)
  {
    case SYSTEM_EVENT_WIFI_READY: {
      break;
    }
    case SYSTEM_EVENT_SCAN_DONE: {
      break;
    }
    case SYSTEM_EVENT_STA_START: {
      break;
    }
    case SYSTEM_EVENT_STA_STOP: {
      break;
    }
    case SYSTEM_EVENT_STA_CONNECTED: {
      break;
    }
    case SYSTEM_EVENT_STA_DISCONNECTED: {
      WiFi.disconnect();
      break;
    }
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE: {
      break;
    }
    case SYSTEM_EVENT_STA_GOT_IP: {
      break;
    }
    case SYSTEM_EVENT_STA_LOST_IP: {
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS: {
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_FAILED: {
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT: {
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_PIN: {
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP: {
      break;
    }
    case SYSTEM_EVENT_AP_START: {
      break;
    }
    case SYSTEM_EVENT_AP_STOP: {
      break;
    }
    case SYSTEM_EVENT_AP_STACONNECTED: {
      StaticJsonDocument<32> doc;
      doc["cmd"] = RESPONSE_SYSTEM_EVENT_AP_STACONNECTED;
      doc["data"] = WiFi.softAPgetStationNum();
      webserver.sendEvent(RESPONSE_SYSTEM_EVENT_AP_STACONNECTED, doc);
      break;
    }
    case SYSTEM_EVENT_AP_STADISCONNECTED: {
      StaticJsonDocument<32> doc;
      doc["cmd"] = RESPONSE_SYSTEM_EVENT_AP_STADISCONNECTED;
      doc["data"] = WiFi.softAPgetStationNum();
      webserver.sendEvent(RESPONSE_SYSTEM_EVENT_AP_STADISCONNECTED, doc);
      break;
    }
    case SYSTEM_EVENT_AP_STAIPASSIGNED: {
      break;
    }
    case SYSTEM_EVENT_AP_PROBEREQRECVED: {
      break;
    }
    case SYSTEM_EVENT_GOT_IP6: {
      break;
    }
    case SYSTEM_EVENT_ETH_START: {
      break;
    }
    case SYSTEM_EVENT_ETH_STOP: {
      break;
    }
    case SYSTEM_EVENT_ETH_CONNECTED: {
      break;
    }
    case SYSTEM_EVENT_ETH_DISCONNECTED: {
      break;
    }
    case SYSTEM_EVENT_ETH_GOT_IP: {
      break;
    }
    case SYSTEM_EVENT_MAX: {
      break;
    }    
    default: {
      Logger::log("ARDUINO_EVENT_UNDEFINED"); 
      break;
    }
  }
}

void Network::setup()
{
  WiFi.onEvent(&Network::onEvent);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(settings.network.apSSID().c_str(), settings.network.passpharse);  
  WiFi.begin(settings.network.ssid, settings.network.password);  
  // dns.setErrorReplyCode(DNSReplyCode::NoError);
  // dns.start(DEFAULT_DNSSERVER_PORT, "*", WiFi.softAPIP());
  if(MDNS.begin("esp32")) {
    MDNS.addService("http", "tcp", DEFAULT_HTTP_PORT);
  }
}

void Network::loop()
{
  // dns.processNextRequest();
}
