#ifndef UM6LT_H_INCLUDED
#define UM6LT_H_INCLUDED

#include "ninedofsensor.h"
#include "PinNames.h"
#include "SPI.h"
#include "DigitalOut.h"

namespace quadcopter
{
class UM6LT final : public NineDOFSensor
{
private:
    mbed::SPI spi;
    mbed::DigitalOut select;
public:
    explicit UM6LT(PinName select, PinName mosi, PinName miso, PinName sck);
    virtual void update() override;
};
}

#endif // UM6LT_H_INCLUDED
