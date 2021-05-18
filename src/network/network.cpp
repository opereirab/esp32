#include "network.h"
#include "settings/settings.h"

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
    case SYSTEM_EVENT_WIFI_READY:{
      Logger::log("ESP32 WiFi ready");
      break;
    } 
    case SYSTEM_EVENT_SCAN_DONE: {
      Logger::log("ESP32 finish scanning AP");
      break;
    }
    case SYSTEM_EVENT_STA_START: {
      Logger::log("ESP32 station start");
      break;
    }
    case SYSTEM_EVENT_STA_STOP: {
      Logger::log("ESP32 station stop");
      break;
    }
    case SYSTEM_EVENT_STA_CONNECTED: {
      Logger::log("ESP32 station connected to AP");
      break;
    }
    case SYSTEM_EVENT_STA_DISCONNECTED: {
      Logger::log("ESP32 station disconnected from AP");
      WiFi.disconnect();
      //WiFi.mode(WIFI_MODE_AP);
      // WiFi.softAP("ESP32_AP");
      break;
    }
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE: {
      Logger::log("The auth mode of AP connected by ESP32 station changed");
      break;
    }
    case SYSTEM_EVENT_STA_GOT_IP: {
      Logger::log("ESP32 station got IP from connected AP");
      break;
    }
    case SYSTEM_EVENT_STA_LOST_IP: {
      Logger::log("ESP32 station lost IP and the IP is reset to 0");
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS: {
      Logger::log("ESP32 station wps succeeds in enrollee mode");
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_FAILED: {
      Logger::log("ESP32 station wps fails in enrollee mode");
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT: {
      Logger::log("ESP32 station wps timeout in enrollee mode");
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_PIN: {
      Logger::log("ESP32 station wps pin code in enrollee mode");
      break;
    }
    case SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP: {
      Logger::log("ESP32 station wps overlap in enrollee mode");
      break;
    }
    case SYSTEM_EVENT_AP_START: {
      Logger::log("ESP32 soft-AP start");
      break;
    }
    case SYSTEM_EVENT_AP_STOP: {
      Logger::log("ESP32 soft-AP stop");
      break;
    }
    case SYSTEM_EVENT_AP_STACONNECTED: {
      Logger::log("A station connected to ESP32 soft-AP");
      break;
    }
    case SYSTEM_EVENT_AP_STADISCONNECTED: {
      Logger::log("A station disconnected from ESP32 soft-AP");
      break;
    }
    case SYSTEM_EVENT_AP_STAIPASSIGNED: {
      Logger::log("ESP32 soft-AP assign an IP to a connected station");
      break;
    }
    case SYSTEM_EVENT_AP_PROBEREQRECVED: {
      Logger::log("Receive probe request packet in soft-AP interface");
      break;
    }
    case SYSTEM_EVENT_GOT_IP6: {
      Logger::log("ESP32 station or ap or ethernet interface v6IP addr is preferred");
      break;
    }
    case SYSTEM_EVENT_ETH_START: {
      Logger::log("ESP32 ethernet start");
      break;
    }
    case SYSTEM_EVENT_ETH_STOP: {
      Logger::log("ESP32 ethernet stop");
      break;
    }
    case SYSTEM_EVENT_ETH_CONNECTED: {
      Logger::log("ESP32 ethernet phy link up");
      break;
    }
    case SYSTEM_EVENT_ETH_DISCONNECTED: {
      Logger::log("ESP32 ethernet phy link down");
      break;
    }
    case SYSTEM_EVENT_ETH_GOT_IP: {
      Logger::log("ESP32 ethernet got IP from connected AP");
      break;
    }
    case SYSTEM_EVENT_MAX: {
      Logger::log("SYSTEM_EVENT_MAX");
      break;
    }
    default: {
      Logger::log("UNHANDLED_WIFI_EVENT");
    }  
  }
}

void Network::setup()
{
  WiFi.onEvent(&Network::onEvent);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(settings.network.apSSID().c_str());
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
