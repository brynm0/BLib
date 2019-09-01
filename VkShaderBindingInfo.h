/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#ifndef VK_SHADER_BINDING_INFO_H
#define VK_SHADER_BINDING_INFO_H

#pragma pack(push,1)
#include "CommonDefines.h"
struct ShaderBindingInfo
{
    VkDescriptorType type;
    VkShaderStageFlagBits stageFlags;
    b32 isPushConstant;
    //if push constant, ignore binding
    uint32_t binding;
};

#define MAX_BINDINGS 8
struct MaterialInfo
{
    char vertShaderPath[256];
    char fragShaderPath[256];
    ShaderBindingInfo bindings[MAX_BINDINGS];
    u32 numBindings;
    u32 vertShaderPathLength;
    u32 fragShaderPathLength;
};

#pragma pack(pop)

#endif //VK_SHADER_BINDING_INFO_H
