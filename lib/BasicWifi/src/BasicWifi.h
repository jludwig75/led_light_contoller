#pragma once


bool wifi_setup(const char* hostName, const char* ssid, const char* password, int timeoutMs = -1);

void wifi_onLoop();
