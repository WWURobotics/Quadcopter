#ifndef MOTOR_IMPLEMENTATION_H_INCLUDED
#define MOTOR_IMPLEMENTATION_H_INCLUDED

#include "motor.h"
#include "PinNames.h"
#include "PwmOut.h"
#include <cmath>

using namespace std;

namespace quadcopter
{
class MotorImplementation final : public Motor
{
private:
    float maxRPM, period;
    float a, b, c; // output value is a + speed * b + speed ^ 2 * c
    PwmOut pwmOut;
    float idleValue;
public:
    MotorImplementation(mbed::PinName pin, float maxRPM, float period, float a, float b, float c, float idleValue = -1)
        : maxRPM(maxRPM), period(period), a(a), b(b), c(c), pwmOut(pin), idleValue(idleValue == -1 ? a : idleValue)
    {
        pwmOut.period(period);
        pwmOut.write(0);
        set(0);
    }
    virtual void update() override final
    {
        float v = max(0.0f, min(maxRPM, get()));
        if(v == 0)
            v = idleValue;
        else
            v = a + v * b + v * v * c;
        pwmOut.write(v);
    }
    virtual float maxSpeed() const override final
    {
        return maxRPM;
    }
};
}

#endif // MOTOR_IMPLEMENTATION_H_INCLUDED
