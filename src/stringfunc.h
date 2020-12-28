#pragma once


class StringFunction
{
public:
    struct StripeValues
    {
        StripeValues(int stripe0Brightness, int stripe1Brightness)
            :
            stripe0Brightness(stripe0Brightness),
            stripe1Brightness(stripe1Brightness)
        {
        }
        StripeValues(int brightness)
            :
            stripe0Brightness(brightness),
            stripe1Brightness(brightness)
        {
        }
        int stripe0Brightness;
        int stripe1Brightness;
    };
    virtual StripeValues operator()(unsigned long time) = 0;
};