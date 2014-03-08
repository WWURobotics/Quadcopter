#include "mbedio.h"
#include "gtimer.h"
#include "scheduler.h"
#include "um6lt.h"
#include <string>

using namespace std;
using namespace quadcopter;

Scheduler scheduler;

UM6LT * nineDOFSensor = nullptr;

int main()
{
    nineDOFSensor = new UM6LT(PinName::p8, PinName::p5, PinName::p6, PinName::p7);
    scheduler.add(make_shared<FnRunnable>([](){mbedOut << "\n\x1b[K\n\x1b[K\n\x1b[K\x1b[H" << std::setprecision(9) << global_time::get() << "\x1b[K" << endl;}));
    scheduler.add(*nineDOFSensor);
    scheduler.add(*nineDOFSensor);
    scheduler.add(*nineDOFSensor);
    scheduler.add(make_shared<FnRunnable>([](){nineDOFSensor->dump(mbedOut);}));
    scheduler.add(*nineDOFSensor);
    scheduler.add(*nineDOFSensor);
    scheduler.add(*nineDOFSensor);
    while(true)
    {
        scheduler.update();
    }
}
