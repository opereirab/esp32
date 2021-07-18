#include "notifier.h"

#include "display/LCDDisplay128x64.h"
#include "websockets/WebSocketServer.h"
#include "websockets/WebSocketClient.h"

Notifier notifier;

Notifier::Notifier(/* args */)
{
}

Notifier::~Notifier()
{
}

void Notifier::notify(JsonDocument &doc)
{
    // TODO:
    // display128x64.drawPZEM004t()
    wsc.send(doc);    
    wss.sendBroadcast(doc);
}
