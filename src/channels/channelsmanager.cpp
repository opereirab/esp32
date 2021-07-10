#include "channelsmanager.h"
#include "commands/cmds.h"
#include "filesystem/filesystem.h"
#include "clock/systemclock.h"

ChannelsManager mng;

ChannelsManager::ChannelsManager(/* args */)
  : channels(NULL), count(0), lastUpdate(millis())
{
}

ChannelsManager::~ChannelsManager()
{
  if(channels) {
    delete [] channels;
  }
  channels = NULL;
  count = 0;
}

void ChannelsManager::setup()
{
  if(!filesystem.exists(DB_PATH + + "/channels.json")) {
    Serial.println("File don't exist");
    return;
  }
    

  File file = filesystem.open(DB_PATH + + "/channels.json");
  if(!file) {
    Serial.println("Error opening file");
    return;
  }

  count = 0;
  channels = new Channel[MAX_CHANNELS];

  StaticJsonDocument<48> filter;
  filter["type"] = true;
  filter["pin"] = true;
  filter["id"] = true;

  file.find("[");
  do{
    StaticJsonDocument<128> doc;
    deserializeJson(doc, file, DeserializationOption::Filter(filter));
    
    // TODO: Remove this two lines
    // serializeJson(doc, Serial);
    // Serial.println();

    const char* id = doc["id"].as<const char*>();
    uint8_t ch = doc["ch"].as<uint8_t>();
    uint8_t pin = doc["pin"].as<uint8_t>();
    SensorType type = (SensorType) doc["type"].as<uint8_t>();

    if(id != NULL) {
      channels[count].setup(id, ch, pin, type);
      count++;
    }

  } while(file.findUntil(",","]"));

  file.close();
  // Serial.printf("Sensors: %d\n", count);

  /*for(size_t i = 0; i < count; i++) {
    channels[i].setup();
  }*/
}

void ChannelsManager::loop()
{
  if(millis() - lastUpdate >= 3000) {
    
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(count + 1) +  (count + 1)*(JSON_OBJECT_SIZE(2) + JSON_ARRAY_SIZE(7)) + 255;
    DynamicJsonDocument doc(capacity);
    doc["cmd"] = RESPONSE_SENSORS_VALUES;
    JsonArray data = doc.createNestedArray("data");

    for (size_t i = 0; i < count; i++)
    {
      channels[i].loop(data);
    }

    doc["date"] = systemclock.Epoch64Time();

    // TODO: Notify to all listeners
    // serializeJson(doc, Serial);

    if(!doc.isNull()) {
      doc.clear();
    }

    lastUpdate = millis();
  }
}
