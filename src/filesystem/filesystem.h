#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <SPIFFS.h>

class FileSystem
{
private:
  /* data */
public:
  FileSystem(/* args */);
  virtual ~FileSystem();

public:
  File open(const char* path, const char* mode = "r") ;
  File open(const String& path, const char* mode = "r");

  bool exists(const char* path);
  bool exists(const String& path);

  bool remove(const char* path);
  bool remove(const String& path);

  bool rename(const char* pathFrom, const char* pathTo);
  bool rename(const String& pathFrom, const String& pathTo);

  bool mkdir(const char *path);
  bool mkdir(const String &path);

  bool rmdir(const char *path);
  bool rmdir(const String &path);

  bool format();
  void end();

public:
  size_t totalBytes();
  size_t usedBytes();
  float usedPercent();
  size_t freeBytes();
  size_t freePercent();

public:
  void setup();
  void loop();

};

extern FileSystem filesystem;


#endif
