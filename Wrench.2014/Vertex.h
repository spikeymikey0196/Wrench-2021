#ifndef VERTEX_H
#define VERTEX_H

#include "Vector2.h"
#include "Vector3.h"
#include "Color4.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace Wrench
{
	struct Vertex
	{
		Vector3 position;
		Vector2 tex;
		Vector3 normal;
		Color4 color;
	};
}

#endif