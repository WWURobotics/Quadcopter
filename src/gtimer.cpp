#include "gtimer.h"
#include "mbedio.h"
#include "mbed.h"

namespace quadcopter
{
namespace global_time
{
double get()
{
    static mbed::Timer * timer = nullptr;
    static uint64_t curTimeOffset = 0;
    if(timer == nullptr)
    {
        timer = new mbed::Timer;
        timer->start();
    }
    uint64_t t = timer->read_us();
    if(t > 10000000)
    {
        timer->reset();
        curTimeOffset += t;
        t = 0;
    }
    t += curTimeOffset;
    return (double)t * 1e-6;
}
}
void delay(float time)
{
    wait(time);
}
}
