#include "webserver.h"

#include <vector>

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WString.h>


class LedChannel
{
public:
    enum Mode
    {
        OFF,
        CONSTANT,
        FADE,
        FADE_ALTERNATE,
        UNKNOWN = 999
    };
    LedChannel(uint8_t channelNumber)
        :
        _channelNumber(channelNumber),
        _mode(OFF)
    {
    }
    uint8_t number() const
    {
        return _channelNumber;
    }
    bool setMode(const String& mode)
    {
        return false;
    }
    String getMode() const
    {
        return modeToString(_mode);
    }
    static std::vector<String> supportedModes()
    {
        return _supportedModes;
    }
    static bool isSupportedMode(const String& modeString)
    {
        return modeFromString(modeString) != UNKNOWN;
    }
private:
    static String modeToString(Mode mode)
    {
        switch (mode)
        {
            case OFF:
                return "Off";
            case CONSTANT:
                return "Constant";
            case FADE:
                return "Fade";
            case FADE_ALTERNATE:
                return "Alternating Fade";
            default:
                return "UNKNOWN";
        }
    }
    static Mode modeFromString(const String& modeString)
    {
        if (modeString == "Off")
        {
            return OFF;
        }
        if (modeString == "Fade")
        {
            return FADE;
        }
        if (modeString == "Alternating Fade")
        {
            return FADE_ALTERNATE;
        }
        return UNKNOWN;
    }
    uint8_t _channelNumber;
    Mode _mode;
    static std::vector<String> _supportedModes;
};

std::vector<String> LedChannel::_supportedModes{ modeToString(OFF), modeToString(CONSTANT), modeToString(FADE), modeToString(FADE_ALTERNATE) };

std::vector<LedChannel> _channels{ LedChannel(1), LedChannel(2) };

ESP8266WebServer server(80);


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

void handleGetUpload()
{
    server.send(200, "text/html", web_page);
}

void handleRoot()
{
    File webpage = SPIFFS.open("/index.html", "r");
    if (!webpage)
    {
        handleGetUpload();
        return;
    }

    size_t webPageSize = webpage.available();
    char *pageContent = new char[webPageSize + 1];
    if (!pageContent)
    {
        server.send(500, "text/plain", "Could not allocate memory to load web page\r\n");
        return;
    }
    FreeBufferOnExit<char> onExit(pageContent);

    auto bytesRead = webpage.read(reinterpret_cast<uint8_t*>(pageContent), webPageSize);
    if (bytesRead != webPageSize)
    {
        server.send(500, "text/plain", "Error loading web page\r\n");
        return;
    }
    pageContent[webPageSize] = 0;

    server.send(200, "text/html", pageContent);
}

void handle_supported_modes()
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
    server.send(200, "application/json", message);
}

void handle_channels()
{
    String message = "[";
    for (const auto& channel : _channels)
    {
        if (!message.endsWith("["))
        {
            message += ", ";
        }
        message += String(channel.number());
    }
    message += "]";
    server.send(200, "application/json", message);
}

void handle_mode()
{
    if (server.method() == HTTP_POST || server.method() == HTTP_GET)
    {
        if (!server.hasArg("channel"))
        {
            server.send(400, "txt/plain", "\"channel\" argument was not specified");
            return;
        }

        auto channelString = server.arg("channel");
        auto channelNumber = channelString.toInt();
        if (channelNumber == 0 && channelString != "0")
        {
            server.send(400, "txt/plain", "Non-numeric value \"" + channelString + "\" for argument \"channel\"");
            return;
        }

        const LedChannel* channel = NULL;
        for (const auto& _channel : _channels)
        {
            if (_channel.number() == channelNumber)
            {
                channel = &_channel;
                break;
            }
        }

        if (channel == NULL)
        {
            server.send(404, "txt/plain", "Channel \"" + channelString + "\" not found");
            return;
        }

        if (server.method() == HTTP_POST)
        {
            if (!server.hasArg("mode"))
            {
                server.send(400, "txt/plain", "\"mode\" argument was not specified");
                return;
            }
        }
        else if (server.method() == HTTP_GET)
        {
            if (server.hasArg("mode"))
            {
                server.send(400, "txt/plain", "\"mode\" argument invalid for method GET");
                return;
            }
        }
    }
    else
    {
        server.send(405, "txt/plain", "method not supported\r\n");
    }
}

File uploadFile;

void replyServerError(String msg)
{
    Serial.println(msg);
    server.send(500, "text/plain", msg + "\r\n");
}

void handleUpload()
{
    Serial.println(String("Got upload request"));

    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START)
    {
        //String filename = "/index.html";
        String filename = upload.filename;
        if (!filename.startsWith("/"))
        {
            filename = "/" + filename;
        }

        Serial.println(String("handleFileUpload Name: ") + filename);
        uploadFile = SPIFFS.open(filename, "w");
        if (!uploadFile)
        {
            return replyServerError(F("CREATE FAILED"));
        }

        Serial.println(String("Upload: START, filename: ") + filename);
    }
    else if (upload.status == UPLOAD_FILE_WRITE)
    {
        if (uploadFile)
        {
            size_t bytesWritten = uploadFile.write(upload.buf, upload.currentSize);
            if (bytesWritten != upload.currentSize)
            {
                return replyServerError(F("WRITE FAILED"));
            }
        }
        Serial.println(String("Upload: WRITE, Bytes: ") + upload.currentSize);
    }
    else if (upload.status == UPLOAD_FILE_END)
    {
        if (uploadFile)
        {
            uploadFile.close();
        }
        Serial.println(String("Upload: END, Size: ") + upload.totalSize);
        server.sendHeader("Location", String("/"), true);
        server.send ( 302, "text/plain", "");
    }
}

void replyOK()
{
    server.send(200, "text/plain", "");
}


void webServer_setup()
{

    server.on("/", handleRoot);
    server.on("/supported_modes", handle_supported_modes);
    server.on("/channels", handle_channels);
    server.on("/mode", handle_mode);
    server.on("/upload", HTTP_POST, replyOK, handleUpload);
    server.on("/upload", HTTP_GET, handleGetUpload);
    server.serveStatic("/", SPIFFS, "/");
    server.begin();
    Serial.println("HTTP server started");
}

void webServer_onLoop()
{
    server.handleClient();
}