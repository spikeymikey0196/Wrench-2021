#ifndef TERRAIN_H
#define TERRAIN_H

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "BoundingBox.h"
#include "Matrix.h"

namespace Wrench
{
	class Terrain
	{
		friend class WorldChunkNode;

	protected:
		int width;
		int length;
		
		Shader *shader;
		Texture *controller;
		Texture *textures[4];

		VertexArray vertexArray;

	public:
		Terrain();
		Terrain(int nWidth, int nLength);
		Terrain(int nWidth, int nLength, Texture *nController, Texture *tex0, Texture *tex1, Texture *tex2, Texture *tex3);
		Terrain(const string &heightmap, Texture *nController, Texture *tex0, Texture *tex1, Texture *tex2, Texture *tex3);

		void CreateBlank(int nWidth, int nLength);
		void SetHeight(int x, int z, float vertexHeight);
		void CalculateNormals();

		virtual void Render();
		virtual void Render(const Matrix &worldMatrix);

		float GetHeight(float x, float z);
		float GetHeight(const Vector3 &pos);
		virtual BoundingBox Bounds();
	};
}

#endif
