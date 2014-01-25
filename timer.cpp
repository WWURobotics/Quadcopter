#include "timer.h"

Timer_t & makeTimer()
{
    return *new Timer_t;
}

Timer_t & Timer = makeTimer();

double Timer_t::getTime() const
{
    //FIXME(jacob#):finish
    return 0;
}
