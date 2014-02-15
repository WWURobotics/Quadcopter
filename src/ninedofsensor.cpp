#include "ninedofsensor.h"
#include "gtimer.h"
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
    os << "NineDOFSensor:\n";
    os << "TransformationMatrix: " << m_tform << "\nVelocity: " << m_vel << "\nrel Acceleration: " << m_accel << "\nLast Update Time :" << lastTime << endl;
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
    m_vel += deltaTime * (absAccel() - gravityVector);
    m_tform = setTranslation(normalizedRotation, getTranslation(m_tform) + deltaTime * m_vel);
}

}
