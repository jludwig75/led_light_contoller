#include "webserver.h"

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <FS.h>

#include "ledcontroller.h"


const char* web_page = ""
"<html>\n"
"  <head>\n"
"  </head>\n"
"  <body>\n"
"    <p>\n"
"      No web page found. Please upload a web page.</p>\n"
"      <form action=\"/upload\" method=\"POST\" enctype=\"multipart/form-data\">\n"
"          <input type=\"file\"  name=\"fileToUpload\" id=\"fileToUpload\"/><br/>\n"
"          <input type=\"submit\" value=\"Upload File\" name=\"submit\"/>\n"
"      </form>\n"
"  </body>\n"
"</html>\n";

template<typename T>
class FreeBufferOnExit
{
public:
    FreeBufferOnExit(T* buffer)
        :
        _buffer(buffer)
    {
    }
    ~FreeBufferOnExit()
    {
        delete[] _buffer;
    }
private:
    T* _buffer;
};

WebServer::WebServer(LedController& controller)
    :
    _server(80),
    _controller(controller)
{
}

void WebServer::begin()
{
    _server.on("/", [this](){ handle_root(); });
    _server.on("/supported_modes", [this](){ handle_supported_modes(); });
    _server.on("/channels", [this](){ handle_channels(); });
    _server.on("/mode", [this](){ handle_mode(); });
    _server.on("/upload", HTTP_POST, [this](){ replyOK(); }, [this](){ handle_upload_POST(); });
    _server.on("/upload", HTTP_GET, [this](){ handle_upload_GET(); });
    _server.serveStatic("/", SPIFFS, "/");
    _server.begin();
    Serial.println("HTTP server started");
}

void WebServer::onLoop()
{
    _server.handleClient();
}


void WebServer::handle_upload_GET()
{
    _server.send(200, "text/html", web_page);
}

void WebServer::handle_root()
{
    File webpage = SPIFFS.open("/index.html", "r");
    if (!webpage)
    {
        handle_upload_GET();
        return;
    }

    _server.streamFile(webpage, "text/html");
}

void WebServer::handle_supported_modes()
{
    String message = "[";
    for (const auto& mode : LedChannel::supportedModes())
    {
        if (!message.endsWith("["))
        {
            message += ", ";
        }
        message += "\"" + mode + "\"";
    }
    message += "]";
    _server.send(200, "application/json", message);
}

void WebServer::handle_channels()
{
    String message = "[";
    for (const auto& channel : _controller.channels())
    {
        if (!message.endsWith("["))
        {
            message += ", ";
        }
        message += String(channel.number());
    }
    message += "]";
    _server.send(200, "application/json", message);
}

void WebServer::handle_mode()
{
    if (_server.method() == HTTP_POST || _server.method() == HTTP_GET)
    {
        if (!_server.hasArg("channel"))
        {
            _server.send(400, "txt/plain", "\"channel\" argument was not specified");
            return;
        }

        const auto& channelString = _server.arg("channel");
        auto channelNumber = channelString.toInt();
        if (channelNumber == 0 && channelString != "0")
        {
            _server.send(400, "txt/plain", "Non-numeric value \"" + channelString + "\" for argument \"channel\"");
            return;
        }

        LedChannel* channel = NULL;
        for (auto& _channel : _controller.channels())
        {
            if (_channel.number() == channelNumber)
            {
                channel = &_channel;
                break;
            }
        }
        if (channel == NULL)
        {
            _server.send(404, "txt/plain", "Channel \"" + channelString + "\" not found");
            return;
        }

        if (_server.method() == HTTP_POST)
        {
            if (!_server.hasArg("mode"))
            {
                _server.send(400, "txt/plain", "\"mode\" argument was not specified");
                return;
            }

            const auto& mode = _server.arg("mode");
            if (!LedChannel::isSupportedMode(mode))
            {
                _server.send(400, "txt/plain", "\"" + mode + "\" is not a supported mode");
                return;
            }

            if (channel->setMode(mode))
            {
                _server.send(200, "application/json", "OK");
                return;
            }
            else
            {
                _server.send(500, "txt/plain", "Unexpected error setting mode to \"" + mode + "\"");
                return;
            }
        }
        else if (_server.method() == HTTP_GET)
        {
            if (_server.hasArg("mode"))
            {
                _server.send(400, "txt/plain", "\"mode\" argument invalid for method GET");
                return;
            }

            _server.send(200, "application/json", channel->getMode());
        }
    }
    else
    {
        _server.send(405, "txt/plain", "method not supported\r\n");
    }
}

void WebServer::replyServerError(const String& msg)
{
    Serial.println(msg);
    _server.send(500, "text/plain", msg + "\r\n");
}

void WebServer::handle_upload_POST()
{
    Serial.println(String("Got upload request"));

    HTTPUpload& upload = _server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
        //String filename = "/index.html";
        String filename = upload.filename;
        if (!filename.startsWith("/"))
        {
            filename = "/" + filename;
        }

        Serial.println(String("handleFileUpload Name: ") + filename);
        _uploadFile = SPIFFS.open(filename, "w");
        if (!_uploadFile)
        {
            return replyServerError(F("CREATE FAILED"));
        }

        Serial.println(String("Upload: START, filename: ") + filename);
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
        if (_uploadFile)
        {
            size_t bytesWritten = _uploadFile.write(upload.buf, upload.currentSize);
            if (bytesWritten != upload.currentSize)
            {
                return replyServerError(F("WRITE FAILED"));
            }
        }
        Serial.println(String("Upload: WRITE, Bytes: ") + upload.currentSize);
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
        if (_uploadFile)
        {
            _uploadFile.close();
        }
        Serial.println(String("Upload: END, Size: ") + upload.totalSize);
        _server.sendHeader("Location", String("/"), true);
        _server.send ( 302, "text/plain", "");
    }
}

void WebServer::replyOK()
{
    _server.send(200, "text/plain", "");
}
