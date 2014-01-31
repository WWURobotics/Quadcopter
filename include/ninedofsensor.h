#ifndef NINEDOFSENSOR_H
#define NINEDOFSENSOR_H

#include "sensor.h"
#include "matrix.h"

class NineDOFSensor : public Sensor
{
public:
    NineDOFSensor();
    virtual ~NineDOFSensor();
    virtual void update() = 0;
    virtual void dump(ostream & os) const;
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
    void tform(const Matrix4x4 v)
    {
        m_tform = v;
    }
    void rawAccel(const Vector3D v)
    {
        m_accel = v;
    }
    void absVel(const Vector3D v)
    {
        m_vel = v;
    }
    void handleUpdate();
private:
    Matrix4x4 m_tform;
    Vector3D m_accel;
    Vector3D m_vel;
};

#endif // NINEDOFSENSOR_H
