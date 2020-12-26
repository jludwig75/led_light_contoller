#pragma once

#include <WString.h>
#include <ESP8266WebServer.h>
#include <FS.h>


class LedController;

class WebServer
{
public:
    WebServer(LedController& controller);
    void begin();
    void onLoop();

protected:
    void handle_upload_GET();
    void handle_root();
    void handle_supported_modes();
    void handle_channels();
    void handle_mode();
    void replyServerError(const String& msg);
    void handle_upload_POST();
    void replyOK();

private:
    ESP8266WebServer _server;
    LedController& _controller;
    File _uploadFile;
};
