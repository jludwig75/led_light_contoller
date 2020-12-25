#include <Arduino.h>
#include <BasicOTA.h>
#include <BasicWifi.h>

#include "webserver.h"
#include "filesystem.h"

/* NOTE: please add this file (config.h) and define the following in it:
const char* ssid = "SSID Name";
const char* password = "SSID Passwod";
const char* hostName = "Desired board host name";
const char* otaPassword = "Desired OTA password";
const uint8_t POWER_SWITCH_PIN = pin_to_control;
*/
#include "config.h" // <= This file is not part of the repo code. You must add it. See above. ^^^


void setup()
{
    Serial.begin(115200);

    fileSystem_setup();
    wifi_setup(hostName, ssid, password);
    ota_setup(hostName, otaPassword);
    webServer_setup();
}

void loop()
{
    ota_onLoop();
    webServer_onLoop();
    wifi_onLoop();
}