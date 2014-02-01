#include "gtimer.h"
#include "timer.h"

Timer_t & makeTimer()
{
    return *new Timer_t;
}

Timer_t & Timer = makeTimer();

double Timer_t::getTime() const
{
    static mbed::Timer timer;
    static uint64_t curTime = 0;
    uint64_t t = timer.read_us();
    if(t > 100000)
    {
        curTime += t;
        timer.reset();
        t = 0;
    }
    t += curTime;
    return (double)t * 1e-6;
}
