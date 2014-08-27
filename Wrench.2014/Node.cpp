#include "Node.h"
#include "Utils.h"
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

namespace Wrench
{
	Node::Node()
	{
		transform = Transform();
		scene = NULL;
		parent = NULL;
		children = list<Node *>();
	};

	Node::Node(Scene *nScene)
	{
		transform = Transform();
		scene = nScene;
		parent = NULL;
		children = list<Node *>();
	};

	Node::Node(Scene *nScene, const Transform &nTransform)
	{
		transform = nTransform;
		scene = nScene;
		parent = NULL;
		children = list<Node *>();
	};

	Node::Node(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale)
	{
		transform = Transform(nPosition, nOrientation, nScale);
		scene = nScene;
		parent = NULL;
		children = list<Node *>();
	};

	Node::Node(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale)
	{
		transform = Transform(nPosition, nOrientation, nScale);
		scene = nScene;
		parent = NULL;
		children = list<Node *>();
	};

	Node::Node(Scene *nScene, TiXmlElement *entry)
	{
		scene = nScene;

		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("Transform")) transform = Transform(it);
			else if (!valueStr.compare("Children"))
			{
				XmlLoop(it, childEntry)
				{
					valueStr = childEntry->ValueStr();

					//BUILD EM!
				}
			}
		}
	};

	void Node::Render(const Matrix &worldMatrix)
	{
		Matrix m = transform.GetMatrix() * worldMatrix;

		//override by child classes

		for (auto it : children)
			it->Render(m);
	};

	void Node::Update(unsigned int Delta)
	{
		//override by child classes

		for (auto it : children)
			it->Update(Delta);
	};

	Node *Node::AddChild(Node *child)
	{
		if (find(children.begin(), children.end(), child) == children.end())
		{
			child->parent = this;
			children.push_back(child);
		}
		return child;
	};

	void Node::AddChildren(list<Node *> children)
	{
		for (auto child : children)
			AddChild(child);
	};

	void Node::RemoveChild(Node*child)
	{
		child->parent = NULL;
		children.remove(child);
	};

	Transform *Node::GetTransform()
	{
		return &transform;
	};

	BoundingBox Node::GetBounds()
	{
		return BoundingBox(transform.Position(), transform.Position());
	}
}