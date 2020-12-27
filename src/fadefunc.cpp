#include "fadefunc.h"


FadeFunction::FadeFunction(unsigned long offTime,
                           unsigned long fadeTime,
                           unsigned long onTime)
    :
    _fadeInStartTime(offTime),
    _holdStartTime(offTime + fadeTime),
    _fadeOutStartTime(offTime + fadeTime + onTime),
    _cycleDuration(offTime + fadeTime + onTime + fadeTime)
{
}

int FadeFunction::operator()(unsigned long time)
{
    time %= _cycleDuration;
    if (time < _fadeInStartTime)
    {
        return 0;
    }

    if (time < _holdStartTime)
    {
        return ((time - _fadeInStartTime) * 1023) / (_holdStartTime - _fadeInStartTime);
    }

    if (time < _fadeOutStartTime)
    {
        return 1023;
    }

    if (time < _cycleDuration)
    {
        return 1023 - (((time - _fadeOutStartTime) * 1023) / (_cycleDuration - _fadeOutStartTime));
    }

    // Shouldn't ever hit this.
    return 0;
}

LedString::Direction FadeFunction::direction(unsigned long time)
{
    return LedString::BOTH;
}

unsigned long FadeFunction::cycleDuration() const
{
    return _cycleDuration;
}
