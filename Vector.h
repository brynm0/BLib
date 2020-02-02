#if !defined(VECTOR_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#include "blib_utils.h"
//#include "MathUtils.h"

struct uiv2
{
    union
    {
        struct
        {
            u32 x;
            u32 y;
        };
        struct
        {
            u32 r;
            u32 g;
        };
        struct
        {
            u32 u;
            u32 v;
        };
        struct
        {
            u32 arr[2];
        };
    };
     
    inline uiv2 operator+=(const u32& b)
    {
        *this = {this->x + b, this->y + b};
        return *this;
    }
    inline uiv2 operator+=(const uiv2& b)
    {
        *this = {this->x + b.x, this->y + b.y};
        return *this;
    }
};

flocal uiv2 uint_vec(u32 a, u32 b)
{
    return {a,b};
}

struct v2
{
    
    union
    {
        struct
        {
            r32 x;
            r32 y;
        };
        struct
        {
            r32 r;
            r32 g;
        };
        struct
        {
            r32 u;
            r32 v;
        };
        struct
        {
            r32 arr[2];
        };
    };
    inline v2 operator+=(const r32& b)
    {
        *this = {this->x + b, this->y + b};
        return *this;
    }
    inline v2 operator+=(const v2& b)
    {
        *this = {this->x + b.x, this->y + b.y};
        return *this;
    }
};

struct v3
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
            r32 r;
            r32 g;
            r32 b;
        };
        struct
        {
            r32 u;
            r32 v;
            r32 w;
        };
        struct
        {
            r32 arr[4];
        };
    };
    inline v3 operator*=(const r32& b)
    {
        *this = {this->x * b, this->y * b, this->z * b};
        return *this;
    }
    inline v3 operator/=(const r32& b)
    {
        *this = {this->x / b, this->y / b, this->z / b};
        return *this;
    }
    inline v3 operator+=(const r32& b)
    {
        *this = {this->x + b, this->y + b, this->z + b};
        return *this;
    }
    inline v3 operator-=(const r32& b)
    {
        *this = {this->x - b, this->y - b, this->z - b};
        return *this;
    }
    
    inline v3 operator*=(const v3& b)
    {
        *this = {this->x * b.x, this->y * b.y, this->z * b.z};
        return *this;
    }
    inline v3 operator/=(const v3& b)
    {
        *this = {this->x / b.x, this->y / b.y, this->z / b.z};
        return *this;
    }
    inline v3 operator+=(const v3& b)
    {
        *this = {this->x + b.x, this->y + b.y, this->z + b.z};
        return *this;
    }
    inline v3 operator-=(const v3& b)
    {
        *this = {this->x - b.x, this->y - b.y, this->z - b.z};
        return *this;
    }
};


struct v4
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
            r32 r;
            r32 g;
            r32 b;
            r32 a;
        };
    };
};

inline b32
operator==(const v4& a, const v4& b)
{
    return a.x == b.x &&
        a.y == b.y &&
        a.z == b.z &&
        a.w == b.w;
}

inline v3 cross(const v3& x, const v3& y)
{
    v3 result = {x.y * y.z - y.y * x.z,
                 x.z * y.x - y.z * x.x,
                 x.x * y.y - y.x * x.y};
    return result;
}

inline v2 operator+(const v2& a, const v2& b)
{
    return {a.x + b.x, a.y + b.y};
}

inline v3 operator+(const v3& a, const v3& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline v3 operator+(const v3& a, const r32& b)
{
    return {a.x + b, a.y + b, a.z + b};
}

inline v4 operator+(const v4& a, const v4& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

inline v2 operator-(const v2& a, const v2& b)
{
    return {a.x - b.x, a.y - b.y};
}

inline v3 operator-(const v3& a, const v3& b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline v3 operator-(const r32 a, const v3& b)
{
    return {a - b.x, a - b.y, a - b.z};
}
#if 0 
inline v4 operator-(const r32 a, const v4& b)
{
    return {a - b.x, a - b.y, a - b.z, a - b.w};
}
#endif
inline v3 operator-(const v3& a, const r32 b)
{
    return {a.x - b, a.y - b, a.z - b};
}

inline v4 operator-(const v4& a, const v4& b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

inline v2
operator*(const v2& a, const v2& b)
{
    return {a.x * b.x, a.y * b.y};
}

inline v3 operator*(const v3& a, const v3& b)
{
    return {a.x * b.x, a.y * b.y, a.z * b.z};
}

inline v4
operator*(const v4& a, const v4& b)
{
    return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

inline v2
operator*(const v2& a, const r32& b)
{
    return {a.x * b, a.y * b};
}

inline v3
operator*(const v3& a, const r32& b)
{
    return {a.x * b, a.y * b, a.z * b};
}

inline v4
operator*(const v4& a, const r32& b)
{
    return {a.x * b, a.y * b, a.z * b, a.w * b};
}

inline v2
operator/(const v2& a, const r32& b)
{
    return {a.x / b, a.y / b};
}

inline v3
operator/(const v3& a, const r32& b)
{
    return {a.x / b, a.y / b, a.z / b};
}

inline v4
operator/(const v4& a, const r32& b)
{
    return {a.x / b, a.y / b, a.z / b, a.w / b};
}

inline v2 operator*(const r32& a, const v2& b)
{
    return b * a;
}

inline v3 operator*(const r32& a, const v3& b)
{
    return b * a;
}

inline v4 operator*(const r32& a, const v4& b)
{
    return b * a;
}

inline v2 operator-(const v2& a)
{
    return {-a.x, -a.y};
}

inline v3 operator-(const v3& a)
{
    return {-a.x, -a.y, -a.z};
}

inline v4 operator-(const v4& a)
{
    return {-a.x, -a.y, -a.z, -a.w};
}

inline b32
operator==(const v3& a, const v3& b)
{
    return a.x == b.x &&
        a.y == b.y &&
        a.z == b.z;
}

inline b32
operator!=(const v3& a, const v3& b)
{
    return !(a == b);
}

inline b32
operator==(const v2& a, const v2& b)
{
    return a.x == b.x &&
        a.y == b.y;
}

inline b32
operator!=(const v2& a, const v2& b)
{
    return !(a == b);
}

inline v3 xyz(const v4& a)
{
    return {a.x, a.y, a.z};
}

inline v2 xy(const v3& a)
{
    return {a.x, a.y};
}

inline v2 xy(const v4& a)
{
    return {a.x, a.y};
}

inline v2 v(r32 a, r32 b)
{
    return {a,b};
}

inline v3 v(const v3& a)
{
    return {a.x, a.y, a.z};
}

inline v3 v(r32 a, r32 b, r32 c)
{
    return {a,b,c};
}

inline v3 v(r32 a)
{
    return {a,a,a};
}

inline v4 v(r32 a, r32 b, r32 c, r32 d)
{
    return {a,b,c,d};
}

inline v4 v(const v3& a, r32 w)
{
    return {a.x, a.y, a.z, w};
}

inline v4 v(const v2& a, r32 w, r32 u)
{
    return {a.x, a.y, w, u};
}

inline v3 v(const v2& a, r32 w)
{
    return {a.x, a.y, w};
}

flocal inline v3 xyy(const v2& a)
{
    return {a.x, a.y, a.y};
}

flocal inline v3 yxy(const v2& a)
{
    return {a.y, a.x, a.y};
}

flocal inline v3 yyx(const v2& a)
{
    return {a.y, a.y, a.x};
}

flocal inline b32 eps_equals(const v3& a, const v3& b, r32 eps)
{
    if (a.x < (b.x + eps) && a.x > (b.x - eps) &&
        a.y < (b.y + eps) && a.y > (b.y - eps) &&
        a.z < (b.z + eps) && a.z > (b.z - eps))
    {
        return true;
    }
    return false;
    
}

inline v3 normalize(const v3& a);
inline v2 normalize(const v2& a);
inline r32 dot(const v3& a, const v3& b);
inline r32 dot(const v2& a, const v2& b);

inline size_t v2hash(v2 v);

inline size_t v3hash(v3 v);

inline size_t v4hash(v4 v);

    
#define VECTOR_H
#endif
