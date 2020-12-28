#include "ledchannel.h"

#include <Arduino.h>
#include <FS.h>

#include "fadefunc.h"
#include "altfadefunc.h"


static FadeFunction fadeFunction(1000, 1500, 500);
static AlternateFadeFunction alternateFadeFunction(1000, 1500, 500);
// static AlternateFadeFunction alternateFadeFunction(5000, 50, 50);
static AlternateFadeFunction slowPulseFunction(1000, 200, 100);
static FadeFunction starLightFunction(300, 120, 3000);


LedChannel::LedChannel(uint8_t channelNumber,
                       uint8_t pin1,
                       uint8_t pin2)
    :
    _channelNumber(channelNumber),
    _mode(CONSTANT),
    _string(pin1, pin2),
    _currentFunction(NULL),
    _channelFileName(String("/channel") + String(channelNumber) + ".mode")
{
}

void LedChannel::begin()
{
    _string.begin();
    if (!loadMode())
    {
        Serial.println("Failed to load mode for channel " + String(_channelNumber));
        // Not fatal.
    }
    
    setMode(modeToString(_mode));
}

void LedChannel::onLoop()
{
    if (_currentFunction)
    {
        auto t = millis();
        _string.setBrightness((*_currentFunction)(t));
    }
    _string.onLoop();
}

void LedChannel::onTimerInterval()
{
    LedString::onTimerInterval();
}

uint8_t LedChannel::number() const
{
    return _channelNumber;
}

bool LedChannel::setMode(const String& mode)
{
    auto newMode = modeFromString(mode);
    if (newMode == UNKNOWN)
    {
        return false;
    }
    _currentFunction = NULL;

    switch (newMode)
    {
    case OFF:
        _string.setBrightness(0);
        break;
    case CONSTANT:
        _string.setBrightness(1023);
        break;
    case FADE:
        _currentFunction = &fadeFunction;
        break;
    case FADE_ALTERNATE:
        _currentFunction = &alternateFadeFunction;
        break;
    case SLOW_PULSE:
        _currentFunction = &slowPulseFunction;
        break;
    case STAR_LIGHT:
        _currentFunction = &starLightFunction;
        break;
    default:
        // Not supported now.
        return false;
    }

    Serial.println("Changed channel " + String(_channelNumber) + " mode to \"" + mode + "\"");
    _mode = newMode;
    if (!LedChannel::saveMode())
    {
        Serial.println("Failed to presist mode for channel " + String(_channelNumber));
        // Not a fatal error.
    }
    else
    {
        Serial.println("Successfully saved mode " + String(_mode) + " for channel " + String(_channelNumber));
    }
    
    return true;
}

String LedChannel::getMode() const
{
    return modeToString(_mode);
}

bool LedChannel::saveMode()
{
    auto file = SPIFFS.open(_channelFileName, "w");
    if (!file)
    {
        return false;
    }

    auto ret = file.write((const uint8_t *)&_mode, sizeof(_mode));
    return ret == sizeof(_mode);
}

bool LedChannel::loadMode()
{
    auto file = SPIFFS.open(_channelFileName, "r");
    if (!file)
    {
        return false;
    }

    auto ret = file.read((uint8_t *)&_mode, sizeof(_mode));
    return ret == sizeof(_mode);
}


std::vector<String> LedChannel::supportedModes()
{
    return _supportedModes;
}

bool LedChannel::isSupportedMode(const String& modeString)
{
    return modeFromString(modeString) != UNKNOWN;
}

String LedChannel::modeToString(Mode mode)
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
        case SLOW_PULSE:
            return "Slow Pulse";
        case STAR_LIGHT:
            return "Star Light";
        default:
            return "UNKNOWN";
    }
}

LedChannel::Mode LedChannel::modeFromString(const String& modeString)
{
    if (modeString == "Off")
    {
        return OFF;
    }
    if (modeString == "Constant")
    {
        return CONSTANT;
    }
    if (modeString == "Fade")
    {
        return FADE;
    }
    if (modeString == "Alternating Fade")
    {
        return FADE_ALTERNATE;
    }
    if (modeString == "Slow Pulse")
    {
        return SLOW_PULSE;
    }
    if (modeString == "Star Light")
    {
        return STAR_LIGHT;
    }
    return UNKNOWN;
}

std::vector<String> LedChannel::_supportedModes{
                                                modeToString(OFF),
                                                modeToString(CONSTANT),
                                                modeToString(FADE),
                                                modeToString(FADE_ALTERNATE),
                                                modeToString(SLOW_PULSE),
                                                modeToString(STAR_LIGHT)
                                               };
