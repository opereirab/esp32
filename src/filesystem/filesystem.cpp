#include "filesystem.h"
#include "definitions/constants.h"

FileSystem filesystem;

FileSystem::FileSystem(/* args */)
{
}

FileSystem::~FileSystem()
{
}

File FileSystem::open(const char* path, const char* mode)
{ 
  return SPIFFS.open(path, mode); 
}

File FileSystem::open(const String& path, const char* mode)
{ 
  return SPIFFS.open(path, mode); 
}

bool FileSystem::exists(const char* path)                      
{ 
  return SPIFFS.exists(path); 
}

bool FileSystem::exists(const String& path)                    
{ 
  return SPIFFS.exists(path); 
}

bool FileSystem::remove(const char* path)                      
{ 
  return SPIFFS.remove(path); 
}

bool FileSystem::remove(const String& path)                    
{ 
  return SPIFFS.remove(path); 
}

bool FileSystem::rename(const char* pathFrom, const char* pathTo)
{ 
  return SPIFFS.rename(pathFrom, pathTo); 
}

bool FileSystem::rename(const String& pathFrom, const String& pathTo)
{ 
  return SPIFFS.rename(pathFrom, pathTo); 
}

bool FileSystem::mkdir(const char *path)                       
{ 
  return SPIFFS.mkdir(path); 
}

bool FileSystem::mkdir(const String &path)                     
{ 
  return SPIFFS.mkdir(path); 
}

bool FileSystem::rmdir(const char *path)                       
{ 
  return SPIFFS.rmdir(path); 
}

bool FileSystem::rmdir(const String &path)                     
{ 
  return SPIFFS.rmdir(path); 
}

bool FileSystem::format() 
{ 
  return SPIFFS.format(); 
}

void FileSystem::end()
{ 
  SPIFFS.end(); 
}

size_t FileSystem::totalBytes() {
  return SPIFFS.totalBytes();
}

size_t FileSystem::usedBytes() {
  return SPIFFS.usedBytes();
}

float FileSystem::usedPercent() {
  return ((float)usedBytes()*100.0f)/(float)totalBytes();
}

size_t FileSystem::freeBytes() {
  return totalBytes() - usedBytes();
}

size_t FileSystem::freePercent() {
  return 100.0f - usedPercent();
}

void FileSystem::setup()
{
  if(!SPIFFS.begin(false, "/spiffs", 20)) {
    Serial.println("Fail mount filesystem!!!");
  }

  if(!exists(DB_PATH)) {
    if(!mkdir(DB_PATH)) {
      Serial.println("Fail initialize database!!!");
    }
  }
}

void FileSystem::loop()
{

}
