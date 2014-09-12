#ifndef WORLDCHUNKNODE_H
#define WORLDCHUNKNODE_H

#include "Node.h"
#include "Terrain.h"
#include "Water.h"

namespace Wrench
{
	class WorldChunkNode : public Node
	{
	protected:
		Terrain *terrain;
		Water *water;

	public:
		WorldChunkNode();
		WorldChunkNode(Scene *nScene);
		WorldChunkNode(Scene *nScene, Terrain *nTerrain, Water *nWater);
		WorldChunkNode(Scene *nScene, TiXmlElement *entry);
		WorldChunkNode(Scene *nScene, const Vector3 &nPosition, int nWidth, int nLength, float waterHeight, const string &heightMapFile, Material *nMaterial, Texture *waterTex);
		WorldChunkNode(Scene *nScene, const Vector3 &nPosition, Terrain *nTerrain, Water *nWater);
		WorldChunkNode(Scene *nScene, const Vector3 &nPosition, Terrain *nTerrain, float waterHeight, Texture *waterTexture);

		virtual void Render(const Matrix &worldMatrix);
		virtual void RenderTerrain(const Matrix &worldMatrix);
		virtual void RenderChildren(const Matrix &worldMatrix);
		virtual void RenderWater(const Matrix &worldMatrix);

		virtual BoundingBox GetBounds();
		virtual float GetTerrainHeight(const Vector3 &pos);
		virtual float GetWaterHeight(const Vector3 &pos);

		Terrain *GetTerrain();
		Water *GetWater();
	};
}

#endif
