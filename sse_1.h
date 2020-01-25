#if !defined(RAY_WIDE_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#include "CommonDefines.h"

struct lane_r32
{
    union
    {
        struct
        {
            r32 x;
        };
        struct
        {
            r32 v;
        };
    };
};

struct lane_u32
{
    union
    {
        struct
        {
            u32 x;
        };
        struct
        {
            u32 v;
        };
    };
};

struct lane_v3
{
    union
    {
        struct
        {
            r32 x;
            r32 y;
            r32 z;
        };
        struct
        {
            r32 mX;
            r32 mY;
            r32 mZ;
        };
    };  
};

#define LANE_WIDTH 1
flocal inline void conditionalAssign(lane_u32* lane, lane_u32 mask, lane_u32 toAssign)
{
    mask = {mask.v ? 0xFFFFFFFF : 0};
    lane->v = (~(mask.v) & lane->v) | (mask.v & toAssign.v);
}

flocal inline void conditionalAssign(lane_r32* lane, lane_u32 mask, lane_r32 source)
{
    conditionalAssign((lane_u32*)lane, mask, *(lane_u32*)&source);
}

flocal inline void conditionalAssign(lane_v3* lane, lane_u32 mask, lane_v3 toAssign)
{
    mask.v = mask.v ? 0xFFFFFFFF : 0;
    conditionalAssign((lane_r32*)&lane->x, mask, {toAssign.x});
    conditionalAssign((lane_r32*)&lane->y, mask, {toAssign.y});
    conditionalAssign((lane_r32*)&lane->z, mask, {toAssign.z});
}

flocal inline lane_r32 load_copy(r32 a)
{
    return {a};
}

flocal inline u32 horizontalAdd(lane_u32 toAdd)
{
    return toAdd.v;
}

flocal inline
lane_r32 lane_min(lane_r32 a, lane_r32 b)
{
    return {(a.v < b.v) ? a.v : b.v};
}

flocal inline lane_r32 lane_max(lane_r32 a, lane_r32 b)
{
    return {(a.v > b.v) ? a.v : b.v};
}

flocal inline b32 maskZeroed (lane_u32 mask)
{
    return mask.v == 0;
}



#define RAY_WIDE_H
#endif
