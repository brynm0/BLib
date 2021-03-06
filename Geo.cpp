/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Bryn Murrell $
   ======================================================================== */
#include "Geo.h"
#include "Vector.h"
#include "flat_hash_map.hpp"
#include <vector>
#include "SDF.h"
#include "VectorMath.h"
//NOTE: 
flocal Mesh
quad(r32 aspectRatio, v3 pos, v3 normal, v3 size)
{
    //TODO(bryn): This may cause problems w/math_ quads facing wrong way when normal is z
    //Too tired to think about it now
    v3 crossingVec = v(0,0,1);
    if (normal == crossingVec)
    {
        crossingVec = v(0,1,0);
    }
    v3 localX = cross(crossingVec, normal);
    v3 localY = cross(normal, localX);

    size.x /= 2.0f;
    size.y /= 2.0f;

    v4 a_pos,b_pos,c_pos,d_pos;
    v4 a_normal,b_normal,c_normal,d_normal;
    v2 a_tex_coord,b_tex_coord,c_tex_coord,d_tex_coord;
    
    size.x *= aspectRatio;
    a_pos = v(localX * -size.x + localY * size.y, 1);
    b_pos = v(localX * -size.x + localY * -size.y, 1);
    c_pos = v(localX * size.x  + localY * size.y, 1);
    d_pos = v(localX * size.x  + localY * -size.y, 1);

    a_pos += v(pos, 1);
    b_pos += v(pos, 1);
    c_pos += v(pos, 1);
    d_pos += v(pos, 1);

    a_normal = v(normal, 1);
    b_normal = v(normal, 1);
    c_normal = v(normal, 1);
    d_normal = v(normal, 1);

    a_tex_coord = v(0,0);
    b_tex_coord = v(0,1);
    c_tex_coord = v(1,0);
    d_tex_coord = v(1,1);
    
    Mesh m = {};

    m.pos.push_back(a_pos);
    m.pos.push_back(b_pos);
    m.pos.push_back(c_pos);
    m.pos.push_back(d_pos);
    
    m.colors.push_back(v(1,1,1,1));
    m.colors.push_back(v(1,1,1,1));
    m.colors.push_back(v(1,1,1,1));
    m.colors.push_back(v(1,1,1,1));
    
    m.normals.push_back(a_normal);
    m.normals.push_back(b_normal);
    m.normals.push_back(c_normal);
    m.normals.push_back(d_normal);

    m.coords.push_back(a_tex_coord);
    m.coords.push_back(b_tex_coord);
    m.coords.push_back(c_tex_coord);
    m.coords.push_back(d_tex_coord);
    
    m.vIndices.push_back(0);
    m.vIndices.push_back(2);
    m.vIndices.push_back(1);
    m.vIndices.push_back(2);
    m.vIndices.push_back(3);
    m.vIndices.push_back(1);
    
    m.tIndices.push_back(0);
    m.tIndices.push_back(2);
    m.tIndices.push_back(1);
    m.tIndices.push_back(2);
    m.tIndices.push_back(3);
    m.tIndices.push_back(1);
        
    m.nIndices.push_back(0);
    m.nIndices.push_back(2);
    m.nIndices.push_back(1);
    m.nIndices.push_back(2);
    m.nIndices.push_back(3);
    m.nIndices.push_back(1);
    
    return m;
}

flocal Mesh
loadMesh(char* path, b32 swapYZ)
{
    Mesh out = {};
    out.type = MESH_TYPE_TRIANGLES;
    FILE* f = fopen(path, "r");
    char buf[256];
    std::vector<v4> positions = {};
    std::vector<v4> normals = {};
    std::vector<v2> texCoords = {};
    std::vector<v4> colors = {};
    while (fgets(buf, 256, f))
    {
        if (buf[0] == '#' || buf[0] == 'm' || buf[0] == 'u')
        {
            continue;
        }
        else if (buf[0] == 'v' && buf[1] == 't')
        {
            strtok(buf, " ");
            r32 x = atof(strtok(NULL, " "));
            r32 y = atof(strtok(NULL, " "));
            texCoords.push_back({x,y});      
        }
        else if (buf[0] == 'v' && buf[1] == 'n')
        {
            strtok(buf, " ");
            r32 x = atof(strtok(NULL, " "));
            r32 y = atof(strtok(NULL, " "));
            r32 z = atof(strtok(NULL, " "));
            normals.push_back({x,y,z});   
        }
        else if (buf[0] == 'v')
        {
            char* ret = strtok(buf, " ");
            char* xs = strtok(NULL, " ");
            char* ys = strtok(NULL, " ");
            char* zs = strtok(NULL, " ");
            r32 x = atof(xs);
            r32 y = atof(ys);
            r32 z = atof(zs);
            if (!swapYZ)
            {
                positions.push_back({x,y,z});
            }
            else
            {
                positions.push_back({x,z,y});
            }
            colors.push_back({0.5f, 0.5f, 0.5f});
        }
        else if (buf[0] == 'f')
        {
            strtok(buf, " ");
            char* v1 = strtok(NULL, " ");
            char* v2 = strtok(NULL, " ");
            char* v3 = strtok(NULL, " ");
            char* v4 = strtok(NULL, " ");
            u32 vidx = atoi(strtok(v1, "/")) - 1;
            char* param = strtok(NULL, "/");
            u32 tidx = atoi(param) - 1;
            u32 nidx = atoi(strtok(NULL, "/")) - 1;
            out.vIndices.push_back(vidx);
            out.tIndices.push_back(tidx);
            out.nIndices.push_back(nidx);
            
            vidx = atoi(strtok(v2, "/")) - 1;
            param = strtok(NULL, "/");
            tidx = atoi(param) - 1;
            nidx = atoi(strtok(NULL, "/")) - 1;
            out.vIndices.push_back(vidx);
            out.tIndices.push_back(tidx);
            out.nIndices.push_back(nidx);
            
            vidx = atoi(strtok(v3, "/")) - 1;
            param = strtok(NULL, "/");
            tidx = atoi(param) - 1;
            nidx = atoi(strtok(NULL, "/")) - 1;
            out.vIndices.push_back(vidx);
            out.tIndices.push_back(tidx);
            out.nIndices.push_back(nidx);
            if (v4)
            {
                vidx = atoi(strtok(v4, "/")) - 1;
                param = strtok(NULL, "/");
                tidx = atoi(param) - 1;
                nidx = atoi(strtok(NULL, "/")) - 1;
                out.vIndices.push_back(vidx);
                out.tIndices.push_back(tidx);
                out.nIndices.push_back(nidx);
                out.type = MESH_TYPE_QUADS;
            }
            else
            {
                ASSERT(out.type == MESH_TYPE_TRIANGLES, "Mesh loading failed: Meshes can contain either triangles or quads, but not both");
            }
        }
        
    }
    
    out.pos     = positions;
    out.coords  = texCoords;
    out.normals = normals;
    out.colors  = colors;
    
    
    fclose(f);
	return out;
}

flocal SDF
loadSDF(char* path)
{
    SDF out = {};
    FILE* f = fopen(path, "r");
    char buf[256];
    u32 len = atoi(fgets(buf, 256, f));
    out.sideLen = (u32)std::cbrt(len);
    out.buf = (r32*)malloc(sizeof(r32) * len);
    r32* ctr = out.buf;
    while (fgets(buf, 256, f))
    {
        *ctr++ = atof(buf);
    }
    
    fclose(f);
	return out;
}
#if 0 
flocal Edge
edge(const Vertex& a, const Vertex& b)
{
    Edge out = {};
    if (b < a)
    {
        out.a = b;
        out.b = a;
    }
    else
    {
        out.a = a;
        out.b = b;
    }
    return out;
}
#endif
flocal std::vector<v2>
loadPosFile(char* path)
{
    std::vector<v2> out = {};
	FILE* file = fopen(path, "r");
#define MAX_STRING_LENGTH 256
	char strBuf[MAX_STRING_LENGTH];
	while (fgets(strBuf, MAX_STRING_LENGTH, file))
	{
        strtok(strBuf, " ");
		char xString[MAX_STRING_LENGTH];
		char yString[MAX_STRING_LENGTH];

		int strBufIndex = 0;
		int xIndex = 0;
        v2 vert = {};
		//v2 vertex = {};
		while (xIndex == 0 || xString[xIndex - 1] != NULL_TERMINATOR)
		{
			xString[xIndex++] = strBuf[strBufIndex++];
		}

		vert.x = atof(xString);
		int yIndex = 0;
		while (yIndex == 0 || yString[yIndex - 1] != NULL_TERMINATOR)
		{
			yString[yIndex++] = strBuf[strBufIndex++];
		}
		vert.y = atof(yString);
		out.push_back(vert);
	}
	fclose(file);
    return out;
}

flocal b32 writeMeshFile(const EntityMesh& m, char* path)
{
    FILE* f = fopen(path, "w");

    if (!f)
    {
        fclose(f);
        return false;
    }
    fprintf(f, "# obj file made by bryn murrell\n");

    for (u32 i = 0; i < m.vertexCount; i++)
    {
        const v4* current = &m.positions[i];
        fprintf(f, "v %.10f %.10f %.10f\n", current->x, current->y, current->z);
    }
    for (u32 i = 0; i < m.paramCount; i++)
    {
        const v2* current = &m.parameters[i];
        fprintf(f, "vt %.10f %.10f\n", current->x, current->y);
    }

    for (u32 i = 0; i < m.normalCount; i++)
    {
        const v4* current = &m.normals[i];
        fprintf(f, "vn %.10f %.10f %.10f\n", current->x, current->y, current->z);
        
    }
    if (m.type == MESH_TYPE_TRIANGLES)
    {
        for(u32 i = 0; i < m.indexCount; i+=3)
        {
            fprintf(f, "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
                    1 + m.vIndices[i    ], 1 + m.tIndices[i    ], 1 + m.nIndices[i    ],
                    1 + m.vIndices[i + 1], 1 + m.tIndices[i + 1], 1 + m.nIndices[i + 1],
                    1 + m.vIndices[i + 2], 1 + m.tIndices[i + 2], 1 + m.nIndices[i + 2]);
            
        }
    }
    else if (m.type == MESH_TYPE_QUADS)
    {
     
        for(u32 i = 0; i < m.indexCount; i+=4)
        {
            fprintf(f, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                    1 + m.vIndices[i    ], 1 + m.tIndices[i    ], 1 + m.nIndices[i    ],
                    1 + m.vIndices[i + 1], 1 + m.tIndices[i + 1], 1 + m.nIndices[i + 1],
                    1 + m.vIndices[i + 2], 1 + m.tIndices[i + 2], 1 + m.nIndices[i + 2],
                    1 + m.vIndices[i + 3], 1 + m.tIndices[i + 3], 1 + m.nIndices[i + 3]);
            
        }   
    }
    
    fclose(f);
    return true;
    
    
}
#if 0 
flocal bool castMesh(v3 ro, v3 rd, const EntityMesh& mesh, v3* intersection)
{
    v3 result = {};
    for (u32 i = 0; i < mesh.indexCount; i+=3)
    {
        v3 a = xyz(mesh.positions[mesh.vIndices[i  ]]);
        v3 b = xyz(mesh.positions[mesh.vIndices[i+1]]);
        v3 c = xyz(mesh.positions[mesh.vIndices[i+2]]);
        if (ray_triangle_x(ro, rd, a, b, c, &result))
        {
            *intersection = result;
            return true;
        }
    }
    *intersection = {};
    return false;
}

flocal v3* castMesh(v3 ro, v3 rd, const EntityMesh& mesh, u32 maxHits, u32* hitCount)
{
    v3* result = (v3*)calloc(maxHits, sizeof(v3));
    u32 numHits = 0;
    for (u32 i = 0; i < mesh.indexCount; i+=3)
    {
        v3 a = xyz(mesh.positions[mesh.vIndices[i  ]]);
        v3 b = xyz(mesh.positions[mesh.vIndices[i+1]]);
        v3 c = xyz(mesh.positions[mesh.vIndices[i+2]]);
        v3 res = {};
        if (ray_triangle_x(ro, rd, a, b, c, &res))
        {
            result[numHits++] = res;
        }
    }
    *hitCount = numHits;
    return result;
}
#endif
flocal EntityMesh convertMeshToEntityMesh(const Mesh& m, v3 color)
{

    EntityMesh out;
    out.type = m.type;
    out.paramTree = 0;
    out.indexCount = m.vIndices.size();
    out.vertexCount = m.pos.size();
    out.paramCount = m.coords.size();
    out.normalCount = m.normals.size();
    out.colorCount = m.colors.size();
    out.positions = (v4*)malloc(sizeof(v4) * out.vertexCount);
    out.parameters = (v2*)malloc(sizeof(v2) * out.paramCount);
    out.colors = (v4*)malloc(sizeof(v4) * out.colorCount);
    out.normals = (v4*)malloc(sizeof(v4) * out.normalCount);
    out.vIndices = (u32*)malloc(sizeof(u32) * out.indexCount);
    out.tIndices = (u32*)malloc(sizeof(u32) * out.indexCount);
    out.nIndices = (u32*)malloc(sizeof(u32) * out.indexCount);
    for (u32 idx = 0; idx < out.indexCount; idx++)
    {
        out.vIndices[idx] = m.vIndices[idx];
        out.tIndices[idx] = m.tIndices[idx];
        out.nIndices[idx] = m.nIndices[idx];
    }    
    for (u32 idx = 0; idx < m.pos.size(); idx++)
    {
        out.positions[idx] = m.pos[idx];
    }
    for (u32 idx = 0; idx < m.coords.size(); idx++)
    {
        out.parameters[idx] = m.coords[idx];
    }
    for (u32 idx = 0; idx < m.colors.size(); idx++)
    {
        out.colors[idx] = m.colors[idx];
    }
    for (u32 idx = 0; idx < m.normals.size(); idx++)
    {
        out.normals[idx] = m.normals[idx];
    }

    return out;                                      
}
