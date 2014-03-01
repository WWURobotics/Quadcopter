#include "mbedio.h"
#include "gtimer.h"
#include "scheduler.h"
#include "um6lt.h"
#include <string>

using namespace std;
using namespace quadcopter;

UM6LT nineDOFSensor(PinName::p8, PinName::p5, PinName::p6, PinName::p7);
Scheduler scheduler;

int main()
{
    scheduler.add(make_shared<FnRunnable>([](){mbedOut << std::setprecision(9) << global_time::get() << endl;}));
    scheduler.add(nineDOFSensor);
    scheduler.add(make_shared<FnRunnable>([](){nineDOFSensor.dump(mbedOut);}));
    while(true)
    {
        scheduler.update();
    }
}
