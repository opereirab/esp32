#include "WebSocketServer.h"
#include "commands/cmdprocessor.h"
#include "settings/settings.h"
#include "channels/channelsmanager.h"

WebSocketServer wss;

WebSocketServer::WebSocketServer() 
    : ws(DEFAULT_WSS_PORT, "/ws")
{    
}

WebSocketServer::~WebSocketServer()
{        
}

void WebSocketServer::onEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
    switch (type)
    {
        case WStype_ERROR: 
        {
            if(length > 0)
                Serial.println((const char*)payload);
            Serial.println("WebSocket server client connection error");
            wss.ws.disconnect(num);
            break;
        }           
        case WStype_DISCONNECTED:
        {           
            break;
        }
        case WStype_CONNECTED:           
        {
            break;
        }
        case WStype_TEXT: 
        {   
            String resp = cmdprocessor.process((const char*) payload, length);
            if(!resp.isEmpty())
            {      
                wss.ws.sendTXT(num, resp);
            }
            break;
        }
        case WStype_BIN:            
        case WStype_FRAGMENT_TEXT_START:            
        case WStype_FRAGMENT_BIN_START:            
        case WStype_FRAGMENT:            
        case WStype_FRAGMENT_FIN:            
        // case WStype_PING:            
        // case WStype_PONG:            
        default: 
        {
            // TODO:
            break;
        }                
    }
}

void WebSocketServer::setup()
{
    if(!settings.security.username.isEmpty() && 
       !settings.security.password.isEmpty()) {
        ws.setAuthorization(
            settings.security.username.c_str(), 
            settings.security.password.c_str()
        );
    }
    ws.onEvent(&wss.onEvent);

    ws.begin();
}

void WebSocketServer::loop()
{
    ws.loop();
}

size_t WebSocketServer::connectedClients() { 
    return ws.connectedClients();
}

void WebSocketServer::sendBroadcastExcept(const char* payload, size_t size, const IPAddress& exceptAdd)
{
    // int connectedClients = wss.ws->connectedClients();
    // for(int i = 0; i < connectedClients; i++) {
    //     IPAddress add = ws->remoteIP(i);
    //     if(add != exceptAdd) {
    //         wss.ws->sendTXT(i, (const char*)payload, size);
    //     }
    // }       
}

void WebSocketServer::sendTo(const char* payload, size_t size, const IPAddress& addSender) 
{
    // int connectedClients = wss.ws->connectedClients();
    // for(int i = 0; i < connectedClients; i++) {
    //     IPAddress add = ws->remoteIP(i);
    //     if(add == addSender) {
    //         wss.ws->sendTXT(i, (const char*)payload, size);
    //     }
    // }
}
