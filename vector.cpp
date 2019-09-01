/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#include "CommonDefines.h"
#include "Vector.h"
#include "Matrix.h"
#define p1 73856093
#define p2 19349663
#define p3 83492791
#define p4 305175781

inline size_t v2hash(v2 v)
{
    return ((u64)v.x * p1) ^ ((u64)v.y * p3);
}

inline size_t v3hash(v3 v)
{
    return ((u64)v.x * p1) ^ (u64)((u64)v.y * p2) ^ ((u64)v.z * p3);
}

inline size_t v4hash(v4 v)
{
    return ((u64)v.x * p1) ^ ((u64)v.y * p2) ^ ((u64)v.z * p3) ^ ((u64)v.w * p4);
}

namespace std
{
	template<> struct hash<v2>
	{
		size_t operator()(v2 const& v) const
		{
			return v2hash(v);
		}
	};
	template<> struct hash<v3>
	{
		size_t operator()(v3 const& v) const
		{
			return v3hash(v);
		}
	};
	template<> struct hash<v4>
	{
		size_t operator()(v4 const& v) const
		{
			return v4hash(v);
		}
	};
}

inline v3 normalize(const v3& a)
{
    return a / sqrtf(sqLen(a));
}

inline r32 dot(const v3& a, const v3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline v3 rotate (const v3& v, const r32& angle, const v3& axis)
{
    return m4tom3(rotate(angle, axis)) * v;
    r32 cos_theta = cosf(angle);
    r32 sin_theta = sinf(angle);
    v3 rotated = (v * cos_theta) + (cross(axis, v) * sin_theta) + (axis * dot(axis, v)) * (1 - cos_theta);
    return rotated;
}
