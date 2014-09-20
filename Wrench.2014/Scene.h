#ifndef SCENE_H
#define SCENE_H

#include "ContentManager.h"
#include "CallbackManager.h"
#include "Viewport.h"
#include "UI.h"
#include <list>
#include <tuple>

using namespace std;

namespace Wrench
{
	class Scene
	{
		friend class Node;
		friend class ModelNode;
		friend class WidgetNode;
		friend class Camera;
		friend class WorldChunkNode;
		friend class PhysicsNode;

	protected:
		bool skipFrame;
		ContentManager *content;
		CallbackManager *callbacks;
		Vector3 gravity;

		Node *skybox;
		list<WorldChunkNode*> worldChunks;
		list<Node *> nodes;

		list<tuple<Camera*, Viewport*, UI*>> renderPasses;

	public:
		Scene();
		~Scene();
		virtual void Draw();
		virtual void Update(unsigned int Delta);
		virtual void KeyDown(int KeyID);
		virtual void KeyUp(int KeyID);
		virtual void MouseButtonDown(float x, float y);
		virtual void MouseButtonUp(float x, float y);
		virtual void MouseMotion(float x, float y);

		virtual Vector3 Gravity();
		virtual Vector3 MillisecondGravity();
		virtual void SetGravity(const Vector3 &nGravity);

		virtual void AddRenderPass(Camera *c, Viewport *v, UI *ui);
		virtual void ClearRenderPasses();

		virtual WorldChunkNode *AddWorldChunk(WorldChunkNode *chunk);
		virtual void RemoveWorldChunk(WorldChunkNode *chunk);

		virtual Node *AddNode(Node *n);
		virtual void RemoveNode(Node *n);

		virtual void Resize(int nWidth, int nHeight);
	};
}

#endif