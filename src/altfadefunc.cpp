#include "altfadefunc.h"


AlternateFadeFunction::AlternateFadeFunction(unsigned long offTime, unsigned long fadeTime, unsigned long onTime)
    :
    FadeFunction(offTime, fadeTime, onTime)
{
}

LedString::Direction AlternateFadeFunction::direction(unsigned long time)
{
    auto interval = time / cycleDuration();

    return (interval % 2 ? LedString::FORWARD : LedString::REVERSE);
}
