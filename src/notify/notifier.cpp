#include "notifier.h"

#include "display/LCDDisplay128x64.h"
#include "webserver/webserver.h"
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
    // TODO:
    // wsc.send()
    serializeJson(doc, Serial);
    CommandType cmd = (CommandType) doc["cmd"].as<uint8_t>();
    webserver.sendEvent(cmd, doc);
}
