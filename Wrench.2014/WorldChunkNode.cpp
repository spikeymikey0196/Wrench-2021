#include "WorldChunkNode.h"

namespace Wrench
{
	WorldChunkNode::WorldChunkNode()
		: Node()
	{
		terrain = NULL;
		water = NULL;
	};

	WorldChunkNode::WorldChunkNode(Scene *nScene)
		: Node(nScene)
	{
		terrain = NULL;
		water = NULL;
	};

	WorldChunkNode::WorldChunkNode(Scene *nScene, Terrain *nTerrain, Water *nWater)
		: Node(nScene)
	{
		terrain = nTerrain;
		water = nWater;

		if (terrain) terrain->SetupVBO();
		if (water) water->SetupVBO();
	};

	WorldChunkNode::WorldChunkNode(Scene *nScene, TiXmlElement *entry)
		: Node(nScene, entry)
	{
		//parse stuff
	};

	WorldChunkNode::WorldChunkNode(Scene *nScene, const Vector3 &nPosition, int nWidth, int nLength, float waterHeight, const string &heightMapFile, Material *nMaterial, Texture *waterTex)
		: Node(nScene, nPosition, Vector3::Zero(), 1.0f)
	{
		terrain = new Terrain(nWidth, nLength, nMaterial);

		if (waterHeight > 0.0f)
			water = new Water(nWidth, nLength, waterHeight, waterTex);

		if (terrain) terrain->SetupVBO();
		if (water) water->SetupVBO();
	};

	WorldChunkNode::WorldChunkNode(Scene *nScene, const Vector3 &nPosition, Terrain *nTerrain, Water *nWater)
		: WorldChunkNode(nScene, nTerrain, nWater)
	{
		transform.SetPosition(nPosition);
	};

	WorldChunkNode::WorldChunkNode(Scene *nScene, const Vector3 &nPosition, Terrain *nTerrain, float waterHeight, Texture *waterTexture)
		: WorldChunkNode(nScene, nPosition, nTerrain, NULL)
	{
		if (waterHeight != FLT_MIN)
			water = new Water(terrain->width, terrain->length, waterHeight, waterTexture);

		if (water) water->SetupVBO();
	};

	void WorldChunkNode::Render(const Matrix &worldMatrix)
	{
		RenderTerrain(worldMatrix);
		RenderChildren(worldMatrix);
		RenderWater(worldMatrix);
	};

	void WorldChunkNode::RenderTerrain(const Matrix &worldMatrix)
	{
		if (terrain) terrain->Render(transform.GetMatrix() * worldMatrix);
	};

	void WorldChunkNode::RenderChildren(const Matrix &worldMatrix)
	{
		Node::Render(transform.GetMatrix() * worldMatrix);
	};

	void WorldChunkNode::RenderWater(const Matrix &worldMatrix)
	{
		if (water) water->Render(transform.GetMatrix() * worldMatrix);
	};

	BoundingBox WorldChunkNode::GetBounds()
	{
		Vector3 pos = transform.Position();

		if (terrain) return BoundingBox(Vector3(pos.x, pos.y - 1000.0f, pos.z), Vector3(pos.x + terrain->width, pos.y + 1000.0f, pos.z + terrain->length));
		if (water) return BoundingBox(Vector3(pos.x, pos.y - 1000.0f, pos.z), Vector3(pos.x + water->width, pos.y + 1000.0f, pos.z + water->length));

		return BoundingBox(pos, pos);
	};

	float WorldChunkNode::GetTerrainHeight(const Vector3 &pos)
	{
		if (terrain)
			return terrain->GetHeight(((Vector3)pos) - transform.Position()) + transform.Position().y;
		return FLT_MIN;
	};

	float WorldChunkNode::GetWaterHeight(const Vector3 &pos)
	{
		if (water)
			return water->GetHeight(((Vector3)pos) - transform.Position()) + transform.Position().y;
		return FLT_MIN;
	};

	Terrain *WorldChunkNode::GetTerrain()
	{
		return terrain;
	};

	Water *WorldChunkNode::GetWater()
	{
		return water;
	};
}
