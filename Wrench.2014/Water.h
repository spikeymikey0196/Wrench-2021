#ifndef WATER_H
#define WATER_H

#include "VertexArray.h"
#include "BoundingBox.h"
#include "Texture.h"
#include "Shader.h"
#include "Matrix.h"

namespace Wrench
{
	class Water
	{
		friend class WorldChunkNode;

	protected:
		int width;
		int length;

		unsigned int tex0;
		unsigned int ticks;

		Shader *shader;
		Texture *texture;

		VertexArray vertexArray;

	public:
		Water();
		Water(int nWidth, int nLength, float waterHeight, Texture *nTexture);

		void CreateBlank(int nWidth, int nLength, float waterHeight);
		void SetHeight(int x, int z, float vertexHeight);
		void SetupVBO();

		virtual void Render();
		virtual void Render(const Matrix &worldMatrix);

		float GetHeight(float x, float z);
		float GetHeight(const Vector3 &pos);
		virtual BoundingBox Bounds();
	};
}

#endif
