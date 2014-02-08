#include "gtimer.h"
#include <Timer.h>

namespace quadcopter
{
namespace global_time
{
double get()
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
}
}
