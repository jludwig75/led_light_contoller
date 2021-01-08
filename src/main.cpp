#include <Arduino.h>
#include <BasicOTA.h>
#include <BasicWifi.h>

#include "ledcontroller.h"
#include "webserver.h"
#include "filesystem.h"

/* NOTE: please add this file (config.h) and define the following in it:
const char* ssid = "SSID Name";
const char* password = "SSID Passwod";
const char* otaPassword = "Desired OTA password";
const uint8_t CHANNEL1_PIN1 = 1;
const uint8_t CHANNEL1_PIN2 = 2;
const uint8_t CHANNEL2_PIN1 = 3;
const uint8_t CHANNEL2_PIN2 = 4;
*/
#include "config.h" // <= This file is not part of the repo code. You must add it. See above. ^^^


LedController controller(CHANNEL1_PIN1,
                         CHANNEL1_PIN2,
                         CHANNEL2_PIN1,
                         CHANNEL2_PIN2);

WebServer webServer(controller);

void setup()
{
    Serial.begin(115200);
    delay(50);
    fileSystem_setup();
    controller.begin();

    wifi_setup(HOST_NAME, ssid, password);
    ota_setup(HOST_NAME, otaPassword);
    webServer.begin();
}

void loop()
{
    controller.onLoop();
    ota_onLoop();
    webServer.onLoop();
    wifi_onLoop();
}