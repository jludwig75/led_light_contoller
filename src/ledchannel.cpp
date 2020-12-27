#include "ledchannel.h"

#include <Arduino.h>

#include "fadefunc.h"
#include "altfadefunc.h"


static FadeFunction fadeFunction(2000, 4000, 1000);
static AlternateFadeFunction alternateFadeFunction(2000, 4000, 1000);


LedChannel::LedChannel(uint8_t channelNumber,
                       uint8_t pin1,
                       uint8_t pin2)
    :
    _channelNumber(channelNumber),
    _mode(CONSTANT),
    _string(pin1, pin2),
    _currentFunction(NULL)
{
}

void LedChannel::begin()
{
    _string.begin();
    setMode(modeToString(_mode));
}

void LedChannel::onLoop()
{
    if (_currentFunction)
    {
        auto t = millis();
        _string.setDirection(_currentFunction->direction(t));
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
        _string.setDirection(LedString::FORWARD); // Disable timer work when off.
        _string.setBrightness(0);
        break;
    case CONSTANT:
        _string.setDirection(LedString::BOTH);
        _string.setBrightness(1023);
        break;
    case FADE:
        _currentFunction = &fadeFunction;
        break;
    case FADE_ALTERNATE:
        _currentFunction = &alternateFadeFunction;
        break;
    default:
        // Not supported now.
        return false;
    }

    Serial.println("Changed channel " + String(_channelNumber) + " mode to \"" + mode + "\"");
    _mode = newMode;
    return true;
}

String LedChannel::getMode() const
{
    return modeToString(_mode);
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
    return UNKNOWN;
}

std::vector<String> LedChannel::_supportedModes{ modeToString(OFF), modeToString(CONSTANT), modeToString(FADE), modeToString(FADE_ALTERNATE) };
