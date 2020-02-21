#if !defined(QUATERNION_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#include "blib_utils.h"

struct quat
{
    union
    {
        struct
        {
            r32 x;
            r32 y;
            r32 z;
            r32 w;
        };
        struct
        {
            v3 imaginary;
            r32 real;
        };
    };
};

flocal inline quat operator/(const quat& q, const r32 a)
{
    return {q.x / a, q.y / a, q.z / a, q.w / a};
}

flocal inline quat operator+(const quat& q_1, const quat& q_2)
{
    quat ret = {};
    ret.imaginary = q_1.imaginary + q_2.imaginary;
    ret.real = q_1.real + q_2.real;
    return ret;
}

flocal inline quat operator*(const quat& q_1, const quat& q_2)
{
    quat ret = {};
    ret.w = q_1.w * q_2.w - dot(q_1.imaginary, q_2.imaginary);
    ret.imaginary = q_1.w * q_2.imaginary + q_2.w * q_1.imaginary + cross(q_1.imaginary, q_2.imaginary);
    return ret;
}

flocal inline quat operator*(const float& a, const quat& q)
{
    return {q.x * a, q.y * a, q.z * a, q.w * a};
}

flocal inline quat operator*(const quat& q, const float& a)
{
    return {q.x * a, q.y * a, q.z * a, q.w * a};
}

flocal inline quat operator-(const quat& q_1, const quat& q_2)
{
    quat ret = {};
    ret.real = q_1.real - q_2.real;
    ret.imaginary = q_1.imaginary - q_2.imaginary;
    return ret;
}

flocal inline b32 operator==(const quat& q_1, const quat& q_2)
{
    return q_1.x == q_2.x && q_1.y == q_2.y && q_1.z == q_2.z && q_1.w == q_2.w;
}

flocal inline quat operator-(const quat& q)
{
    quat ret = {};
    ret.real = -q.real;
    ret.imaginary = -q.imaginary;
    return ret;
}

flocal inline quat from_v3(v3 imaginary, r32 w)
{
    return {imaginary.x, imaginary.y, imaginary.z, w};
}

flocal inline r32 sq_mag(const quat& q)
{
    return SQ(q.w) + SQ(q.x) + SQ(q.y) + SQ(q.z);
}

flocal inline quat normalize(const quat& q)
{
    r32 mag = sqrtf(sq_mag(q));
    return q / mag;
}

flocal inline quat inverse(const quat& q)
{
    return from_v3(-q.imaginary, q.real) / sq_mag(q);
}

flocal inline r32 dot(const quat& q_1, const quat& q_2)
{
    return q_1.w * q_2.w + q_1.x * q_2.x + q_1.y * q_2.y + q_1.z * q_2.z;
}

flocal inline quat lerp(quat a, quat b, const r32& t)
{
    return {mix(a.x, b.x, t),
            mix(a.y, b.y, t),
            mix(a.z, b.z, t),
            mix(a.w, b.w, t)};
}

flocal inline quat slerp(quat a, quat b, const r32& t)
{
    a = normalize(a);
    b = normalize(b);
    r32 dot_val = dot(a, b);
    if (dot_val < 0.f)
    {
        b = -1.f * b;
        dot_val = -dot_val;
    }

    if (dot_val > 1.0f - 0.001f)
    {
        return lerp(a,b,t);
    }
    else
    {
        float angle = acos(dot_val);
        return (sin((1.0f - t) * angle) * a + sin(t * angle) * b) / sin(angle);
    }
}


#define QUATERNION_H
#endif
