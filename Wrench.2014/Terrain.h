#ifndef TERRAIN_H
#define TERRAIN_H

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "BoundingBox.h"
#include "Matrix.h"
#include "Waypoint.h"
#include "Material.h"

namespace Wrench
{
	class Terrain
	{
		friend class WorldChunkNode;

	protected:
		int width;
		int length;

		Shader *shader;
		Material *material;

		VertexArray vertexArray;

		Waypoint ***waypoints;

	public:
		Terrain();
		Terrain(int nWidth, int nLength);
		Terrain(int nWidth, int nLength, Material *nMaterial);
		Terrain(const string &heightmap, Material *nMaterial);

		void CreateBlank(int nWidth, int nLength);
		void SetHeight(int x, int z, float vertexHeight);
		void CalculateNormals();
		void SetupVBO();

		virtual void Render();
		virtual void Render(const Matrix &worldMatrix);
		virtual void RenderWaypoints(const Matrix &worldMatrix);

		float GetHeight(float x, float z);
		float GetHeight(const Vector3 &pos);
		virtual BoundingBox Bounds();

		Waypoint *WaypointAt(float x, float z);
	};
}

#endif
