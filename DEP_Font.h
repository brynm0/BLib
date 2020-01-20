#if !defined(FONT_H)

/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#include "flat_hash_map.hpp"
#include "CommonDefines.h"
#define MAX_CHARS_IN_FONT 256
struct Kerning
{
    u32 idFirst;
    u32 idSecond;
    i32 amount;
};

struct Character
{
    u32 id;
    u32 x;
    u32 y;
    u32 width;
    u32 height;
    u32 xOffset;
    u32 yOffset;
    u32 xAdvance;
    u32 page;
    u32 channel;
    char letter;
    Kerning* kerning_arr; //[MAX_CHARS_IN_FONT];
};

struct Page
{
    u32 id;
    char path[64];
};

struct Font
{
    u32 size;
    b32 bold;
    b32 italic;
    char charset;
    b32 unicode;
    u32 stretchHeight;
    b32 smooth;
    u32 ssLevel;
    u32 padding[4];
    u32 spacing[2];
    u32 lineHeight;
    u32 base;
    u32 scaleW;
    u32 scaleH;
    b32 packed;
    Page page;
    
    Character* character_arr; //[MAX_CHARS_IN_FONT];
};

struct FontInfo
{
    u32 characterCount;
    ska::flat_hash_map<char, u32> charVertexMap;
};

struct TypeFace
{
    Font font;
    FontInfo info;
};

#define FONT_H
#endif
