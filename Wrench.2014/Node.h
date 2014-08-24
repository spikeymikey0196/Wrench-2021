#ifndef NODE_H
#define NODE_H

#include "Transform.h"
#include "Matrix.h"
#include "BoundingBox.h"
#include "tinyxml.h"
#include <list>

using namespace std;

namespace Wrench
{
	class Scene;

	class Node
	{
		friend class Brain;

	protected:
		Transform transform;
		Scene *scene;
		Node *parent;
		list<Node *> children;

	public:
		Node();
		Node(Scene *nScene);
		Node(Scene *nScene, const Transform &nTransform);
		Node(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale);
		Node(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale);
		Node(Scene *nScene, TiXmlElement *entry);

		virtual void Render(const Matrix &worldMatrix);
		virtual void Update(unsigned int Delta);

		virtual Node *AddChild(Node *child);
		virtual void AddChildren(list<Node *> children);
		virtual void RemoveChild(Node*child);

		Transform *GetTransform();
		virtual BoundingBox GetBounds();
	};
}

#endif