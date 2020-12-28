#pragma once

#include "ledstring.h"


class StringFunction
{
public:
    virtual int operator()(unsigned long time) = 0;
    virtual LedString::Stripe stripe(unsigned long time) = 0;
};