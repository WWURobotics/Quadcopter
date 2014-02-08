#include "ninedofsensor.h"
#include "gtimer.h"
#include <assert.h>

namespace quadcopter
{

NineDOFSensor::NineDOFSensor()
{
    m_tform = Matrix4x4::identity();
    m_vel = Vector3D(0, 0, 0);
    m_accel = Vector3D(0, 0, 0);
}

void NineDOFSensor::dump(ostream & os) const
{

}

}
