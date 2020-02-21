#if !defined(MATERIAL_INFO_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */

#define MAX_BINDINGS 16
#pragma pack(push,1)

struct material_info
{
    char vert_shader_path[256];
    char frag_shader_path[256];
    shader_binding_info bindings[MAX_BINDINGS];
    u32 num_bindings;
    vertex_binding_info vertex_bindings[MAX_BINDINGS];
    u32 num_vertex_bindings;
    u32 vert_shader_path_length;
    u32 frag_shader_path_length;
};

#pragma pack(pop)

#define MATERIAL_INFO_H
#endif
