#if !defined(MATRIX_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#include "CommonDefines.h"
#include "Vector.h"
#include <math.h>
#include <stdio.h>
struct m4
{
    union
    {
        struct
        {
            r32 xx;
            r32 xy;
            r32 xz;
            r32 xw;

            r32 yx;
            r32 yy;
            r32 yz;
            r32 yw;

            r32 zx;
            r32 zy;
            r32 zz;
            r32 zw;

            r32 wx;
            r32 wy;
            r32 wz;
            r32 ww;

        };
        /*
        struct
        {
            v4 x;
            v4 y;
            v4 z;
            v4 w;
        };
        */
        struct
        {
            //TODO overload [] operator for matrices to return a vector
            r32 arr[4][4];
        };
        struct
        {
            r32 arr_1d[16];
        };
    };
};

struct m3
{
    union
    {
        struct
        {
            r32 xx;
            r32 xy;
            r32 xz;
         
            r32 yx;
            r32 yy;
            r32 yz;
         
            r32 zx;
            r32 zy;
            r32 zz;

        };
        
        struct
        {
            //TODO overload [] operator for matrices to return a vector
            r32 arr[3][3];
        };
    };
};

flocal inline m3 m4tom3(const m4& a)
{
    m3 ret = {};
    ret.xx = a.xx;
    ret.xy = a.xy;
    ret.xz = a.xz;
    ret.yx = a.yx;
    ret.yy = a.yy;
    ret.yz = a.yz;
    ret.zx = a.zx;
    ret.zy = a.zy;
    ret.zz = a.zz;
    return ret;
}

flocal inline v3 operator*(const m3& m, const v3& b)
{
    return v(m.arr[0][0] * b.x + m.arr[1][0] * b.y + m.arr[2][0] * b.z,
             m.arr[0][1] * b.x + m.arr[1][1] * b.y + m.arr[2][1] * b.z,
             m.arr[0][2] * b.x + m.arr[1][2] * b.y + m.arr[2][2] * b.z);
}

flocal inline v4 operator*(const m4& m, const v4& b)
{
    return v(m.arr[0][0] * b.x + m.arr[1][0] * b.y + m.arr[2][0] * b.z + m.arr[3][0] * b.w,
             m.arr[0][1] * b.x + m.arr[1][1] * b.y + m.arr[2][1] * b.z + m.arr[3][1] * b.w,
             m.arr[0][2] * b.x + m.arr[1][2] * b.y + m.arr[2][2] * b.z + m.arr[3][2] * b.w,
             m.arr[0][3] * b.x + m.arr[1][3] * b.y + m.arr[2][3] * b.z + m.arr[3][3] * b.w);
}

flocal inline m4 operator*(const m4& a, const m4& b)
{
    m4 out;


    /*
      x.x x.y x.z x.w  xx yx zx wx
      y.x y.y y.z y.w  xy yy zy wy 
      z.x z.y z.z z.w  xz yz zz wz
      w.x w.y w.z w.w  xw yw zw ww
     */
# if 1
    out.xx = a.xx * b.xx + a.yx * b.xy + a.zx * b.xz + a.wx * b.xw;
    out.yx = a.xx * b.yx + a.yx * b.yy + a.zx * b.yz + a.wx * b.yw;
    out.zx = a.xx * b.zx + a.yx * b.zy + a.zx * b.zz + a.wx * b.zw;
    out.wx = a.xx * b.wx + a.yx * b.wy + a.zx * b.wz + a.wx * b.ww;
    
    out.xy = a.xy * b.xx + a.yy * b.xy + a.zy * b.xz + a.wy * b.xw;
    out.yy = a.xy * b.yx + a.yy * b.yy + a.zy * b.yz + a.wy * b.yw;
    out.zy = a.xy * b.zx + a.yy * b.zy + a.zy * b.zz + a.wy * b.zw;
    out.wy = a.xy * b.wx + a.yy * b.wy + a.zy * b.wz + a.wy * b.ww;
    
    out.xz = a.xz * b.xx + a.yz * b.xy + a.zz * b.xz + a.wz * b.xw;
    out.yz = a.xz * b.yx + a.yz * b.yy + a.zz * b.yz + a.wz * b.yw;
    out.zz = a.xz * b.zx + a.yz * b.zy + a.zz * b.zz + a.wz * b.zw;
    out.wz = a.xz * b.wx + a.yz * b.wy + a.zz * b.wz + a.wz * b.ww;
        
    out.xw = a.xw * b.xx + a.yw * b.xy + a.zw * b.xz + a.ww * b.xw;
    out.yw = a.xw * b.yx + a.yw * b.yy + a.zw * b.yz + a.ww * b.yw;
    out.zw = a.xw * b.zx + a.yw * b.zy + a.zw * b.zz + a.ww * b.zw;
    out.ww = a.xw * b.wx + a.yw * b.wy + a.zw * b.wz + a.ww * b.ww;
# else
    float sum = 0.f;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                sum += a.arr[i][k] * b.arr[k][j];
            }
            out.arr[i][j] = sum;
            sum = 0.0f;
        }
        
    }
#endif
    return out;
}

flocal inline m4 matrix(r32 val)
{
    m4 result;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            result.arr[i][j] = val;
        }
    }
    return result;
}

flocal inline m4 matrix()
{
    m4 result = matrix(0.0f);
    result.xx = 1.0f;
    result.yy = 1.0f;
    result.zz = 1.0f;
    result.ww = 1.0f;
    return result;
}

flocal inline m4
ortho(r32 left, r32 right, r32 bottom, r32 top, r32 z_near, r32 z_far)
{
    m4 result = matrix();
    result.arr[0][0] = 2.0f / (right - left);
    result.arr[1][1] = 2.0f / (top - bottom);
    result.arr[2][2] = - (1.0f) / (z_far - z_near);
    result.arr[3][0] = - (right + left) / (right - left);
    result.arr[3][1] = - (top + bottom) / (top - bottom);
    result.arr[3][2] = - (z_near) / (z_far - z_near);
    return result;
}

flocal inline m4 perspective(r32 fovy, r32 aspect, r32 zNear, r32 zFar)
{

    //r32 const tanHalfFovY = tanf(fovy / 2.0f);
    r32 ys = 1.0f / tanf(fovy / 2.0f);
    r32 xs = ys / aspect;
    r32 nmf = zNear - zFar;
    m4 result = matrix(0);
    result.arr[0][0] = xs; //1.0f / (aspect * tanHalfFovY);
    result.arr[1][1] = ys; //1.0f / (tanHalfFovY);
    result.arr[2][2] = ((zFar + zNear)) / nmf; //(//zFar / (zNear - zFar); 
    result.arr[2][3] = -1.0f; //1.0f / (aspect * tanHalfFovY);
    result.arr[3][2] = (2 * zFar * zNear) / nmf; //-(zFar * zNear) / (zFar - zNear); //1.0f / (aspect * tanHalfFovY);
    return result;
}

flocal inline m4 lookAt(v3 eye, v3 target, v3 up)
{
    v3 f = normalize(target - eye);
    v3 s = normalize(cross(f,up));
    v3 u = cross(s,f);

    m4 result = matrix();
    result.arr[0][0] = s.x;
    result.arr[1][0] = s.y;
    result.arr[2][0] = s.z;
    result.arr[0][1] = u.x;
    result.arr[1][1] = u.y;
    result.arr[2][1] = u.z;
    result.arr[0][2] =-f.x;
    result.arr[1][2] =-f.y;
    result.arr[2][2] =-f.z;
    result.arr[3][0] =-dot(s, eye);
    result.arr[3][1] =-dot(u, eye);
    result.arr[3][2] = dot(f, eye);
    return result;
}

flocal inline m4 rotate(const m4& m, r32 angle, v3 v)
{
    r32 a = angle;
    r32 c = cosf(a);
    r32 s = sinf(a);

    v3 axis = normalize(v);
    v3 temp = (1.0f - c) * axis;
    m4 rotate = {};
    rotate.arr[0][0] = c + temp.x * axis.x;
    rotate.arr[0][1] = temp.x * axis.y + s * axis.z;
    rotate.arr[0][2] = temp.x * axis.z - s * axis.y;
    
    rotate.arr[1][0] = temp.y * axis.x - s * axis.z;
    rotate.arr[1][1] = c + temp.y * axis.y;
    rotate.arr[1][2] = temp.y * axis.z + s * axis.x;
    
    rotate.arr[2][0] = temp.z * axis.x + s * axis.y;
    rotate.arr[2][1] = temp.z * axis.y - s * axis.x;
    rotate.arr[2][2] = c + temp.z * axis.z;
    
    m4 result;
    //result.arr[0] = m.arr[0] * rotate.arr[0][0] + m.arr[1] * rotate.arr[0][1] + m.arr[2] * rotate.arr[0][2];
    result.arr[0][0] = m.arr[0][0] * rotate.arr[0][0] + m.arr[1][0] * rotate.arr[0][1] + m.arr[2][0] * rotate.arr[0][2];
    result.arr[0][1] = m.arr[0][1] * rotate.arr[0][0] + m.arr[1][1] * rotate.arr[0][1] + m.arr[2][1] * rotate.arr[0][2];
    result.arr[0][2] = m.arr[0][2] * rotate.arr[0][0] + m.arr[1][2] * rotate.arr[0][1] + m.arr[2][2] * rotate.arr[0][2];
    result.arr[0][3] = m.arr[0][3] * rotate.arr[0][0] + m.arr[1][3] * rotate.arr[0][1] + m.arr[2][3] * rotate.arr[0][2];


    //result.arr[1] = m.arr[0] * rotate.arr[1][0] + m.arr[1] * rotate.arr[1][1] + m.arr[2] * rotate.arr[1][2];
    result.arr[1][0] = m.arr[0][0] * rotate.arr[1][0] + m.arr[1][0] * rotate.arr[1][1] + m.arr[2][0] * rotate.arr[1][2];
    result.arr[1][1] = m.arr[0][1] * rotate.arr[1][0] + m.arr[1][1] * rotate.arr[1][1] + m.arr[2][1] * rotate.arr[1][2];
    result.arr[1][2] = m.arr[0][2] * rotate.arr[1][0] + m.arr[1][2] * rotate.arr[1][1] + m.arr[2][2] * rotate.arr[1][2];
    result.arr[1][3] = m.arr[0][3] * rotate.arr[1][0] + m.arr[1][3] * rotate.arr[1][1] + m.arr[2][3] * rotate.arr[1][2];

    
    //result.arr[2] = m.arr[0] * rotate.arr[2][0] + m.arr[1] * rotate.arr[2][1] + m.arr[2] * rotate.arr[2][2];
    result.arr[2][0] = m.arr[0][0] * rotate.arr[2][0] + m.arr[1][0] * rotate.arr[2][1] + m.arr[2][0] * rotate.arr[2][2];
    result.arr[2][1] = m.arr[0][1] * rotate.arr[2][0] + m.arr[1][1] * rotate.arr[2][1] + m.arr[2][1] * rotate.arr[2][2];
    result.arr[2][2] = m.arr[0][2] * rotate.arr[2][0] + m.arr[1][2] * rotate.arr[2][1] + m.arr[2][2] * rotate.arr[2][2];
    result.arr[2][3] = m.arr[0][3] * rotate.arr[2][0] + m.arr[1][3] * rotate.arr[2][1] + m.arr[2][3] * rotate.arr[2][2];
    
    result.arr[3][0] = m.arr[3][0];
    result.arr[3][1] = m.arr[3][1];
    result.arr[3][2] = m.arr[3][2];
    result.arr[3][3] = m.arr[3][3];
    return result;
}

flocal inline m4 rotate(r32 angle, v3 axis)
{
    return rotate(matrix(), angle, axis);
}

flocal inline m4 inverse(m4 m)
{
    double inv[16], det;
    int i;

    inv[0] = m.arr_1d[5]  * m.arr_1d[10] * m.arr_1d[15] - 
             m.arr_1d[5]  * m.arr_1d[11] * m.arr_1d[14] - 
             m.arr_1d[9]  * m.arr_1d[6]  * m.arr_1d[15] + 
             m.arr_1d[9]  * m.arr_1d[7]  * m.arr_1d[14] +
             m.arr_1d[13] * m.arr_1d[6]  * m.arr_1d[11] - 
             m.arr_1d[13] * m.arr_1d[7]  * m.arr_1d[10];

    inv[4] = -m.arr_1d[4]  * m.arr_1d[10] * m.arr_1d[15] + 
              m.arr_1d[4]  * m.arr_1d[11] * m.arr_1d[14] + 
              m.arr_1d[8]  * m.arr_1d[6]  * m.arr_1d[15] - 
              m.arr_1d[8]  * m.arr_1d[7]  * m.arr_1d[14] - 
              m.arr_1d[12] * m.arr_1d[6]  * m.arr_1d[11] + 
              m.arr_1d[12] * m.arr_1d[7]  * m.arr_1d[10];

    inv[8] = m.arr_1d[4]  * m.arr_1d[9] * m.arr_1d[15] - 
             m.arr_1d[4]  * m.arr_1d[11] * m.arr_1d[13] - 
             m.arr_1d[8]  * m.arr_1d[5] * m.arr_1d[15] + 
             m.arr_1d[8]  * m.arr_1d[7] * m.arr_1d[13] + 
             m.arr_1d[12] * m.arr_1d[5] * m.arr_1d[11] - 
             m.arr_1d[12] * m.arr_1d[7] * m.arr_1d[9];

    inv[12] = -m.arr_1d[4]  * m.arr_1d[9] * m.arr_1d[14] + 
               m.arr_1d[4]  * m.arr_1d[10] * m.arr_1d[13] +
               m.arr_1d[8]  * m.arr_1d[5] * m.arr_1d[14] - 
               m.arr_1d[8]  * m.arr_1d[6] * m.arr_1d[13] - 
               m.arr_1d[12] * m.arr_1d[5] * m.arr_1d[10] + 
               m.arr_1d[12] * m.arr_1d[6] * m.arr_1d[9];

    inv[1] = -m.arr_1d[1]  * m.arr_1d[10] * m.arr_1d[15] + 
              m.arr_1d[1]  * m.arr_1d[11] * m.arr_1d[14] + 
              m.arr_1d[9]  * m.arr_1d[2] * m.arr_1d[15] - 
              m.arr_1d[9]  * m.arr_1d[3] * m.arr_1d[14] - 
              m.arr_1d[13] * m.arr_1d[2] * m.arr_1d[11] + 
              m.arr_1d[13] * m.arr_1d[3] * m.arr_1d[10];

    inv[5] = m.arr_1d[0]  * m.arr_1d[10] * m.arr_1d[15] - 
             m.arr_1d[0]  * m.arr_1d[11] * m.arr_1d[14] - 
             m.arr_1d[8]  * m.arr_1d[2] * m.arr_1d[15] + 
             m.arr_1d[8]  * m.arr_1d[3] * m.arr_1d[14] + 
             m.arr_1d[12] * m.arr_1d[2] * m.arr_1d[11] - 
             m.arr_1d[12] * m.arr_1d[3] * m.arr_1d[10];

    inv[9] = -m.arr_1d[0]  * m.arr_1d[9] * m.arr_1d[15] + 
              m.arr_1d[0]  * m.arr_1d[11] * m.arr_1d[13] + 
              m.arr_1d[8]  * m.arr_1d[1] * m.arr_1d[15] - 
              m.arr_1d[8]  * m.arr_1d[3] * m.arr_1d[13] - 
              m.arr_1d[12] * m.arr_1d[1] * m.arr_1d[11] + 
              m.arr_1d[12] * m.arr_1d[3] * m.arr_1d[9];

    inv[13] = m.arr_1d[0]  * m.arr_1d[9] * m.arr_1d[14] - 
              m.arr_1d[0]  * m.arr_1d[10] * m.arr_1d[13] - 
              m.arr_1d[8]  * m.arr_1d[1] * m.arr_1d[14] + 
              m.arr_1d[8]  * m.arr_1d[2] * m.arr_1d[13] + 
              m.arr_1d[12] * m.arr_1d[1] * m.arr_1d[10] - 
              m.arr_1d[12] * m.arr_1d[2] * m.arr_1d[9];

    inv[2] = m.arr_1d[1]  * m.arr_1d[6] * m.arr_1d[15] - 
             m.arr_1d[1]  * m.arr_1d[7] * m.arr_1d[14] - 
             m.arr_1d[5]  * m.arr_1d[2] * m.arr_1d[15] + 
             m.arr_1d[5]  * m.arr_1d[3] * m.arr_1d[14] + 
             m.arr_1d[13] * m.arr_1d[2] * m.arr_1d[7] - 
             m.arr_1d[13] * m.arr_1d[3] * m.arr_1d[6];

    inv[6] = -m.arr_1d[0]  * m.arr_1d[6] * m.arr_1d[15] + 
              m.arr_1d[0]  * m.arr_1d[7] * m.arr_1d[14] + 
              m.arr_1d[4]  * m.arr_1d[2] * m.arr_1d[15] - 
              m.arr_1d[4]  * m.arr_1d[3] * m.arr_1d[14] - 
              m.arr_1d[12] * m.arr_1d[2] * m.arr_1d[7] + 
              m.arr_1d[12] * m.arr_1d[3] * m.arr_1d[6];

    inv[10] = m.arr_1d[0]  * m.arr_1d[5] * m.arr_1d[15] - 
              m.arr_1d[0]  * m.arr_1d[7] * m.arr_1d[13] - 
              m.arr_1d[4]  * m.arr_1d[1] * m.arr_1d[15] + 
              m.arr_1d[4]  * m.arr_1d[3] * m.arr_1d[13] + 
              m.arr_1d[12] * m.arr_1d[1] * m.arr_1d[7] - 
              m.arr_1d[12] * m.arr_1d[3] * m.arr_1d[5];

    inv[14] = -m.arr_1d[0]  * m.arr_1d[5] * m.arr_1d[14] + 
               m.arr_1d[0]  * m.arr_1d[6] * m.arr_1d[13] + 
               m.arr_1d[4]  * m.arr_1d[1] * m.arr_1d[14] - 
               m.arr_1d[4]  * m.arr_1d[2] * m.arr_1d[13] - 
               m.arr_1d[12] * m.arr_1d[1] * m.arr_1d[6] + 
               m.arr_1d[12] * m.arr_1d[2] * m.arr_1d[5];

    inv[3] = -m.arr_1d[1] * m.arr_1d[6] * m.arr_1d[11] + 
              m.arr_1d[1] * m.arr_1d[7] * m.arr_1d[10] + 
              m.arr_1d[5] * m.arr_1d[2] * m.arr_1d[11] - 
              m.arr_1d[5] * m.arr_1d[3] * m.arr_1d[10] - 
              m.arr_1d[9] * m.arr_1d[2] * m.arr_1d[7] + 
              m.arr_1d[9] * m.arr_1d[3] * m.arr_1d[6];

    inv[7] = m.arr_1d[0] * m.arr_1d[6] * m.arr_1d[11] - 
             m.arr_1d[0] * m.arr_1d[7] * m.arr_1d[10] - 
             m.arr_1d[4] * m.arr_1d[2] * m.arr_1d[11] + 
             m.arr_1d[4] * m.arr_1d[3] * m.arr_1d[10] + 
             m.arr_1d[8] * m.arr_1d[2] * m.arr_1d[7] - 
             m.arr_1d[8] * m.arr_1d[3] * m.arr_1d[6];

    inv[11] = -m.arr_1d[0] * m.arr_1d[5] * m.arr_1d[11] + 
               m.arr_1d[0] * m.arr_1d[7] * m.arr_1d[9] + 
               m.arr_1d[4] * m.arr_1d[1] * m.arr_1d[11] - 
               m.arr_1d[4] * m.arr_1d[3] * m.arr_1d[9] - 
               m.arr_1d[8] * m.arr_1d[1] * m.arr_1d[7] + 
               m.arr_1d[8] * m.arr_1d[3] * m.arr_1d[5];

    inv[15] = m.arr_1d[0] * m.arr_1d[5] * m.arr_1d[10] - 
              m.arr_1d[0] * m.arr_1d[6] * m.arr_1d[9] - 
              m.arr_1d[4] * m.arr_1d[1] * m.arr_1d[10] + 
              m.arr_1d[4] * m.arr_1d[2] * m.arr_1d[9] + 
              m.arr_1d[8] * m.arr_1d[1] * m.arr_1d[6] - 
              m.arr_1d[8] * m.arr_1d[2] * m.arr_1d[5];

    det = m.arr_1d[0] * inv[0] + m.arr_1d[1] * inv[4] + m.arr_1d[2] * inv[8] + m.arr_1d[3] * inv[12];

    ASSERT(det != 0, "You didn't pass an invertible matrix, silly!\n");

    det = 1.0 / det;
    m4 ret = {};
    for (i = 0; i < 16; i++)
    {
        ret.arr_1d[i] = inv[i] * det;
    }

    return ret;
   
}


#define MATRIX_H
#endif
