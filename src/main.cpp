#include "mbedio.h"
#include "gtimer.h"
#include "scheduler.h"
#include <string>

using namespace std;
using namespace quadcopter;

int main()
{
    Scheduler scheduler;
    scheduler.add(make_shared<FnRunnable>([](){mbedOut << std::setprecision(9) << global_time::get() << endl;}));
    while(true)
    {
        scheduler.update();
    }
}
