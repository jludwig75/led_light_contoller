#pragma once

#include <vector>

#include <stdint.h>
#include <WString.h>

#include "ledstring.h"


class StringFunction;

class LedChannel
{
public:
    LedChannel(uint8_t channelNumber,
               uint8_t pin1,
               uint8_t pin2);
    void begin();
    uint8_t number() const;
    bool setMode(const String& mode);
    String getMode() const;
    static std::vector<String> supportedModes();
    static bool isSupportedMode(const String& modeString);
    void onLoop();
    static void onTimerInterval();
private:
    enum Mode
    {
        OFF,
        CONSTANT,
        FADE,
        FADE_ALTERNATE,
        UNKNOWN = 999
    };
    static String modeToString(Mode mode);
    static Mode modeFromString(const String& modeString);
    uint8_t _channelNumber;
    Mode _mode;
    static std::vector<String> _supportedModes;
    LedString _string;
    StringFunction* _currentFunction;
};
