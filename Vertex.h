#ifndef VERTEX_H
#define VERTEX_H

#include "CommonDefines.h"
#include "MathUtils.h"
#include "Vector.h"
#include "Vector.cpp"

struct Vertex
{
	v3 pos;
    //float x;
	v3 color;
    //float y;
	v3 normal;
    //float z;
	v2 texCoord;
	bool operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};

namespace std
{
	template<> struct hash<Vertex>
	{
		size_t operator()(Vertex const& v) const
		{
			return ((v3hash(v.pos) ^
                     (v3hash(v.color) << 1)) >> 1) ^
				(v2hash(v.texCoord) << 1);
		}
	};
}


inline bool operator < (const Vertex& a, const Vertex& b)
{
    return (sqLen(a.pos) < sqLen(b.pos));
}

#endif /* VERTEX_H */
