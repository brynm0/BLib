#if !defined(VECTORMATH_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#include <stdio.h>
#include <math.h>
#include "Vector.h"
#include "MathUtils.h"
flocal v2 get_perp_vec_lh(v2 v)
{
    return {-v.y, v.x};
}

flocal inline v3
evaluate_line_parameter(const v3& start, const v3& end, const r32& t)
{
    ASSERT(t >= 0 && t <= 1, "Parameter must be in the range (0,1)");
    return t * (end - start) + start;
}

flocal inline r32
sqLen(v3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

flocal inline r32
sqLen(v2 vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

flocal inline r32
cross(const v2& a, const v2& b)
{
    return a.x * b.y - a.y * b.x;
}

//NOTE projects A onto B
flocal inline v2 project(v2 a, v2 b)
{
    r32 d = dot(a,b);
    r32 sq_mag = sqLen(b);
    return (d / sq_mag) * b;
}

#if 1
flocal v3 setMag (v3 toSet, const r32& target)
{
    r32 len = sqrtf(sqLen(toSet));
    r32 ratio = target / len;
    return toSet * ratio;
}
#endif

flocal void limit (v3* toLimit, const r32& limiter)
{
    r32 toLimitLenSq = sqLen(*toLimit);
    if (toLimitLenSq > limiter * limiter)
    {
        *toLimit *= (limiter) / sqrtf(toLimitLenSq);
    }
}

flocal inline r32
sqDist(const v3& a, const v3& b)
{
    return sqLen(a - b);
}

flocal inline r32
sqDist(const v2& a, const v2& b)
{
    return sqLen(a - b);
}

flocal inline
r32 distance (const v3& a, const v3& b)
{
    return sqrt(sqDist(a,b));
}


flocal inline v2 clamp(v2 a, v2 low, v2 high)
{
    return {clamp_r32(a.x, low.x, high.x),
            clamp_r32(a.y, low.y, high.y)};
}

flocal inline v3 clamp(v3 a, v3 low, v3 high)
{
    return {clamp_r32(a.x, low.x, high.x),
            clamp_r32(a.y, low.y, high.y),
            clamp_r32(a.z, low.z, high.z)};
}

flocal inline v2
cross(r32 s, const v2& a)
{
    return v(-s * a.y, s * a.x);
}

flocal inline v2
cross(const v2& a, r32 s)
{
    return v(s * a.y, -s * a.x);
}

//NOTE t is parameter along the ray direction
//TODO test this
b32 ray_line_seg_x(v2 ro,
                   v2 rd,
                   v2 a,
                   v2 b, r32* t, v2* intersection_pt)
{
    ASSERT(sqLen(rd) == 1.0f, "Ray dir must be normalised before passing to ray_line_seg_x")
    v2 v_a = ro - a;
    v2 v_b = b - a;
    v2 v_c = v(-rd.y, rd.x);


    r32 d_prod = dot(v_b, v_c);
    if (fast_fabs(d_prod) < 0.000001f)
    {
        ASSIGN_PTR(t, R32_MAX); //if (t) { *t = R32_MAX; }
        ASSIGN_PTR(intersection_pt, MAX_V2); //if (intersection_pt) { *intersection_pt = MAX_V2; }
        return false;
    }
    r32 t_a = cross(v_b, v_a) / d_prod;
    r32 t_b = dot(v_a, v_c) / d_prod;
    
    if (t_a >= 0.0 && (t_b >= 0.0 && t_b <= 1.0))
    {
        ASSIGN_PTR(t, t_a); //if (t) { *t = t_a; }
        ASSIGN_PTR(intersection_pt, ro + rd * t_a); //if (intersection_pt) { *intersection_pt = ro + rd * t; }
        return true;
    }
    
    ASSIGN_PTR(t, R32_MAX); //if (t) { *t = R32_MAX; }
    ASSIGN_PTR(intersection_pt, MAX_V2); //if (intersection_pt) { *intersection_pt = MAX_V2; } 
    return false;
    
}

b32 ray_closed_polyline_x(v2 ro,
                          v2 rd,
                          u32 num_pts,
                          v2* pts,
                          r32* t,
                          v2* intersection_pt,
                          u32* provoking_idx)
{
    //NOTE we don't support multiple intersections, this only returns the first intersection it finds
    LOOP(i,num_pts)
    {
        if (i == num_pts - 1)
        {
            if (ray_line_seg_x(ro, rd, pts[i], pts[0], t, intersection_pt))
            {
                ASSIGN_PTR(provoking_idx, i);
                return true;
            }
        }
        else
        {
            if(ray_line_seg_x(ro, rd, pts[i], pts[i+1], t, intersection_pt))
            {
                ASSIGN_PTR(provoking_idx, i);
                return true;
            }
        }
    }
    return false;
}

b32 ray_triangle_x(v3 ro, 
                  v3 rd, 
                  v3 a, v3 b, v3 c,
                  v3* intersection)
{
    const r32 EPSILON = 0.0000001f;
    v3 edge1 = b - a;
    v3 edge2 = c - a;
    v3 h = cross(rd, edge2); //rd.crossProduct(edge2);
    r32 dotted = dot(edge1, h); //edge1.dotProduct(h);
    if (dotted > -EPSILON && dotted < EPSILON)
    {
        return false;    // This ray is parallel to this triangle.
    }
    r32 f = 1.0/dotted;
    v3 s = ro - a;
    r32 u = f * dot(s,h); //s.dotProduct(h);
    if (u < 0.0 || u > 1.0)
    {
        return false;
    }
    v3 q = cross(s, edge1); //s.crossProduct(edge1);
    r32 v = f * dot(rd, q); //rd.dotProduct(q);
    if (v < 0.0 || u + v > 1.0)
    {
        return false;
    }
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * dot(edge2, q); //edge2.dotProduct(q);
    if (t > EPSILON) // ray intersection
    {
        *intersection = ro + rd * t;
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
    {
        return false;
    }
}

flocal inline v3
intColorToFloat(u32 color)
{
    v3 out = {};
    u8* current = (u8*)(&color);
    out.b = (r32)(*current++) / 255.0f;
    out.g = (r32)(*current++) / 255.0f;
    out.r = (r32)(*current++) / 255.0f;
    return out;
}

//from http://realtimecollisiondetection.net/
flocal inline v3 barycentric_coords(v3 a, v3 b, v3 c, v3 p)
{
    v3 va = b - a;
    v3 vb = c - a;
    v3 vc = p - a;
    r32 d00 = dot(va, va);
    r32 d01 = dot(va, vb);
    r32 d11 = dot(vb, vb);
    r32 d20 = dot(vc, va);
    r32 d21 = dot(vc, vb);
    r32 denom = d00 * d11 - d01 * d01;
    v3 ret = {};
    ret.v = (d11 * d20 - d01 * d21) / denom;
    ret.w = (d00 * d21 - d01 * d20) / denom;
    ret.u = 1.0f - ret.v - ret.w;
    return ret;
}

flocal v2 line_intersection(v2 start1, v2 end1, v2 start2, v2 end2, r32* param)
{
    const r32 eps = 0.00001f;
      r32 ax = end1.arr[0] - start1.arr[0];
    r32 ay = end1.arr[1] - start1.arr[1];

    r32 bx = start2.arr[0] - end2.arr[0];
    r32 by = start2.arr[1] - end2.arr[1];
    
    r32 dx = start2.arr[0] - start1.arr[0];
    r32 dy = start2.arr[1] - start1.arr[1];
    
    r32 det = ax * by - ay * bx;

    if (fabs(det) < eps)
    {
        return MAX_VEC2;
    }
    r32 r = (dx * by - dy * bx) / det;
    r32 s = (ax * dy - ay * dx) / det;
    
    if ( !(r < 0 || r > 1|| s < 0 || s > 1) )
    {
        if (param)
        {
            *param = r;
        }
        return start1 + ((end1 - start1)*r);
    }
    else
    {
        return MAX_VEC2;
    }
}

flocal inline v3 lineCP(v3 a, v3 b, v3 query)
{
    v3 aToB = b - a;
    v3 aToQ = query - a;
    r32 aToB_len = sqLen(aToB);
    r32 t = dot(aToQ, aToB) / aToB_len;
    if (t > 1.0f) {t = 1;}
    else if (t < 0.0f) {t = 0;}
    return a + (aToB * t);
}

flocal inline v2 lineCP(v2 a, v2 b, v2 query)
{
    v2 aToB = b - a;
    v2 aToQ = query - a;
    r32 aToB_len = sqLen(aToB);
    r32 t = dot(aToQ, aToB) / aToB_len;
    if (t > 1.0f) {t = 1;}
    else if (t < 0.0f) {t = 0;}
    return a + (aToB * t);
}

flocal inline b32 point_is_on_line(v2 a, v2 b, v2 query)
{
    v2 aToB = b - a;
    v2 aToQ = query - a;
    r32 aToB_len = sqLen(aToB);
    r32 t = dot(aToQ, aToB) / aToB_len;
    if (t > 1.0f || t < 0.0f)
    {
        return false;
    }
    r32 distance = sqDist(lineCP(a,b,query),query);
    if (distance < 0.001f)
    {
        return true;
    }
    return false;
}

flocal inline v3 barycentric_coords(v2 a, v2 b, v2 c, v2 query)
{
    v3 lambda = {};
    r32 den = 1.0f / ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
	lambda.x = ((b.y - c.y) * (query.x - c.x) + (c.x - b.x) * (query.y - c.y)) * den;
	lambda.y = ((c.y - a.y) * (query.x - c.x) + (a.x - c.x) * (query.y - c.y)) * den;
	lambda.z = 1 - lambda.x - lambda.y;
	return lambda;
}


flocal inline v2 quad_line_intersection(v2 line_a, v2 line_b, v2 top_left, v2 bottom_right)
{

    v2 intersection_result = MAX_VEC2;
    r32 record_distance = R32_MAX;
    
    v2 corner_min = v(math_min(top_left.x, bottom_right.x),
                   math_min(top_left.y, bottom_right.y));
    v2 corner_max = v(math_max(top_left.x, bottom_right.x),
                   math_max(top_left.y, bottom_right.y));

    v2 intersection = MAX_VEC2;    
    intersection = line_intersection(line_a,
                                    line_b,
                                    corner_min,
                                    v(corner_min.x, corner_max.y),
                                    nullptr);
    r32 distance = sqDist(intersection, line_a);
    
    if (intersection != MAX_VEC2 && distance < record_distance)
    {
        record_distance = distance;
        intersection_result = intersection;
    }
    
    intersection = line_intersection(line_a,
                                    line_b,
                                    v(corner_max.x, corner_min.y),
                                    corner_max,
                                    nullptr);
    distance = sqDist(intersection, line_a);
    if (intersection != MAX_VEC2 && distance < record_distance)
    {
        record_distance = distance;
        intersection_result = intersection;
    }
    
    intersection = line_intersection(line_a,
                                    line_b,
                                    v(corner_min.x, corner_max.y),
                                    corner_max,
                                    nullptr);
    distance = sqDist(intersection, line_a);
    if (intersection != MAX_VEC2 && distance < record_distance)
    {
        record_distance = distance;
        intersection_result = intersection;
    }
    
    intersection = line_intersection(line_a,
                                    line_b,
                                    corner_min,
                                    v(corner_max.x, corner_min.y),
                                    nullptr);
    
    distance = sqDist(intersection, line_a);
    if (intersection != MAX_VEC2 && distance < record_distance)
    {
        record_distance = distance;
        intersection_result = intersection;
    }
    return intersection_result;
}

#define VECTORMATH_H
#endif
