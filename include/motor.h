#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "output.h"

namespace quadcopter
{
class Motor : public SingleChannelOutput
{
public:
    Motor()
    {
    }
    virtual void dump(ostream & os) const override
    {
        os << "Motor : Speed = " << get() << "RPM\n";
    }
    virtual float maxSpeed() const = 0;
};
}

#endif // MOTOR_H_INCLUDED
