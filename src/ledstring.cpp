#include "ledstring.h"

#include <Arduino.h>


LedString::LedString(uint8_t pin1, uint8_t pin2)
    :
    _pin1(pin1),
    _pin2(pin2),
    _direction(FORWARD),
    _brightness(0)
{
}

void LedString::begin()
{
    analogWriteFreq(10 * 1000); // Don't go too high to limit CPU utilization. 40KHz is the max
    Serial.print(_pin1); Serial.println(" to 0");
    analogWrite(_pin1, 0);
    Serial.print(_pin2); Serial.println(" to 0");
    analogWrite(_pin2, 0);
    updateBrightness();
}

void LedString::setDirection(Direction direction)
{
    if (direction == _direction)
    {
        return;
    }
    _direction = direction;

    Serial.print(_pin1); Serial.println(" to 0");
    analogWrite(_pin1, 0);
    Serial.print(_pin2); Serial.println(" to 0");
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
    Serial.print("Setting brightness to ");
    Serial.println(_brightness);
    if (_direction == FORWARD)
    {
        Serial.print(_pin1); Serial.print(" to "); Serial.println(_brightness);
        analogWrite(_pin1, _brightness);
    }
    else
    {
        Serial.print(_pin2); Serial.print(" to "); Serial.println(_brightness);
        analogWrite(_pin2, _brightness);
    }
}
