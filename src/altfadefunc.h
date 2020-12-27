#include "fadefunc.h"


class AlternateFadeFunction : public FadeFunction
{
public:
    AlternateFadeFunction(unsigned long offTime, unsigned long fadeTime, unsigned long onTime);
    LedString::Direction direction(unsigned long time) override;
};