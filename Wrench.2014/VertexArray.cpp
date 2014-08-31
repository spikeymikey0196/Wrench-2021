#include "VertexArray.h"

#include "GLee.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace Wrench
{
	VertexArray::VertexArray()
	{
		usageFlags = 0;
		numIndices = 0;

		vboID = 0;
		indexID = 0;

		vertices = vector<Vertex>();
		indices = vector<unsigned int>();
	};

	VertexArray::VertexArray(int nUsageFlags)
		: VertexArray()
	{
		usageFlags = nUsageFlags;
	};

	void VertexArray::PushVertex(const Vertex &v)
	{
		vertices.push_back(v);
	};

	void VertexArray::SetVertex(int index, const Vertex &v)
	{
		vertices[index] = v;
	};

	Vertex VertexArray::GetVertex(unsigned int index)
	{
		return vertices[index];
	};

	void VertexArray::PushTriangleIndices(unsigned int v1, unsigned int v2, unsigned int v3)
	{
		indices.push_back(v1);
		indices.push_back(v2);
		indices.push_back(v3);

		numIndices += 3;
	};

	void VertexArray::SetTriangleIndex(unsigned int index, unsigned int v1)
	{
		indices[index] = v1;
	};

	void VertexArray::GenerateVBO()
	{
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), &vertices[0]);

		glNormalPointer(GL_FLOAT, sizeof(Vertex), &(vertices[0].normal.x));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(vertices[0].color.r));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &(vertices[0].tex.x));

		glGenBuffers(1, &indexID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	};

	void VertexArray::Render()
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glNormalPointer(GL_FLOAT, sizeof(Vertex), &(vertices[0].normal.x));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(vertices[0].color.r));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &vertices[0]);
		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &(vertices[0].tex.x));

		int vs = sizeof(Vertex);

		if (usageFlags & VA_INDICES)
		{
			if (vboID)
				RenderAsVBO();
			else
				RenderByElements();
		}
		else
			RenderByArray();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	};

	void VertexArray::RenderByArray()
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	};

	void VertexArray::RenderByElements()
	{
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, &indices[0]);
	};

	void VertexArray::RenderAsVBO()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexID);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
		glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
}