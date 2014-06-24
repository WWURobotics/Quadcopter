#ifndef MPU6050_NINEDOFSENSOR_H_INCLUDED
#define MPU6050_NINEDOFSENSOR_H_INCLUDED

#include "MPU6050.h"
#include "ninedofsensor.h"
#include "gtimer.h"

namespace quadcopter
{

class Mpu6050 : public NineDOFSensor
{
    MPU6050 sensor;
    Matrix4x4 rotationMatrix;
    double lastUpdateTime;
public:
    Mpu6050(PinName sda, PinName scl)
        : sensor(sda, scl), rotationMatrix(Matrix4x4::identity())
    {
        lastUpdateTime = global_time::get();
    }
    virtual void update()
    {
        double currentTime = global_time::get();
        float deltaTime = currentTime - lastUpdateTime;
        lastUpdateTime = currentTime;
        float rotationRates[3];
        sensor.getGyro(rotationRates);
        float acceleration[3];
        sensor.getAccelero(acceleration);
        rotationMatrix = concat(rotationMatrix, Matrix4x4::rotatex(rotationRates[0] * deltaTime));
        rotationMatrix = concat(rotationMatrix, Matrix4x4::rotatey(rotationRates[1] * deltaTime));
        rotationMatrix = concat(rotationMatrix, Matrix4x4::rotatez(rotationRates[2] * deltaTime));
        rotationMatrix = rotationReflectionOnly(rotationMatrix);
        handleUpdate(Vector3D(acceleration[0], acceleration[1], acceleration[2]), rotationMatrix);
    }
};

}

#endif // MPU6050_NINEDOFSENSOR_H_INCLUDED
