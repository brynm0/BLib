#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H
#include <stdint.h>
#include <float.h>
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define i16 int16_t
#define i32 int32_t

#define i64 int64_t
#define b32 uint32_t
#define u64 uint64_t
#define r32 float
#define r64 double
#define NUM_WORKER_THREADS (1)
#define DEFAULT_ENTITIES 256
#define RENDER_FRACTION 1
#define MAX_NAME_LEN 256
#define BG_COLOR 0xe0b4b4
#define BG_COLOR_LIGHTER 0xddc7c7
#define B32_TRUE 1;
#define B32_FALSE 0;
#define flocal static
#define global_variable static
#define persist static
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX
#define R32_MAX FLT_MAX
#define NULL_TERMINATOR '\0'
#define NUM_BEZIER_VERTS 3

#define ASCII_START 32
#define ASCII_END 127
#define TEXT_SIZE_MIN 0.04f
#define STATIC_UI_TEXT_SIZE_MIN (32.0f / 1080.0f) * 2.0f//32 pixels @ 1080p https://youtu.be/fVFgSkZtCio
#define TRANSIENT_UI_TEXT_SIZE_MIN (46.0f / 1080.0f) * 2.0f//46 pixels @ 1080p https://youtu.be/fVFgSkZtCio

#define MAX_UBOS (500000)
#define VBO_ELEMENTS (1000000)

#define PI(number) ((number) * 3.14159265359f)
#define SQ(number) ((number) * (number))
#define CUBE(number) ((number) * (number) * (number))
#define MAX_VEC (v(R32_MAX, R32_MAX, R32_MAX))

#define SCL 5
#define MAX_VEC2 (v(R32_MAX, R32_MAX))
#define MAX_V2 MAX_VEC2
#define RADIANS(DEGREES) (DEGREES * (PI(1) / 180.0f))
#define DEGREES(RADIANS) (RADIANS * (180.0f / PI(1)))

#define KILOBYTES(number) ((number) * 1024)
#define MEGABYTES(number) ((KILOBYTES(number) * 1024))
#define GIGABYTES(number) ((MEGABYTES(number) * 1024))

#define ACCESS_PTR(ptr, idx, type) (&(((type *)ptr)[idx]))
#define ACCESS_VAL(ptr, idx, type) (((type*)(ptr))[idx])
#define ASSIGN_PTR(ptr, val) if ((ptr)) { *ptr = (val); }

//Only works for constant arrays, not pointers
#define arrayCount(array) (sizeof(array) / sizeof(array[0]))
#if DEBUG==1
#define ASSERT(expr, text) \
    if (!(expr))           \
    {                                                            \
        fprintf(stderr, "%s %s %d\n", text, __FILE__, __LINE__); \
        *(int*)0 = 0;                                            \
    }
#else
#define ASSERT(expr, text) expr
#endif

#define LOOP(induction, end) for(u32 induction = 0; induction < end; induction++) 
#define POOL(induction, initial) for(u32 induction = initial; induction >= 0; induction--)


#if 0 
void* safe_realloc(void* src, size_t size, size_t original)
{

    void* tmp = realloc((u8*)src, size);
    if (tmp)
    {
        return tmp;
    }
    else
    {
        ASSERT(1==0, "Realloc failed: ");
        return nullptr;
    }
}

#define realloc safe_realloc
#endif

b32 streq(char* a, char* b, u32 b_len)
{
    LOOP(i, b_len)
    {
        if (a[i] != b[i])
        {
            return false;
        }   
    }
    return true;
}


#endif // !COMMON_DEFINES_H
