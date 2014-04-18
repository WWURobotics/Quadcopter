#ifndef ANALOG_INPUT_H_INCLUDED
#define ANALOG_INPUT_H_INCLUDED

#include "sensor.h"
#include "AnalogIn.h"
#include "PinNames.h"

namespace quadcopter
{
class AnalogInput final : public Sensor
{
    mbed::AnalogIn in;
    float minValue, maxValue, v;
public:
    AnalogInput(PinName pin, float minValue, float maxValue)
        : in(pin), minValue(minValue), maxValue(maxValue)
    {
    }
    AnalogInput(PinName pin)
        : in(pin), minValue(0), maxValue(1)
    {
    }
    virtual void update() override
    {
        v = in.read() * (maxValue - minValue) + minValue;
    }
    float read() const
    {
        return v;
    }
    virtual void dump(ostream & os) const override
    {
        os << "Analog Input : " << v << "\x1b[K\n";
    }
};
}

#endif // ANALOG_INPUT_H_INCLUDED
