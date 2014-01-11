#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cmath>
#include <GL/gl.h>
#include "monitor.h"
#include <iostream>
#include <cstdlib>
#include <stdint.h>

namespace JRL
{
class Vector3D
{
public:
    float x, y, z;
    Vector3D(float x_in, float y_in, float z_in) : x(x_in), y(y_in), z(z_in) {}
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D operator +=(Vector3D b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }
    Vector3D operator -=(Vector3D b)
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }
    Vector3D operator *=(float b)
    {
        x *= b;
        y *= b;
        z *= b;
        return *this;
    }
    Vector3D operator /=(float b)
    {
        x /= b;
        y /= b;
        z /= b;
        return *this;
    }
};

inline float dot_prod(Vector3D a, Vector3D b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float abs_squared(Vector3D v)
{
    return dot_prod(v, v);
}

inline float abs(Vector3D v)
{
    return std::sqrt(abs_squared(v));
}

inline Vector3D operator *(Vector3D a, float b)
{
    return Vector3D(a.x * b, a.y * b, a.z * b);
}

inline Vector3D operator *(float a, Vector3D b)
{
    return operator *(b, a);
}

inline Vector3D operator /(Vector3D a, float b)
{
    return Vector3D(a.x / b, a.y / b, a.z / b);
}

inline Vector3D normalize(Vector3D v)
{
    float r = abs(v);
    if(r == 0) return Vector3D(0, 0, 0);
    return v / r;
}

inline Vector3D operator +(Vector3D a, Vector3D b)
{
    return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3D operator -(Vector3D a, Vector3D b)
{
    return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vector3D cross_prod(Vector3D a, Vector3D b)
{
    return Vector3D(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x);
}

inline bool operator ==(Vector3D a, Vector3D b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator !=(Vector3D a, Vector3D b)
{
    return a.x != b.x || a.y != b.y || a.z != b.z;
}

inline Vector3D operator -(Vector3D a)
{
    return Vector3D(-a.x, -a.y, -a.z);
}

inline void glVertex(Vector3D v)
{
    glVertex3f(v.x, v.y, v.z);
#ifdef DEBUG
    OnglVertex();
#endif
}

inline std::ostream & operator <<(std::ostream & os, Vector3D v)
{
    return os << v.x << " " << v.y << " " << v.z;
}

inline std::istream & operator >>(std::istream & is, Vector3D & v)
{
    return is >> v.x >> v.y >> v.z;
}

extern uint32_t CurrentRandom;

float FRand(uint32_t * randv = &CurrentRandom);

inline Vector3D VRand(uint32_t * randv = &CurrentRandom)
{
    Vector3D retval = Vector3D(FRand(randv) * 2 - 1, FRand(randv) * 2 - 1, FRand(randv) * 2 - 1);
    while(abs_squared(retval) > 1 || abs_squared(retval) < 0.001)
    {
        retval = Vector3D(FRand(randv) * 2 - 1, FRand(randv) * 2 - 1, FRand(randv) * 2 - 1);
    }
    return normalize(retval);
}
}

#endif // VECTOR_H_INCLUDED
