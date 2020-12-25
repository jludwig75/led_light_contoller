#pragma once

#include "ledchannel.h"


class LedController
{
public:
    LedController(uint8_t channel1Pin1,
                  uint8_t channel1Pin2,
                  uint8_t channel2Pin1,
                  uint8_t channel2Pin2);
    std::vector<LedChannel>& channels();
private:
    std::vector<LedChannel> _channels;
};