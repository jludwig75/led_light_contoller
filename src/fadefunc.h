#pragma once

#include "stringfunc.h"


class FadeFunction : public StringFunction
{
public:
    FadeFunction(unsigned long offTime, unsigned long fadeTime, unsigned long onTime);
    int operator()(unsigned long time) override;
    LedString::Direction direction(unsigned long time) override;
protected:
    unsigned long cycleDuration() const;
private:
    unsigned long _fadeInStartTime;
    unsigned long _holdStartTime;
    unsigned long _fadeOutStartTime;
    unsigned long _cycleDuration;
};
