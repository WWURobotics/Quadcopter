#ifndef UM6LT_H_INCLUDED
#define UM6LT_H_INCLUDED

#include "ninedofsensor.h"
#include "mbed2/mbed.h"

namespace quadcopter
{
class UM6LT final : public NineDOFSensor
{
private:
    mbed::SPI spi;
    mbed::DigitalOut select;
public:
    explicit UM6LT(mbed::PinName select, mbed::PinName mosi, mbed::PinName miso, mbed::PinName sck);
    virtual void update() override;
};
}

#endif // UM6LT_H_INCLUDED
