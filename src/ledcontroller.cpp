#include "ledcontroller.h"


LedController::LedController(uint8_t channel1Pin1,
                             uint8_t channel1Pin2,
                             uint8_t channel2Pin1,
                             uint8_t channel2Pin2)
    :
    _channels{ LedChannel(1, channel1Pin1, channel1Pin2),
               LedChannel(2, channel2Pin1, channel2Pin2) }
{
}

std::vector<LedChannel>& LedController::channels()
{
    return _channels;
}
