#include "fadefunc.h"


class AlternateFadeFunction : public FadeFunction
{
public:
    AlternateFadeFunction(unsigned long offTime, unsigned long fadeTime, unsigned long onTime);
    StripeValues operator()(unsigned long time) override;
private:
    int activeStripe(unsigned long time);
};