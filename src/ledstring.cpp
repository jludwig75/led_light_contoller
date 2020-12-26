#include "ledstring.h"

#include <Arduino.h>


static volatile LedString::Direction _currentTimerDirection = LedString::FORWARD;

void LedString::onTimerInterval()
{
    if (_currentTimerDirection == LedString::FORWARD)
    {
        _currentTimerDirection = LedString::REVERSE;
    }
    else    // REVERSE
    {
        _currentTimerDirection = LedString::FORWARD;
    }
}

LedString::LedString(uint8_t pin1, uint8_t pin2)
    :
    _pin1(pin1),
    _pin2(pin2),
    _direction(FORWARD),    // Don't enable timer work until needed.
    _brightness(0),
    _lastTimerDirection(BOTH)
{
}

void LedString::begin()
{
    analogWriteFreq(10 * 1000); // Don't go too high to limit CPU utilization. 40KHz is the max
    analogWrite(_pin1, 0);
    analogWrite(_pin2, 0);
}

void LedString::setDirection(Direction direction)
{
    if (direction == _direction)
    {
        return;
    }
    _direction = direction;

    analogWrite(_pin1, 0);
    analogWrite(_pin2, 0);

    if (_brightness > 0)
    {
        updateBrightness();
    }
}

void LedString::setBrightness(int brightness)
{
    if (_brightness == brightness)
    {
        return;
    }
    _brightness = brightness;

    updateBrightness();
}

void LedString::updateBrightness()
{
    if (_direction == FORWARD)
    {
        analogWrite(_pin1, _brightness);
    }
    else if (_direction == REVERSE)
    {
        analogWrite(_pin2, _brightness);
    }
    // Do nothing here for BOTH. The onLoop call will pick up the new brightness.
}

void LedString::onLoop()
{
    if (_direction == BOTH)
    {
        volatile Direction currentDirection = _currentTimerDirection;
        if (_lastTimerDirection == currentDirection)
        {
            return;
        }
        _lastTimerDirection = currentDirection;
        // Use whatever direction the timer has set.
        if (currentDirection == FORWARD)
        {
            analogWrite(_pin2, 0);
            analogWrite(_pin1, _brightness);
        }
        else // REVERSE
        {
            analogWrite(_pin1, 0);
            analogWrite(_pin2, _brightness);
        }
    }
}
