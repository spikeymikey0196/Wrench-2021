#ifndef MODELNODE_H
#define MODELNODE_H

#include "Node.h"
#include "Model.h"
#include "tinyxml.h"

namespace Wrench
{
	class ModelNode : public Node
	{
		friend class Brain;

	protected:
		Model *model;

	public:
		ModelNode();
		ModelNode(Scene *nScene, Model *nModel);
		ModelNode(Scene *nScene, const Transform &nTransform, Model *nModel);
		ModelNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale, Model *nModel);
		ModelNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel);
		ModelNode(Scene *nScene, TiXmlElement *entry);
		ModelNode(Scene *nScene, TiXmlElement *entry, Model *nModel);

		virtual void Render(const Matrix &worldMatrix);
		virtual void Update(unsigned int Delta);
		virtual BoundingBox GetBounds();
	};
}

#endif