#include "channelsmanager.h"
#include "filesystem/filesystem.h"

ChannelsManager mng;

ChannelsManager::ChannelsManager(/* args */)
  : channels(NULL), count(0)
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
    serializeJson(doc, Serial);
    Serial.println();

    const char* id = doc["id"].as<const char*>();

    if(id != NULL) {
      channels[count].pin = doc["pin"].as<uint8_t>();
      channels[count].type = (SensorType) doc["type"].as<uint8_t>();
      channels[count].id = id;
      count++;
    }

  } while(file.findUntil(",","]"));

  file.close();
  Serial.printf("Sensors: %d\n", count);

  for(size_t i = 0; i < count; i++) {
    channels[i].setup();
  }
}

void ChannelsManager::loop()
{
  for (size_t i = 0; i < count; i++)
  {
    channels[i].setup();
  }
  
}
