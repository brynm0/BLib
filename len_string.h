#if !defined(LEN_STRING_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

struct len_string
{
    u32 buffer_len;
    u32 string_len;
    char* str;
};

flocal inline len_string l_string(u32 buffer_len)
{
    len_string str = {};
    str.buffer_len = buffer_len;
    str.string_len = 0;
    str.str = (char*)malloc(str.buffer_len);
    return str;
}

flocal inline void reallocate_len_string(len_string* l, u32 new_size)
{
    l->str = (char*)realloc(l->str, new_size);
    l->buffer_len = new_size;
}

flocal inline void append_to_len_string(len_string* l, char* str)
{
    u32 in_str_len = strlen(str);
    if (in_str_len + l->string_len > l->buffer_len)
    {
        reallocate_len_string(l, in_str_len + l->string_len + 1);
    }
    for (int i = 0; i < in_str_len; i++)
    {
        l->str[l->string_len + i] = str[i];
    }
    l->string_len += in_str_len;
    l->str[l->string_len] = 0;
}

flocal inline void sub_str_to_null_terminated(char* s, u32 length, char** out)
{
    
    for (int i = 0; i < length+1; i++)
    {
        if (i == length)
        {
            (*out)[i] = '\0';
        }
        else
        {
            (*out)[i] = s[i];
        }               
    }
    
}

#define LEN_STRING_H
#endif
