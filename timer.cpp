#include "timer.h"

Timer::Timer()
{
    //ctor
}

Timer::~Timer()
{
    //dtor
}

Timer_t & makeTimer()
{
    return new Timer;
}

Timer_t & Timer = makeTimer();

double Timer_t::getTime() const
{

}
