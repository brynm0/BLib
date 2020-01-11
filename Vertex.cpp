#include "Vertex.h"

flocal VkVertexInputBindingDescription getBindingDescription()
{
	VkVertexInputBindingDescription bindingDescription = {};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return bindingDescription;
}

flocal std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(u32 numAttributes)
{
	std::vector<VkVertexInputAttributeDescription> out = {};
	out.resize(numAttributes);

	out[0].binding = 0;
	out[0].location = 0;
	out[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	out[0].offset = offsetof(Vertex, pos);

	out[1].binding = 0;
	out[1].location = 1;
	out[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	out[1].offset = offsetof(Vertex, color);

	out[2].binding = 0;
	out[2].location = 2;
	out[2].format = VK_FORMAT_R32G32B32_SFLOAT;
	out[2].offset = offsetof(Vertex, normal);

	out[3].binding = 0;
	out[3].location = 3;
	out[3].format = VK_FORMAT_R32G32_SFLOAT;
	out[3].offset = offsetof(Vertex, texCoord);
    
#if 0
	out[4].binding = 0;
	out[4].location = 4;
	out[4].format = VK_FORMAT_R32_SFLOAT;
	out[4].offset = offsetof(Vertex, weight);
#endif
    
	return out; 
}
