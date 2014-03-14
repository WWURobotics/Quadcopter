#include "mbedio.h"
#include "gtimer.h"
#include "scheduler.h"
#include "um6lt.h"
#include <string>
#include <sstream>

using namespace std;
using namespace quadcopter;

Scheduler scheduler;

UM6LT * nineDOFSensor = nullptr;

int main()
{
    stringstream outStream;
    string outString = "";
    nineDOFSensor = new UM6LT(PinName::p8, PinName::p5, PinName::p6, PinName::p7);
    scheduler.add(make_shared<FnRunnable>([&outStream](){outStream.str(""); outStream << "\n\x1b[K\n\x1b[K\n\x1b[K\x1b[H" << std::setprecision(9) << global_time::get() << "\x1b[K" << endl;}));
    scheduler.add(*nineDOFSensor);
    scheduler.add(make_shared<FnRunnable>([&outStream](){nineDOFSensor->dump(outStream);}));
    scheduler.add(make_shared<FnRunnable>([&outStream, &outString](){if(outString == "") outString = outStream.str(); if(outString != "") mbedOut << outString[0]; outString.erase(0, 1);}));
    while(true)
    {
        scheduler.update();
    }
}
