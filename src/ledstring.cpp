#include "ledstring.h"

#include <Arduino.h>


volatile LedString::Stripe LedString::_currentTimerStripe = LedString::STRIPE0;

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
    _stripe0Brightness(0),
    _stripe1Brightness(0),
    _lastTimerStripe(BOTH)
{
}

void LedString::begin()
{
    analogWriteFreq(10 * 1000); // Don't go too high to limit CPU utilization. 40KHz is the max
    analogWrite(_pin1, 0);
    analogWrite(_pin2, 0);
}

void LedString::setBrightness(int brightness)
{
    setStripe0Brightness(brightness);
    setStripe1Brightness(brightness);
}

void LedString::setBrightness(const StringFunction::StripeValues& brightnessValues)
{
    setStripe0Brightness(brightnessValues.stripe0Brightness);
    setStripe1Brightness(brightnessValues.stripe1Brightness);
}


void LedString::setStripe0Brightness(int brightness)
{
    if (brightness <= 2)
    {
        brightness = 0;
    }
    if (brightness == _stripe0Brightness)
    {
        // No change
        return;
    }
    // Serial.print("0:"); Serial.println(brightness);
    _stripe0Brightness = brightness;
}

void LedString::setStripe1Brightness(int brightness)
{
    if (brightness <= 2)
    {
        brightness = 0;
    }
    if (brightness == _stripe1Brightness)
    {
        // No change
        return;
    }
    // Serial.print("1:"); Serial.println(brightness);
    _stripe1Brightness = brightness;
}

void LedString::onLoop()
{
    volatile Stripe currentStripe = _currentTimerStripe;
    if (_lastTimerStripe == currentStripe)
    {
        // It's OK to only change the brightness when
        // the stripe changes. The user won't notice 
        // a 10 ms delay.
        return;
    }
    _lastTimerStripe = currentStripe;
    // Use whatever stripe the timer has set.
    if (currentStripe == STRIPE0)
    {
        analogWrite(_pin2, 0);
        analogWrite(_pin1, _stripe0Brightness);
    }
    else // STRIPE1
    {
        analogWrite(_pin1, 0);
        analogWrite(_pin2, _stripe1Brightness);
    }
}
