#pragma once

#include "ledstring.h"


class StringFunction
{
public:
    virtual int operator()(unsigned long time) = 0;
    virtual LedString::Direction direction(unsigned long time) = 0;
};