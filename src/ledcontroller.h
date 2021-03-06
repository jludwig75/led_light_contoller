#pragma once

#include "ledchannel.h"


class LedController
{
public:
    LedController(uint8_t channel1Pin1,
                  uint8_t channel1Pin2,
                  uint8_t channel2Pin1,
                  uint8_t channel2Pin2);
    void begin();
    std::vector<LedChannel>& channels();
    void onLoop();
private:
    struct ControllerImpl;
    std::vector<LedChannel> _channels;
};