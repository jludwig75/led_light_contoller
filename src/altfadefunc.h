#include "fadefunc.h"


class AlternateFadeFunction : public FadeFunction
{
public:
    AlternateFadeFunction(unsigned long offTime, unsigned long fadeTime, unsigned long onTime);
    LedString::Stripe stripe(unsigned long time) override;
};