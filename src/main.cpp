#include "mbedio.h"
#include "gtimer.h"
#include "scheduler.h"
#include "um6lt.h"
#include "motor_implementation.h"
#include "analog_input.h"
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
    MotorImplementation motor1(PinName::p21, 20000, 0.002, 0.99 * 8000/20000.0, 0.99 * (1.0 - 8000/20000.0) / 20000.0, 0, 7500/20000.0);
    MotorImplementation motor2(PinName::LED1, 20000, 0.002, 0.99 * 8000/20000.0, 0.99 * (1.0 - 8000/20000.0) / 20000.0, 0, 7500/20000.0);
    MotorImplementation motor3(PinName::LED2, 20000, 0.002, 0, 1 / 20000.0, 0);
    AnalogInput ain(PinName::p20, -50, 20100);
    scheduler.add(make_shared<FnRunnable>([&outStream](){outStream.str(""); outStream << "\x1b[K\n\x1b[K\n\x1b[K\n\x1b[K\x1b[H" << std::setprecision(9) << global_time::get() << "\x1b[K" << endl;}));
    scheduler.add(*nineDOFSensor);
    scheduler.add(motor1);
    scheduler.add(motor2);
    scheduler.add(motor3);
    scheduler.add(ain);
    scheduler.add(make_shared<FnRunnable>([&ain, &outStream, &motor1, &motor2, &motor3](){outStream << ain; *motor1 = ain.read(); outStream << motor1.calc() << "\x1b[K\n"; *motor2 = ain.read(); *motor3 = ain.read();}));
    //scheduler.add(make_shared<FnRunnable>([&outStream](){nineDOFSensor->dump(outStream);}));
    scheduler.add(make_shared<FnRunnable>([&outStream, &outString](){if(outString == "") outString = outStream.str(); if(outString != "") mbedOut << outString[0]; outString.erase(0, 1);}));
    while(true)
    {
        scheduler.update();
    }
}
