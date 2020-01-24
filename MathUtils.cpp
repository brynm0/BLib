/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#include <math.h>
#include "MathUtils.h"

flocal b32 is_inside_quad(v2 top_left, v2 bottom_right, v2 point)
{
    if (point.x > top_left.x && point.y < bottom_right.y &&
        point.x < bottom_right.x && point.y > top_left.y)
    {
        return true;
    }
    return false;
}

flocal inline r32 fast_fabs(r32 x)
{
    int casted = *(int*) &x;
    casted &= 0x7FFFFFFF;
    return *(float*)&casted;
}

flocal inline r32
map(r32 input,
    r32 fromLower,
    r32 fromHigher,
    r32 toLower,
    r32 toHigher)
{
    return toLower + ((input - fromLower)*(toHigher - toLower))/(fromHigher-fromLower);
}

#undef max
#undef min
flocal inline r32
map(r32 input, r32 from, r32 to)
{
    return map(input, 0, from, 0, to);
}

flocal inline v2 mapVec(v2 input,
                        r32 xfroml, r32 xfromh, r32 xtol, r32 xtoh,
                        r32 yfroml, r32 yfromh, r32 ytol, r32 ytoh)
{
    return {map(input.x, xfroml, xfromh, xtol, xtoh), map(input.y, yfroml, yfromh, ytol, ytoh)};
}

flocal inline r32
math_max(r32 a, r32 b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

flocal inline r32 max3(r32 a, r32 b, r32 c)
{
    return math_max(math_max(a, b), c);
}

flocal inline r32
math_min(r32 a, r32 b)
{
    if(a > b)
    {
        return b;
    }
    return a;
}

flocal inline r32
clamp_r32(r32 a, r32 low, r32 high)
{
	return math_max(low, math_min(a, high));
}

flocal inline r32
mix(r32 x, r32 y, r32 a)
{
    return  x * (1.0f - a) + y * a;
}

flocal inline r32
bilinear_mix(float c00,
             float c10,
             float c01,
             float c11,
             float tx,
             float ty)
{
    return mix(mix(c00, c10, tx), mix(c01, c11, tx), ty);
}

flocal inline r32
smooth_min(r32 a, r32 b, r32 k)
{
    r32 h = clamp_r32( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

flocal u32
xOrShift32(RandomSeries* series)
{
    // NOTE(casey): Reference XOrShift from https://en.wikipedia.org/wiki/Xorshift
    u32 x = series->state;
    
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    
    series->state = x;
    
    return x;
}

flocal r32
randomUnilateral(RandomSeries* series)
{
    r32 result = (r32)(xOrShift32(series) >> 1) / (r32)(U32_MAX >> 1);
    return result;
}

flocal r32
randomBilateral(RandomSeries* series)
{
    return 2.f * randomUnilateral(series) - 1.f;
}

flocal v3
randomUnilateralV3(RandomSeries* series)
{
    v3 res = {};
    res.x = randomUnilateral(series);
    res.y = randomUnilateral(series);
    res.z = randomUnilateral(series);
    return res;
}

flocal v2
randomUnilateralV2(RandomSeries* series)
{
    v2 res = {};
    res.x = randomUnilateral(series);
    res.y = randomUnilateral(series);
    return res;
}
flocal u32 ceiling(r32 num)
{
    int inum = int(num);
    if (num == (float)inum)
    {
        return inum;
    }
    return (u32)(inum + 1);
}
#if 1
flocal inline r32 radians(r32 degrees)
{
    return degrees * (PI(1) / 180.0f);
}

flocal inline r32 degrees(r32 radians)
{
    return radians * (180.0f / PI(1));
}
#endif

int point_in_polygon(u32 nvert, v2* poly, v2 test)
{
    r32 testx = test.x;
    r32 testy = test.y;
    int i = 0;
    int j = 0;
    int c = 0;
    for (i = 0, j = nvert-1; i < nvert; j = i++) {
        if ( ((poly[i].y>testy) != (poly[j].y>testy)) &&
             (testx < (poly[j].x-poly[i].x) * (testy-poly[i].y) / (poly[j].y-poly[i].y) + poly[i].x) )
            c = !c;
    }
    return c;
}

flocal u32 get_furthest_v_in_d(u32 num_pts, v2* pts, v2 dir)
{
    r32 record_dot = -R32_MAX;
    u32 record_pt = -1;
    LOOP(i, num_pts)
    {
        r32 new_dot = dot(dir,pts[i]);
        if (new_dot > record_dot)
        {
            record_dot = new_dot;
            record_pt = i;
        }
    }
    return record_pt;
}

flocal v2 get_furthest_v_in_d(u32 start_i, u32 end_i, v2* pts, v2 dir)
{
    r32 record_dot = -R32_MAX;
    u32 record_pt = -1;
    for (u32 i = start_i; i < end_i; i++)
    {
        r32 new_dot = dot(dir,pts[i]);
        if (new_dot > record_dot)
        {
            record_dot = new_dot;
            record_pt = i;
        }
    }
    return pts[record_pt];
}
    
flocal u32 clip_polygon(u32 clip_begin, u32 clip_end, u32 num_pts, v2* polygon, v2* intersections, b32 traverse_forwards, v2* out)
{
    
    u32 ctr = 0;
    if (traverse_forwards)
    {
        for (int i = clip_begin; i < clip_end + 2; i++)
        {
            if (i == clip_begin)
            {
                out[ctr++] = intersections[0];
            }
            else if (i == clip_end + 1)
            {
                out[ctr++] = intersections[1];   
            }
            else
            {
                out[ctr++] = polygon[i];   
            }
            
        }
    }
    else if (clip_end == clip_begin)
    {
        out[ctr++] = intersections[0];   
        out[ctr++] = intersections[1];   
    }
    else
    {
        
        for (int i = clip_end; i < num_pts; i++)
        {
            if (i == clip_end)
            {
                out[ctr++] = intersections[1];   
            }
            else
            {
                out[ctr++] = polygon[i];   
            }
            
        }
        for (int i = 0; i < clip_begin + 1; i++)
        {
            
            if (i == clip_begin)
            {
                out[ctr++] = polygon[i];   
                out[ctr++] = intersections[0];
            }
            else
            {
                out[ctr++] = polygon[i];   
            }
        }
    }
    return ctr;
}
