#pragma once

#include <stdint.h>


class LedString
{
public:
    LedString(uint8_t pin1, uint8_t pin2);
    void begin();
    enum Stripe
    {
        STRIPE0,
        STRIPE1,
        BOTH
    };
    void setStripe(Stripe stripe);
    void setBrightness(int brightness);
    void onLoop();
    static void onTimerInterval();
private:
    void updateBrightness();
    uint8_t _pin1;
    uint8_t _pin2;
    Stripe _stripe;
    int _brightness;
    Stripe _lastTimerStripe;
};