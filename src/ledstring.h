#pragma once

#include <stdint.h>
#include "stringfunc.h"


class LedString
{
public:
    LedString(uint8_t pin1, uint8_t pin2);
    void begin();
    void setBrightness(int brightness);
    void setBrightness(const StringFunction::StripeValues& brightnessValues);
    void setStripe0Brightness(int brightness);
    void setStripe1Brightness(int brightness);
    void onLoop();
    static void onTimerInterval();
private:
    enum Stripe
    {
        STRIPE0,
        STRIPE1,
        BOTH
    };
    uint8_t _pin1;
    uint8_t _pin2;
    int _stripe0Brightness;
    int _stripe1Brightness;
    Stripe _lastTimerStripe;
    static volatile Stripe _currentTimerStripe;
};