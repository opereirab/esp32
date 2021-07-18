#include "WebSocketClient.h"
#include <base64.h>

#include "settings/settings.h"
#include "commands/cmds.h"
#include "commands/cmdprocessor.h"

WebSocketClient wsc;

WebSocketClient::WebSocketClient()
{
}

WebSocketClient::~WebSocketClient()
{
}

void WebSocketClient::onEvent(WStype_t type, uint8_t * payload, size_t length)
{
    switch (type)
    {
        case WStype_ERROR: {
            Serial.println("Websocket client error");
            if(length > 0) {
                Serial.println((const char*) payload);
            }
            wsc.ws.disconnect();
            break;
        }
        case WStype_DISCONNECTED:
        {
            // Serial.println("WebSocket Client Disconnected");
            break;
        }
        case WStype_CONNECTED:           
        {
            StaticJsonDocument <255> doc;
            String payload = "{\"cmd\": " + String(CommandType::REQUEST_DEVICE_SETTINGS) + "}";
            String resp = cmdprocessor.process(payload, payload.length());
            if(!resp.isEmpty()) {
                wsc.ws.sendTXT(resp);
            } else {
                wsc.ws.disconnect();
            }           
            break;
        }
        case WStype_TEXT: 
        {   
            break;
        }
        case WStype_BIN:            
        case WStype_FRAGMENT_TEXT_START:            
        case WStype_FRAGMENT_BIN_START:            
        case WStype_FRAGMENT:            
        case WStype_FRAGMENT_FIN:            
        case WStype_PING:            
        case WStype_PONG:            
        default: 
        {
            // TODO:
            break;
        }                
    }
}

void WebSocketClient::setup()
{
    ws.onEvent(&wsc.onEvent);
    if(!settings.cloud.host.isEmpty()) {
        ws.begin(settings.cloud.host, settings.cloud.port);
        /*ws.setAuthorization(
            settings.cloud.username.c_str(), 
            settings.cloud.password.c_str()
        );*/
        // ws.setReconnectInterval(60000);
        // ws.enableHeartbeat(1000, 1000, 1);
    }
}

void WebSocketClient::loop()
{       
    if(!settings.cloud.host.isEmpty()) {
        ws.loop();
    }
}

void WebSocketClient::send(JsonDocument &doc) {
    if(ws.isConnected()) {
        String payload = "";
        serializeJson(doc, payload);
        ws.sendTXT(payload.c_str(), payload.length());
    }
}

void WebSocketClient::send(const char* payload, size_t size)
{
    if(ws.isConnected()) {
        Serial.println(payload);
        ws.sendTXT(payload, size);
    }        
}
