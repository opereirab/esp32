#ifndef _WEBSOCKETCLIENT_H_
#define _WEBSOCKETCLIENT_H_

#include "definitions/constants.h"
#include <WebSocketsClient.h>

class WebSocketClient
{
    private:        
        WebSocketsClient ws;

    public:
        WebSocketClient();
        virtual ~WebSocketClient();

    private:            
        static void onEvent(WStype_t type, uint8_t * payload, size_t length);

    public:
        void setup();
        void loop();
    public:
        void send(JsonDocument &doc);
        void send(const char* payload, size_t size);     
};

extern WebSocketClient wsc;

#endif
