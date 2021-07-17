#ifndef _WEBSOCKETCLIENT_H_
#define _WEBSOCKETCLIENT_H_

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
        void send(const char* payload, size_t size);
    
    public:
        std::function<void ()> onConnected;
        std::function<void ()> onDisconnected;        
};

extern WebSocketClient wsc;

#endif
