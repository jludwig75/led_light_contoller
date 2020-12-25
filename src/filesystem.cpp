#include "filesystem.h"

#include <Arduino.h>
#include <FS.h>


void fileSystem_setup()
{
   Serial.println("Initializing SPIFFS");

    // Create the log file
    if (!SPIFFS.begin())
    {
        Serial.println("Error initializing SPIFFS");
        return;
    }

   Serial.println("Checking for file system...");
   FSInfo info;
   if (!SPIFFS.info(info))
   {
       Serial.println("Formatting file system");
       if (!SPIFFS.format())
       {
           Serial.println("Error formatting SPIFFS");
           return;
       }
   }
   else
   {
       Serial.println("File system already formatted.");
   }
}