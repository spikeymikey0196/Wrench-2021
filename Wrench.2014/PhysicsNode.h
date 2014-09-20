#ifndef PHYSICSNODE_H
#define PHYSICSNODE_H

#include "ModelNode.h"

namespace Wrench
{
	class WorldChunkNode;

	class PhysicsNode : public ModelNode
	{
	protected:
		Vector3 velocity;

	public:
		PhysicsNode();
		PhysicsNode(Scene *nScene, Model *nModel);
		PhysicsNode(Scene *nScene, const Transform &nTransform, Model *nModel);
		PhysicsNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale, Model *nModel);
		PhysicsNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel);
		PhysicsNode(Scene *nScene, TiXmlElement *entry);
		PhysicsNode(Scene *nScene, TiXmlElement *entry, Model *nModel);

		virtual void Update(unsigned int Delta);
		void AddVelocity(float x, float y, float z);
		Vector3 Velocity();
		void SetVelocity(const Vector3 &nVelocity);

		virtual void CollideNodes(list<Node *> *props);
		virtual void CollideTerrain(list<WorldChunkNode*> *worldChunks);
	};
}

#endif