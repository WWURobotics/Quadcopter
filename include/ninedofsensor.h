#ifndef NINEDOFSENSOR_H
#define NINEDOFSENSOR_H

#include "sensor.h"
#include "matrix.h"

namespace quadcopter
{
extern Vector3D gravityVector;
inline float convertFromGsToMetersPerSecondSquared(float v)
{
    return v * 9.80665;
}
inline Vector3D convertFromGsToMetersPerSecondSquared(Vector3D v)
{
    return v * 9.80665;
}
class NineDOFSensor : public Sensor
{
public:
    NineDOFSensor();
    virtual void update() = 0;
    virtual void dump(ostream & os) const override;
    const Matrix4x4 tform() const
    {
        return m_tform;
    }
    const Vector3D rawAccel() const
    {
        return m_accel;
    }
    const Vector3D absAccel() const
    {
        return applyToNormal(m_tform, m_accel);
    }
    const Vector3D absVel() const
    {
        return m_vel;
    }
protected:
    void handleUpdate(Vector3D relativeAcceleration, Matrix4x4 normalizedRotation);
private:
    Matrix4x4 m_tform;
    Vector3D m_accel;
    Vector3D m_vel;
    double lastTime;
};

}

#endif // NINEDOFSENSOR_H
