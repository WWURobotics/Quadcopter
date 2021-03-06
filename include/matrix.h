#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "vector.h"

#include <cmath>

namespace quadcopter
{

class Matrix4x4
{
    float x[4][3];
public:
    Matrix4x4() {}
    Matrix4x4(float x00, float x10, float x20, float x30, float x01, float x11, float x21, float x31, float x02, float x12, float x22, float x32)
    {
        x[0][0] = x00;
        x[1][0] = x10;
        x[2][0] = x20;
        x[3][0] = x30;
        x[0][1] = x01;
        x[1][1] = x11;
        x[2][1] = x21;
        x[3][1] = x31;
        x[0][2] = x02;
        x[1][2] = x12;
        x[2][2] = x22;
        x[3][2] = x32;
    }
    static Matrix4x4 identity()
    {
        return Matrix4x4(1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0);
    }
    static Matrix4x4 zero()
    {
        return Matrix4x4(0, 0, 0, 0,
                         0, 0, 0, 0,
                         0, 0, 0, 0);
    }
    static Matrix4x4 fromNormalizedQuaternion(float a, float b, float c, float d)
    {
        return Matrix4x4(a * a + b * b - c * c - d * d, 2 * b * c - 2 * a * d, 2 * b * d + 2 * a * c, 0,
                         2 * b * c + 2 * a * d, a * a - b * b + c * c - d * d, 2 * c * d - 2 * a * b, 0,
                         2 * b * d - 2 * a * c, 2 * c * d + 2 * a * b, a * a - b * b - c * c + d * d, 0);
    }
    inline float & operator()(int xindex, int yindex)
    {
        static float errorval;
        if(xindex < 0 || xindex > 3 || yindex < 0 || yindex > 2)
        {
            errorval = 0.0;
            if(xindex == yindex) errorval = 1.0;
            return errorval;
        }
        return x[xindex][yindex];
    }
    inline const float & operator()(int xindex, int yindex) const
    {
        static float errorval;
        if(xindex < 0 || xindex > 3 || yindex < 0 || yindex > 2)
        {
            errorval = 0.0;
            if(xindex == yindex) errorval = 1.0;
            return errorval;
        }
        return x[xindex][yindex];
    }
    friend Matrix4x4 transpose(const Matrix4x4 & m);
    friend float determinant(const Matrix4x4 & m);
    friend Matrix4x4 invert(const Matrix4x4 & m);
    friend Vector3D apply(const Matrix4x4 & m, const Vector3D & v);
    friend Vector3D applyToNormal(const Matrix4x4 & m, const Vector3D & v);
    friend Matrix4x4 concat(const Matrix4x4 & a, const Matrix4x4 & b);
    static Matrix4x4 rotate(Vector3D axis, float angle)
    {
        float r = abs(axis);
        if(r == 0)
            return identity();
        axis /= r;

        float c, s, v;
        c = std::cos(angle);
        s = std::sin(angle);
        v = 1.0 - c; // versine

        float xx, xy, xz, yy, yz, zz;
        xx = axis.x * axis.x;
        xy = axis.x * axis.y;
        xz = axis.x * axis.z;
        yy = axis.y * axis.y;
        yz = axis.y * axis.z;
        zz = axis.z * axis.z;

        return Matrix4x4(xx + (1.0 - xx) * c, xy * v - axis.z * s, xz * v + axis.y * s, 0,
                         xy * v + axis.z * s, yy + (1.0 - yy) * c, yz * v - axis.x * s, 0,
                         xz * v - axis.y * s, yz * v + axis.x * s, zz + (1.0 - zz) * c, 0);
    }
    static Matrix4x4 rotatex(float angle)
    {
        return rotate(Vector3D(1, 0, 0), angle);
    }
    static Matrix4x4 rotatey(float angle)
    {
        return rotate(Vector3D(0, 1, 0), angle);
    }
    static Matrix4x4 rotatez(float angle)
    {
        return rotate(Vector3D(0, 0, 1), angle);
    }
    static Matrix4x4 translate(Vector3D position)
    {
        return Matrix4x4(1, 0, 0, position.x,
                         0, 1, 0, position.y,
                         0, 0, 1, position.z);
    }
    static Matrix4x4 translate(float x, float y, float z)
    {
        return translate(Vector3D(x, y, z));
    }
    static Matrix4x4 scale(float x, float y, float z)
    {
        return Matrix4x4(x, 0, 0, 0,
                         0, y, 0, 0,
                         0, 0, z, 0);
    }
    static Matrix4x4 scale(Vector3D s)
    {
        return scale(s.x, s.y, s.z);
    }
    static Matrix4x4 scale(float s)
    {
        return scale(s, s, s);
    }
    friend ostream & operator <<(ostream & os, const Matrix4x4 & m);
};

inline Matrix4x4 transpose(const Matrix4x4 & m)
{
    return Matrix4x4(m(0, 0), m(0, 1), m(0, 2), m(0, 3),
                     m(1, 0), m(1, 1), m(1, 2), m(1, 3),
                     m(2, 0), m(2, 1), m(2, 2), m(2, 3));
}

inline float determinant(const Matrix4x4 & m)
{
    return m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
           m(1, 0) * (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) +
           m(2, 0) * (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1));
}

inline Matrix4x4 invert(const Matrix4x4 & m)
{
    float det = determinant(m);
    if(det == 0.0)
        return Matrix4x4::zero();
    float factor = 1 / det;
    return Matrix4x4((m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) * factor,
                     (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * factor,
                     (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)) * factor,
                     (-m(1, 0) * m(2, 1) * m(3, 2) + m(1, 1) * m(2, 0) * m(3, 2) + m(1, 0) * m(2, 2) * m(3, 1) - m(1, 2) * m(2, 0) * m(3, 1) - m(1, 1) * m(2, 2) * m(3, 0) + m(1, 2) * m(2, 1) * m(3, 0)) * factor,

                     (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * factor,
                     (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * factor,
                     (m(0, 1) * m(2, 0) - m(0, 0) * m(2, 1)) * factor,
                     (m(0, 0) * m(2, 1) * m(3, 2) - m(0, 1) * m(2, 0) * m(3, 2) - m(0, 0) * m(2, 2) * m(3, 1) + m(0, 2) * m(2, 0) * m(3, 1) + m(0, 1) * m(2, 2) * m(3, 0) - m(0, 2) * m(2, 1) * m(3, 0)) * factor,

                     (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * factor,
                     (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) * factor,
                     (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * factor,
                     (-m(0, 0) * m(1, 1) * m(3, 2) + m(0, 1) * m(1, 0) * m(3, 2) + m(0, 0) * m(1, 2) * m(3, 1) - m(0, 2) * m(1, 0) * m(3, 1) - m(0, 1) * m(1, 2) * m(3, 0) + m(0, 2) * m(1, 1) * m(3, 0)) * factor);
}

inline Vector3D apply(const Matrix4x4 & m, const Vector3D & v)
{
    return Vector3D(v.x * m(0, 0) + v.y * m(1, 0) + v.z * m(2, 0) + m(3, 0),
                    v.x * m(0, 1) + v.y * m(1, 1) + v.z * m(2, 1) + m(3, 1),
                    v.x * m(0, 2) + v.y * m(1, 2) + v.z * m(2, 2) + m(3, 2));
}

inline Vector3D getTranslation(const Matrix4x4 & m)
{
    return Vector3D(m(3, 0), m(3, 1), m(3, 2));
}

inline Vector3D applyToNormal(const Matrix4x4 & m, const Vector3D & v)
{
    return Vector3D(v.x * m(0, 0) + v.y * m(1, 0) + v.z * m(2, 0),
                    v.x * m(0, 1) + v.y * m(1, 1) + v.z * m(2, 1),
                    v.x * m(0, 2) + v.y * m(1, 2) + v.z * m(2, 2));
}

inline Matrix4x4 concat(const Matrix4x4 & a, const Matrix4x4 & b)
{
    return Matrix4x4(a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
                     a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
                     a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
                     a(3, 0) * b(0, 0) + a(3, 1) * b(1, 0) + a(3, 2) * b(2, 0) + b(3, 0),
                     a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
                     a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
                     a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
                     a(3, 0) * b(0, 1) + a(3, 1) * b(1, 1) + a(3, 2) * b(2, 1) + b(3, 1),
                     a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),
                     a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),
                     a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2),
                     a(3, 0) * b(0, 2) + a(3, 1) * b(1, 2) + a(3, 2) * b(2, 2) + b(3, 2));
}

inline Matrix4x4 setTranslation(Matrix4x4 m, const Vector3D & translation)
{
    m(3, 0) = translation.x;
    m(3, 1) = translation.y;
    m(3, 2) = translation.z;
    return m;
}

inline ostream & operator <<(ostream & os, const Matrix4x4 & m)
{
    os << "\x1b[K" << endl;
    for(int y = 0; y < 4; y++)
    {
        os << "{";
        for(int x = 0; x < 4; x++)
        {
            os << " " << m(x, y);
        }
        os << " }\x1b[K\n";
    }
    return os << "\x1b[K" << endl;
}

inline Matrix4x4 rotationReflectionOnly(Matrix4x4 m)
{
    m = setTranslation(m, Vector3D(0, 0, 0));
    Vector3D vx = normalize(apply(m, Vector3D(1, 0, 0)));
    Vector3D vy = apply(m, Vector3D(0, 1, 0));
    Vector3D vz = apply(m, Vector3D(0, 0, 1));
    Vector3D newVY = normalize(cross_prod(vx, vz));
    if(dot_prod(newVY, vy) < 0)
    {
        newVY = -newVY;
    }
    Vector3D newVZ = normalize(cross_prod(vx, newVY));
    if(dot_prod(newVZ, vz) < 0)
    {
        newVZ = -newVZ;
    }
    Vector3D newVX = vx;
    return Matrix4x4(newVX.x, newVY.x, newVZ.x, 0,
                     newVX.y, newVY.y, newVZ.y, 0,
                     newVX.z, newVY.z, newVZ.z, 0);
}

}

#endif // MATRIX_H_INCLUDED
