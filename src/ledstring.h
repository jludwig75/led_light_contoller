#pragma once

#include <stdint.h>


class LedString
{
public:
    LedString(uint8_t pin1, uint8_t pin2);
    void begin();
    enum Direction
    {
        FORWARD,
        REVERSE
    };
    void setDirection(Direction direction);
    void setBrightness(int brightness);
private:
    void updateBrightness();
    uint8_t _pin1;
    uint8_t _pin2;
    Direction _direction;
    int _brightness;
};