#include "ledcontroller.h"

#include <Arduino.h>

LedController::LedController(uint8_t channel1Pin1,
                             uint8_t channel1Pin2,
                             uint8_t channel2Pin1,
                             uint8_t channel2Pin2)
    :
    _channels{ LedChannel(1, channel1Pin1, channel1Pin2),
               LedChannel(2, channel2Pin1, channel2Pin2) }
{
}

void LedController::begin()
{
    for (auto& channel : _channels)
    {
        channel.begin();
    }
}

void LedController::onLoop()
{
    static unsigned long lastMillisInterval = 0;
    auto interval = millis() / 10;
    if (interval != lastMillisInterval)
    {
        LedChannel::onTimerInterval();
        lastMillisInterval = interval;
    }
    for (auto& channel : _channels)
    {
        channel.onLoop();
    }
}


std::vector<LedChannel>& LedController::channels()
{
    return _channels;
}
