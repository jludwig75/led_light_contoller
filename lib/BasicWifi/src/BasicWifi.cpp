#include "BasicWifi.h"

#include <Arduino.h>

#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>


bool wifi_setup(const char* hostName, const char* ssid, const char* password, int timeoutMs)
{
    WiFi.hostname(hostName);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    int msWaited = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        msWaited += 500;
        if (timeoutMs != -1 && msWaited > timeoutMs)
        {
            return false;
        }
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin(hostName)) 
    {
        Serial.println("MDNS responder started");
    }
    else
    {
        // Don't make this fatal. Just report it
        Serial.println("Failed to start MDNS responder");
    }

    return true;
}

void wifi_onLoop()
{
    MDNS.update();
}
