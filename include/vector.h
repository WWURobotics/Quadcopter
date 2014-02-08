#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdint.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif // M_PI

namespace quadcopter
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

inline std::ostream & operator <<(std::ostream & os, Vector3D v)
{
    return os << v.x << " " << v.y << " " << v.z;
}

inline std::istream & operator >>(std::istream & is, Vector3D & v)
{
    return is >> v.x >> v.y >> v.z;
}

}

#endif // VECTOR_H_INCLUDED
