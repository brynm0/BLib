#if !defined(GEO_H)
#include <vector>
#include "flat_hash_map.hpp"
#include <map>
#include "Vertex.h"
#include "CommonDefines.h"
#include "w:\AgentBasedFramework\Code\QuadTree.h"
#include "w:\AgentBasedFramework\Code\OctTree.h"

enum MeshType
{
    MESH_TYPE_TRIANGLES,
    MESH_TYPE_QUADS,
    MESH_TYPE_NGONS,
    MESH_TYPE_COUNT
};

struct EntityMesh
{
    MeshType type;
    
    u32 indexCount;
    u32* vIndices;
    u32* tIndices;
    u32* nIndices;
    
    u32 vertexCount;
    v3* positions;

    u32 paramCount;
    v2* parameters;

    u32 colorCount;
    v3* colors;

    u32 normalCount;
    v3* normals;

    Vertex* vertices;
    
    QuadTree* paramTree;
    OctTree* vertexTree;
    
};

struct Mesh
{
    MeshType type;
	std::vector<v3> pos;
    std::vector<v3> colors;
	std::vector<v2> coords;
	std::vector<v3> normals;
	std::vector<u32> vIndices;
	std::vector<u32> tIndices;
	std::vector<u32> nIndices;
};

struct Edge
{
    Vertex a;
    Vertex b;
    bool operator==(const Edge& other) const
    {
        return a == other.a && b == other.b;
    }
};

namespace std
{
	template<> struct hash<Edge>
	{
		size_t operator()(Edge const& v) const
		{
            return ((hash<Vertex>()(v.a) ^
                     (hash<Vertex>()(v.b))));
                     
		}
	};
}

inline bool operator < (const Edge& a, const Edge& b)
{
    if (a.a < b.a)
    {
        return true;
    }
    if (a.a == b.a && a.b < b.b)
    {
        return true;
    }
    return false;
}

struct Curve
{
	Mesh lineMesh;
    //TODO(Bryn):
    //Some object space spatial partitioning for edges should be easy
    //Done with a preprocessor
    ska::flat_hash_map<Edge, u32> edgeMap;
};

#define GEO_H
#endif
