#ifndef UNITNODE_H
#define UNITNODE_H

#include "ModelNode.h"
#include "Range.h"

namespace Wrench
{
	class WorldChunkNode;
	class UnitBrain;

	class UnitNode : public ModelNode
	{
		friend class UnitBrain;

	protected:
		Vector3 velocity;
		UnitBrain *brain;

	public:
		UnitNode();
		UnitNode(Scene *nScene, Model *nModel);
		UnitNode(Scene *nScene, const Transform &nTransform, Model *nModel);
		UnitNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale, Model *nModel);
		UnitNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel);
		UnitNode(Scene *nScene, TiXmlElement *entry);
		UnitNode(Scene *nScene, TiXmlElement *entry, Model *nModel);

		virtual void Update(unsigned int Delta);
		void AddVelocity(float x, float y, float z);

		virtual void CollideProps(list<Node *> *props);
		virtual void CollideTerrain(list<WorldChunkNode*> *worldChunks);
	};
}

#endif