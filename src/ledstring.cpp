#include "ledstring.h"

#include <Arduino.h>


static volatile LedString::Stripe _currentTimerStripe = LedString::STRIPE0;

void LedString::onTimerInterval()
{
    if (_currentTimerStripe == LedString::STRIPE0)
    {
        _currentTimerStripe = LedString::STRIPE1;
    }
    else    // STRIPE1
    {
        _currentTimerStripe = LedString::STRIPE0;
    }
}

LedString::LedString(uint8_t pin1, uint8_t pin2)
    :
    _pin1(pin1),
    _pin2(pin2),
    _stripe(STRIPE0),    // Don't enable timer work until needed.
    _brightness(0),
    _lastTimerStripe(BOTH)
{
}

void LedString::begin()
{
    analogWriteFreq(10 * 1000); // Don't go too high to limit CPU utilization. 40KHz is the max
    analogWrite(_pin1, 0);
    analogWrite(_pin2, 0);
}

void LedString::setStripe(Stripe stripe)
{
    if (stripe == _stripe)
    {
        return;
    }
    _stripe = stripe;

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
    if (_stripe == STRIPE0)
    {
        analogWrite(_pin1, _brightness);
    }
    else if (_stripe == STRIPE1)
    {
        analogWrite(_pin2, _brightness);
    }
    // Do nothing here for BOTH. The onLoop call will pick up the new brightness.
}

void LedString::onLoop()
{
    if (_stripe == BOTH)
    {
        volatile Stripe currentStripe = _currentTimerStripe;
        if (_lastTimerStripe == currentStripe)
        {
            return;
        }
        _lastTimerStripe = currentStripe;
        // Use whatever stripe the timer has set.
        if (currentStripe == STRIPE0)
        {
            analogWrite(_pin2, 0);
            analogWrite(_pin1, _brightness);
        }
        else // STRIPE1
        {
            analogWrite(_pin1, 0);
            analogWrite(_pin2, _brightness);
        }
    }
}
