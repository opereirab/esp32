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
  return SD.open(path, mode); 
}

File FileSystem::open(const String& path, const char* mode)
{ 
  return SD.open(path, mode); 
}

bool FileSystem::exists(const char* path)                      
{ 
  return SD.exists(path); 
}

bool FileSystem::exists(const String& path)                    
{ 
  return SD.exists(path); 
}

bool FileSystem::remove(const char* path)                      
{ 
  return SD.remove(path); 
}

bool FileSystem::remove(const String& path)                    
{ 
  return SD.remove(path); 
}

bool FileSystem::rename(const char* pathFrom, const char* pathTo)
{ 
  return SD.rename(pathFrom, pathTo); 
}

bool FileSystem::rename(const String& pathFrom, const String& pathTo)
{ 
  return SD.rename(pathFrom, pathTo); 
}

bool FileSystem::mkdir(const char *path)                       
{ 
  return SD.mkdir(path); 
}

bool FileSystem::mkdir(const String &path)                     
{ 
  return SD.mkdir(path); 
}

bool FileSystem::rmdir(const char *path)                       
{ 
  return SD.rmdir(path); 
}

bool FileSystem::rmdir(const String &path)                     
{ 
  return SD.rmdir(path); 
}

bool FileSystem::format() 
{ 
  return false; // SD.format(); 
}

void FileSystem::end()
{ 
  SD.end(); 
}

size_t FileSystem::totalBytes() {
  return SD.totalBytes();
}

size_t FileSystem::usedBytes() {
  return SD.usedBytes();
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
  if(!SD.begin(SS, SPI, 4000000U, "/sd", 20)) {
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
