#include "ninedofsensor.h"
#include "gtimer.h"
#include "mbedio.h"
#include <assert.h>

namespace quadcopter
{

Vector3D gravityVector(0, -9.80665, 0);

NineDOFSensor::NineDOFSensor()
{
    m_tform = Matrix4x4::identity();
    m_vel = Vector3D(0, 0, 0);
    m_accel = Vector3D(0, 0, 0);
    lastTime = -1;
}

void NineDOFSensor::dump(ostream & os) const
{
    os << "NineDOFSensor:\x1b[K\n";
    os << "TransformationMatrix: " << m_tform << "\x1b[K\nVelocity: " << m_vel << "\x1b[K\nrel Acceleration: " << m_accel << "\x1b[K\nabs Acceleration: " << absAccel() << "\x1b[K\nLast Update Time :" << lastTime << "\x1b[K" << endl;
}

void NineDOFSensor::handleUpdate(Vector3D relativeAcceleration, Matrix4x4 normalizedRotation)
{
    double curTime = global_time::get();
    m_accel = relativeAcceleration;
    m_tform = setTranslation(normalizedRotation, getTranslation(m_tform));
    if(lastTime < 0)
    {
        lastTime = curTime;
        return;
    }
    float deltaTime = curTime - lastTime;
    lastTime = curTime;
    //mbedOut << "fixed acceleration : " << (absAccel() - gravityVector) << "\x1b[K" << endl;
    m_vel += deltaTime * (absAccel() - gravityVector);
    m_tform = setTranslation(normalizedRotation, getTranslation(m_tform) + deltaTime * m_vel);
}

}
