#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "Vertex.h"
#include <vector>

using namespace std;

namespace Wrench
{
	enum VertexArrayAttributes
	{
		VA_NONE		=	0,
		VA_POSITION	=	1,
		VA_TEXTURE	=	2,
		VA_NORMAL	=	4,
		VA_COLOR	=	8,
		VA_INDICES	=	16,
	};

	class VertexArray
	{
	protected:
		unsigned int vboID;
		unsigned int indexID;

		int usageFlags;
		int numIndices;
		vector<Vertex> vertices;
		vector<unsigned int> indices;

	public:
		VertexArray();
		VertexArray(int nUsageFlags);
		void PushVertex(const Vertex &v);
		void SetVertex(int index, const Vertex &v);
		Vertex GetVertex(unsigned int index);

		void PushTriangleIndices(unsigned int v1, unsigned int v2, unsigned int v3);
		void SetTriangleIndex(unsigned int index, unsigned int v1);
		
		void GenerateVBO();

		void Render();
	
	protected:
		void RenderByArray();
		void RenderByElements();
		void RenderAsVBO();
	};
}

#endif
