#ifndef _WEBSOCKET_SERVER_H_
#define _WEBSOCKET_SERVER_H_

#include "definitions/constants.h"
#include <WebSocketsServer.h>

class WebSocketServer
{
    private:
        WebSocketsServer ws;

    public:
        WebSocketServer();
        virtual ~WebSocketServer();

    private:
        static void onEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

    public:
        void setup();
        void loop();

    public:    
        size_t connectedClients();
    
    public:
        void sendBroadcast(JsonDocument &doc);
        void sendBroadcast(const char* payload, size_t size);

};

extern WebSocketServer wss;

#endif
