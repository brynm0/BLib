#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include "CommonDefines.h"
#include "Vector.h"
struct RandomSeries
{
    u32 state;
};

flocal u32 xOrShift32(RandomSeries* series);
flocal r32 randomUnilateral(RandomSeries* series);
flocal v3 randomUnilateralV3(RandomSeries* series);
flocal inline r32 math_min(r32 a, r32 b);
flocal inline r32 math_max(r32 a, r32 b);
flocal inline r32 clamp_r32(r32 a, r32 low, r32 high);
flocal inline r32 sqDist(const v3& a, const v3& b);
flocal inline r32 sqDist(const v2& a, const v2& b);
flocal inline r32 fast_fabs(r32 x);
flocal inline r32 sqLen(v3 vec);
flocal inline r32 sqLen(v2 vec);
flocal inline u32 ceiling(r32 num);
flocal b32 is_inside_quad(v2 top_left, v2 bottom_right, v2 point);
flocal inline void limit(v3* toLimit, const r32& limiter);
#if 0
flocal void limit (v3* toLimit, const r32& limiter)
{
    r32 toLimitLenSq = sqLen(*toLimit);
    if (toLimitLenSq > limiter * limiter)
    {
        *toLimit *= (limiter*limiter) / toLimitLenSq;
    }
}
#endif
#endif
