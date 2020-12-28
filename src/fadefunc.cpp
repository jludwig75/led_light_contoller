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

StringFunction::StripeValues FadeFunction::operator()(unsigned long time)
{
    time %= _cycleDuration;
    if (time < _fadeInStartTime)
    {
        return StripeValues(0);
    }

    if (time < _holdStartTime)
    {
        return ((time - _fadeInStartTime) * 1023) / (_holdStartTime - _fadeInStartTime);
    }

    if (time < _fadeOutStartTime)
    {
        return StripeValues(1023);
    }

    if (time < _cycleDuration)
    {
        return StripeValues(1023 - (((time - _fadeOutStartTime) * 1023) / (_cycleDuration - _fadeOutStartTime)));
    }

    // Shouldn't ever hit this.
    return StripeValues(0);
}

unsigned long FadeFunction::cycleDuration() const
{
    return _cycleDuration;
}
