#if !defined(RAY_WIDE_4_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#include <intrin.h>
//#include <avxintrin.h>
#include <math.h>
#define USE_SSE2
#include "sse_mathfun_extension.h"
#include <assert.h>
#include "CommonDefines.h"
#include "Vector.h"
#define LANE_WIDTH 4
struct lane_r32
{
    __m128 v;
};

struct lane_u32
{
    __m128i v;    
};

struct LaneRandomSeries
{
    lane_u32 state;
};

struct lane_v2
{
    union
    {
        struct
        {
            lane_r32 x;
            lane_r32 y;
        };
        struct
        {
            lane_r32 u;
            lane_r32 v;
        };
        struct
        {
            lane_r32 r;
            lane_r32 g;
        };
        struct
        {
            __m128 mX;    
            __m128 mY;    
        };
    };
};

struct lane_v3
{
    union
    {
        struct
        {
            lane_r32 x;
            lane_r32 y;
            lane_r32 z;
        };
        struct
        {
            lane_r32 r;
            lane_r32 g;
            lane_r32 b;
        };
        struct
        {
            lane_r32 u;
            lane_r32 v;
            lane_r32 w;
        };
        struct
        {
            __m128 mX;    
            __m128 mY;    
            __m128 mZ;
        };
    };
};

struct lane_v4
{
    union
    {
        struct
        {
            lane_r32 x;
            lane_r32 y;
            lane_r32 z;
            lane_r32 w;
        };
        struct
        {
            lane_r32 r;
            lane_r32 g;
            lane_r32 b;
            lane_r32 a;
        };
        struct
        {
            __m128 mX;    
            __m128 mY;    
            __m128 mZ;
            __m128 mW;
        };
    };
};

flocal inline lane_v3 lv3(lane_r32 a, lane_r32 b, lane_r32 c)
{
    return {a, b, c};
}

flocal inline lane_v4 laneV4(lane_v3 a, lane_r32 b)
{
    return {a.x, a.y, a.z, b};
}

flocal inline lane_v3 loadCopy(v3 vec)
{
    lane_v3 result = {};
    result.mX = _mm_load_ps1(&vec.x);
    result.mY = _mm_load_ps1(&vec.y);
    result.mZ = _mm_load_ps1(&vec.z);
    return result;
}

flocal inline lane_r32 loadCopy(r32 toLoad)
{
    lane_r32 result = {};
    result.v = _mm_load_ps1(&toLoad);
    return result;
}

flocal inline lane_v4 fromLaneR32(lane_r32 x, lane_r32 y, lane_r32 z, lane_r32 w)
{
    return {x,y,z,w};
}

flocal inline lane_u32 loadCopy(u32 toLoad)
{
    __m128i out = _mm_set1_epi32(toLoad);
    return {out};
}

flocal inline lane_u32 loadCopy(int toLoad)
{
    //assert(toLoad >= 0);
    return loadCopy((u32)toLoad);
}

flocal  lane_u32
operator<<(lane_u32 A, u32 Shift)
{
    lane_u32 Result;
    
    Result.v = _mm_slli_epi32(A.v, Shift);
    
    return(Result);
}

flocal lane_u32
operator>>(lane_u32 A, u32 Shift)
{
    lane_u32 Result;
    
    Result.v = _mm_srli_epi32(A.v, Shift);
    
    return(Result);
}

inline lane_u32& operator^=(lane_u32& l, const lane_u32& r)
{
    l.v = _mm_xor_si128(l.v, r.v);
    return l;
}

flocal lane_u32 xorShift(LaneRandomSeries* series)
{
    lane_u32 x = series->state;
    x ^= x << 13;
    
    x ^= x >> 17;
    x ^= x << 5;
    series->state = x;
    return x;
}

flocal lane_u32
laneU32FromU32(u32 repl)
{
    lane_u32 result;
    
    result.v = _mm_set1_epi32(repl);
    
    return result;
}

flocal lane_u32
laneU32FromU32(u32 r0, u32 r1, u32 r2, u32 r3)
{
    lane_u32 result;
    
    result.v = _mm_set_epi32(r0, r1, r2, r3);
    
    return result;
}

flocal lane_r32
laneR32FromU32(lane_u32 a)
{
    lane_r32 result;
    
    result.v = _mm_cvtepi32_ps(a.v);
    
    return result;
}

inline lane_u32
operator&&(const lane_u32& lhs, const lane_u32& rhs)
{
    return {_mm_and_si128(lhs.v, rhs.v)};
}

inline lane_u32
operator&&(const lane_r32& lhs, const lane_r32& rhs)
{
    return {_mm_castps_si128(_mm_and_ps(lhs.v, rhs.v))};
}

inline lane_r32 operator-(const lane_r32& lhs)
{
    return {_mm_sub_ps(loadCopy(0.0f).v, lhs.v)};
}

inline lane_v3 operator-(const lane_v3& l)
{
    return {-l.x, -l.y, -l.z};
}

flocal inline lane_r32 sqrt(lane_r32 a)
{
    return {_mm_sqrt_ps(a.v)};
}

flocal inline lane_u32 laneR32ToLaneU32(lane_r32 toCast)
{
    return {_mm_cvtps_epi32(toCast.v)};
}

flocal inline void conditionalAssign(lane_u32* lane, lane_u32 mask, lane_u32 toAssign)
{
    lane->v = _mm_or_si128(_mm_andnot_si128(mask.v, lane->v), _mm_and_si128(mask.v, toAssign.v));
}

flocal inline void conditionalAssign(lane_r32* lane, lane_u32 mask, lane_r32 source)
{
    __m128 psMask = _mm_castsi128_ps(mask.v);
    lane->v = _mm_or_ps(_mm_andnot_ps(psMask, lane->v), _mm_and_ps(psMask, source.v));
}

flocal inline void conditionalAssign(lane_v3* lane, lane_u32 mask, lane_v3 toAssign)
{
    conditionalAssign(&lane->x, mask, toAssign.x);
    conditionalAssign(&lane->y, mask, toAssign.y);
    conditionalAssign(&lane->z, mask, toAssign.z);
}

flocal inline void conditionalAssign(lane_v4* lane, lane_u32 mask, lane_v4 toAssign)
{
    conditionalAssign(&lane->x, mask, toAssign.x);
    conditionalAssign(&lane->y, mask, toAssign.y);
    conditionalAssign(&lane->z, mask, toAssign.z);
    conditionalAssign(&lane->w, mask, toAssign.w);
}

flocal inline r32 horizontalAdd(__m128 v)
{
    __m128 shuf   = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1));  // [ C D | A B ]
    __m128 sums   = _mm_add_ps(v, shuf);      // sums = [ D+C C+D | B+A A+B ]
    shuf          = _mm_movehl_ps(shuf, sums);      //  [   C   D | D+C C+D ]  // let the compiler avoid a mov by reusing shuf
    sums          = _mm_add_ss(sums, shuf);
    return    _mm_cvtss_f32(sums);   
}

#define LANE_V4_TRANSPOSE(vec) _MM_TRANSPOSE4_PS(vec.x.v, vec.y.v, vec.z.v, vec.w.v)

flocal inline v3
horizontalAdd(lane_v3 l)
{
    return {horizontalAdd(l.mX), horizontalAdd(l.mY), horizontalAdd(l.mZ)};
}

flocal inline
lane_r32 min(lane_r32 a, lane_r32 b)
{
    lane_r32 result = {};
    result.v = _mm_min_ps(a.v, b.v);
    return result;
}

flocal inline lane_r32 laneMax(lane_r32 a, lane_r32 b)
{
    
    lane_r32 result = {};
    result.v = _mm_max_ps(a.v, b.v);
    return result;
}

inline lane_u32
operator+(const lane_u32& l, const lane_u32& r)
{
    return {_mm_add_epi32(l.v, r.v)};
}

inline lane_v3
operator+(const lane_v3& l, const lane_v3& r)
{
    return {_mm_add_ps(l.mX,r.mX),
            _mm_add_ps(l.mY,r.mY),
            _mm_add_ps(l.mZ,r.mZ)};
}

inline lane_r32 floor(lane_r32 x)
{
    __m128 f = x.v;
    const __m128 one = _mm_set_ss(1.0f);
    __m128 t = _mm_cvtepi32_ps(_mm_cvttps_epi32(f));
    __m128 r = _mm_sub_ps(t, _mm_and_ps(_mm_cmplt_ps(f, t), one));
    return {r};
}

inline lane_v3
operator-(const lane_v3& l, const lane_v3& r)
{
    return {_mm_sub_ps(l.mX,r.mX),
            _mm_sub_ps(l.mY,r.mY),
            _mm_sub_ps(l.mZ,r.mZ)};
}

inline lane_r32
operator*(const lane_r32& l, const lane_r32& r)
{
    return {_mm_mul_ps(l.v,r.v)};
}

inline lane_u32
operator*(const lane_u32& l, const lane_u32& r)
{
    __m128i result = _mm_mullo_epi32(l.v,r.v);
    return {result};
}

inline lane_v3
operator*(const lane_v3& l, const lane_r32& r)
{
    return {l.x * r,
            l.y * r,
            l.z * r};
}

inline lane_v3
operator*(const lane_r32& l, const lane_v3& r)
{
    return r * l;
}

inline lane_v3
operator*(const lane_v3& l, const r32& r)
{
    lane_r32 copied = loadCopy(r);
    return {l.x * copied,
            l.y * copied,
            l.z * copied};
}

inline lane_r32
operator*(const r32& l, const lane_r32& r)
{
    lane_r32 copyVec = loadCopy(l);
    return {_mm_mul_ps(copyVec.v,r.v)};
}

inline lane_r32
operator*(const lane_r32& l, const r32& r)
{
    return r*l;
}

inline b32 maskZeroed(lane_u32 a)
{
    int mask = _mm_movemask_epi8(a.v);
    return mask == 0;
}

flocal u64 horizontalAdd(lane_u32 a)
{
    u32* v = (u32*)&a.v;
    u64 result = (u64)v[0] + (u64)v[1] + (u64)v[2] + (u64)v[3];
    return result;
}

inline lane_r32
operator+(const lane_r32& l, const lane_r32& r)
{
    return {_mm_add_ps(l.v,r.v)};
}

inline flocal lane_r32
operator+(const lane_r32& l, const r32& r)
{
    lane_r32 f = loadCopy(r);
    return {_mm_add_ps(l.v,f.v)};
}

inline flocal lane_r32 dot(lane_v3 l, lane_v3 r)
{
    lane_r32 x = l.x * r.x;
    lane_r32 y = l.y * r.y;
    lane_r32 z = l.z * r.z;
    return x + y + z;
}

inline flocal lane_r32 lenSq(lane_v3 v)
{
    return dot(v,v);
}

inline lane_r32
operator-(const lane_r32& l, const lane_r32& r)
{
    return {_mm_sub_ps(l.v,r.v)};
}

inline lane_r32
operator-(const r32& l, const lane_r32& r)
{
    lane_r32 l2 = loadCopy(l);
    return {_mm_sub_ps(l2.v,r.v)};
}

inline flocal lane_r32 sin(lane_r32 x)
{
    return {sin_ps(x.v)};
}

inline flocal lane_r32 cos(lane_r32 x)
{
    return {cos_ps(x.v)};
}

inline flocal lane_r32 asin(lane_r32 x)
{
    const lane_r32 a0 = loadCopy(1.5707288f);
    const lane_r32 a1 = loadCopy(-0.2121144f);
    const lane_r32 a2 = loadCopy(0.0742610f);
    const lane_r32 a3 = loadCopy(-0.0187293f);
    lane_r32 result =
        PI(0.5f) - sqrt(1.0f - x) * (a0 + a1 * x + a2 * x * x + a3 * x * x * x);
    return result;
}

flocal inline lane_r32 atan2(const lane_r32& a, const lane_r32& b)
{
# if 1
    return {atan2_ps(a.v, b.v)};
# else
    r32* a1 = (r32*)&a;
    r32* b1 = (r32*)&b;
    __m128 result = _mm_setr_ps(atan2(a1[0], b1[0]),
                                atan2(a1[1], b1[1]),
                                atan2(a1[2], b1[2]),
                                atan2(a1[3], b1[3]));
    return {result};
# endif
}

inline flocal lane_r32 acos(lane_r32 x)
{
# if 1
    lane_r32 halfPi = loadCopy(PI(0.5f));
    return {asin(halfPi - x)};
# else
    
    r32* a = (r32*)&x;
    __m128 result = _mm_setr_ps(cos(a[0]),
                                cos(a[1]),
                                cos(a[2]),
                                cos(a[3]));
# endif
    
}

inline lane_v3
lerp(lane_v3 a, lane_v3 b, lane_r32 t)
{
    return a * (loadCopy(1.0f)-t) + b * t;
}

inline lane_u32
operator>(const lane_r32& l, const lane_r32& r)
{
    return {_mm_castps_si128(_mm_cmpgt_ps(l.v,r.v))};
}

inline lane_u32
operator<(const lane_r32& l, const lane_r32& r)
{
    __m128i result = _mm_castps_si128(_mm_cmplt_ps(l.v,r.v));
    return {result};
}

inline lane_u32
operator<(const int& l, const lane_r32& r)
{
    return loadCopy((r32)l) < r;
}

inline lane_u32
operator<(const lane_r32& r, const int& l)
{
    return r < loadCopy((r32)l);
}

inline lane_r32
operator&(const lane_r32& l, const lane_r32& r)
{
    return {_mm_and_ps(l.v, r.v)};
}

inline lane_u32
operator&(const lane_u32& l, const lane_u32& r)
{
    return {_mm_and_si128(l.v, r.v)};
}

inline lane_u32& operator+=(lane_u32& l, const lane_u32& r)
{
    l = l + r;
    return l;
}

inline lane_v3& operator+=(lane_v3& l, const lane_v3& r)
{
    l = l + r;
    return l;
}

inline lane_r32& operator+=(lane_r32& l, const lane_r32& r)
{
    l = l + r;
    return l;
}

inline lane_r32& operator-=(lane_r32& l, const lane_r32& r)
{
    l = l - r;
    return l;
}

inline lane_r32& operator&=(lane_r32& l, const lane_r32& r)
{
    l.v = _mm_and_ps(l.v, r.v);
    return l;
}

inline lane_u32& operator&=(lane_u32& l, const lane_u32& r)
{
    l.v = _mm_and_si128(l.v, r.v);
    return l;
}

inline lane_u32 operator^(lane_u32& l, lane_u32& r)
{
    __m128i ret = _mm_xor_si128(l.v, r.v);
    return {ret};
}

inline lane_r32 operator^(lane_r32& l, lane_r32& r)
{
    
    return{_mm_xor_ps(l.v, r.v)};
}

inline lane_u32 operator!(lane_u32& r)
{
    lane_u32 ff = loadCopy(0xffffffff);
    return ff ^ r;
}

inline lane_r32 operator!(lane_r32& r)
{
    lane_r32 ff = {_mm_castsi128_ps(loadCopy(0xffffffff).v)};
    return ff ^ r;
}

inline lane_r32 operator&(lane_r32& l, const lane_r32& r)
{
    return {_mm_and_ps(l.v,r.v)};
}

inline lane_r32 operator/(lane_r32& l, const lane_r32& r)
{
    return {_mm_div_ps(l.v, r.v)};
}

inline lane_r32 operator/(lane_r32& l, const r32& r)
{
    lane_r32 f = loadCopy(r);
    return {_mm_div_ps(l.v, f.v)};
}

inline lane_v3 operator/(lane_v3& l, const lane_r32& r)
{
    
    return {l.x / r, l.y / r, l.z / r};
}

inline lane_r32 abs(lane_r32 v)
{
    const __m128 absMask = _mm_castsi128_ps(_mm_set1_epi32(~(1<<31)));
    return {_mm_and_ps(absMask, v.v)};
}

inline lane_v3 normalize(lane_v3 v)
{
#if 1
    lane_r32 len = {_mm_sqrt_ps(dot(v,v).v)};
    return v / len;
#else
    lane_r32 rLen = {_mm_rsqrt_ps(lenSq(v).v)};
    return v * rLen;
#endif
}

flocal lane_r32 randomUnilateralLane(LaneRandomSeries* series)
{
    lane_r32 result = laneR32FromU32(xorShift(series) >> 1) / (r32)(U32_MAX >> 1);
    return result;
}

flocal inline lane_r32 randomBilateralLane(LaneRandomSeries* series)
{
    lane_r32 result = randomUnilateralLane(series) * 2.0f + -1.0f;
    return result;
}

flocal inline lane_v3
randomBilateralLaneVector(LaneRandomSeries* series)
{
    return {randomBilateralLane(series), randomBilateralLane(series), randomBilateralLane(series)};
}

inline lane_r32 operator!=(lane_r32& l, const lane_r32& r)
{
    return {_mm_cmpneq_ps(l.v,r.v)};
}

inline lane_u32 operator==(lane_u32& l, const lane_u32& r)
{
    return {_mm_cmpeq_epi32(l.v,r.v)};
}

inline lane_u32 operator!=(lane_u32& l, const lane_u32& r)
{
    lane_u32 eq = l == r;
    
    return {!eq};
}

inline lane_r32 operator==(const lane_r32& l, const lane_r32& r)
{
    return {_mm_cmpeq_ps(l.v,r.v)};
}

flocal inline lane_v3 hadamard(lane_v3 a, lane_v3 b)
{
    lane_v3 out = {};
    out.x = a.x * b.x;
    out.y = a.y * b.y;
    out.z = a.z * b.z;
    return out;
}

flocal lane_u32
gatherU32(void* bp, lane_u32 indices)
{
    u32 stride = sizeof(u32);
    lane_u32 result;
    u32 *v = (u32 *)&indices.v;
    
    result.v = _mm_setr_epi32(*(u32 *)((u8 *)bp + v[0]*stride), 
                              *(u32 *)((u8 *)bp + v[1]*stride), 
                              *(u32 *)((u8 *)bp + v[2]*stride), 
                              *(u32 *)((u8 *)bp + v[3]*stride));
    
    return result;
}

flocal lane_r32
indexR32(r32* array, lane_u32 indices)
{
    lane_r32 result;
    u32* v = (u32*)&indices.v;
    result.v = _mm_setr_ps(array[v[0]],
                           array[v[1]],
                           array[v[2]],
                           array[v[3]]);
    return result;
}

flocal lane_r32
gatherR32(void *basePtr, u32 stride, lane_u32 indices)
{
    lane_r32 result;
    u32 *v = (u32 *)&indices.v;
    
    result.v = _mm_setr_ps(*(r32 *)((u8 *)basePtr + v[0]*stride), 
                           *(r32 *)((u8 *)basePtr + v[1]*stride), 
                           *(r32 *)((u8 *)basePtr + v[2]*stride), 
                           *(r32 *)((u8 *)basePtr + v[3]*stride));
    
    return result;
}

flocal lane_v3 gatherV3(v3* basePtr, lane_u32 index)
{
    u32 stride = sizeof(v3);
    lane_v3 result = {};
    result.x = gatherR32((r32*)basePtr + 0, stride, index);
    result.y = gatherR32((r32*)basePtr + 1, stride, index);
    result.z = gatherR32((r32*)basePtr + 2, stride, index);
    return result;
}

flocal lane_v4 gatherV4(v4* basePtr, lane_u32 index)
{
    u32 stride = sizeof(v4);
    lane_v4 result = {};
    result.x = gatherR32((r32*)basePtr + 0, stride, index);
    result.y = gatherR32((r32*)basePtr + 1, stride, index);
    result.z = gatherR32((r32*)basePtr + 2, stride, index);
    result.w = gatherR32((r32*)basePtr + 3, stride, index);
    return result;
}

flocal lane_v3 gatherV4asV3(v4* basePtr, lane_u32 index)
{
    u32 stride = sizeof(v4);
    lane_v3 result = {};
    result.x = gatherR32((r32*)basePtr + 0, stride, index);
    result.y = gatherR32((r32*)basePtr + 1, stride, index);
    result.z = gatherR32((r32*)basePtr + 2, stride, index);
    return result;
}

inline lane_v3
reflectVec(lane_v3 v, lane_v3 n)
{
    lane_v3 nDot = (n * dot(v, n));
    return v - nDot * loadCopy(2.0f);
}

flocal __forceinline __m128 LeftPack_SSE2(__m128 val, int mask)  {
  switch(mask) {
  case  0:
  case  1: return val;
  case  2: return _mm_shuffle_ps(val,val,0x01);
  case  3: return val;
  case  4: return _mm_shuffle_ps(val,val,0x02);
  case  5: return _mm_shuffle_ps(val,val,0x08);
  case  6: return _mm_shuffle_ps(val,val,0x09);
  case  7: return val;
  case  8: return _mm_shuffle_ps(val,val,0x03);
  case  9: return _mm_shuffle_ps(val,val,0x0c);
  case 10: return _mm_shuffle_ps(val,val,0x0d);
  case 11: return _mm_shuffle_ps(val,val,0x34);
  case 12: return _mm_shuffle_ps(val,val,0x0e);
  case 13: return _mm_shuffle_ps(val,val,0x38);
  case 14: return _mm_shuffle_ps(val,val,0x39);
  case 15: return val;
  }
}

flocal __forceinline lane_r32 pack(lane_r32 val, lane_r32 maskv) {
  int mask = _mm_movemask_ps(maskv.v);
  __m128 ret = LeftPack_SSE2(val.v, mask);
  ret = _mm_shuffle_ps(ret, ret,_MM_SHUFFLE(0,1,2,3));
  return {ret};
}

flocal __forceinline lane_v4 packV4(lane_v4 p, lane_r32 maskv)
{
    lane_v4 ret = {};
    ret.x = pack(p.x, maskv);
    ret.y = pack(p.y, maskv);
    ret.z = pack(p.z, maskv);
    ret.w = pack(p.w, maskv);
    return ret;
}

#define RAY_WIDE_4_H
#endif
