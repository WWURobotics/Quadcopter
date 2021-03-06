#ifndef SENSOR_H
#define SENSOR_H

#include <ostream>
#include "scheduler.h"

namespace quadcopter
{

using namespace std;

class Sensor : public Runnable
{
public:
    Sensor();
    virtual ~Sensor();

    virtual void update() = 0;
    virtual void dump(ostream & os) const = 0;
    friend ostream & operator <<(ostream & os, const Sensor & sensor)
    {
        sensor.dump(os);
        return os;
    }
protected:
private:
};

}

#endif // SENSOR_H
