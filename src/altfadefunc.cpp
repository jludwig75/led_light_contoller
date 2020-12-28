#include "altfadefunc.h"


AlternateFadeFunction::AlternateFadeFunction(unsigned long offTime, unsigned long fadeTime, unsigned long onTime)
    :
    FadeFunction(offTime, fadeTime, onTime)
{
}

StringFunction::StripeValues AlternateFadeFunction::operator()(unsigned long time)
{
    auto values = FadeFunction::operator()(time);
    auto stripe = activeStripe(time);
    if (stripe == 0)
    {
        values.stripe1Brightness = 0;
    }
    else
    {
        values.stripe0Brightness = 1;
    }

    return values;
}


int AlternateFadeFunction::activeStripe(unsigned long time)
{
    auto interval = time / cycleDuration();

    return interval % 2;
}
