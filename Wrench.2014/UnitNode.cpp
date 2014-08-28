#include "UnitNode.h"
#include "WorldChunkNode.h"
#include "Scene.h"
#include "UnitBrain.h"

namespace Wrench
{
	UnitNode::UnitNode()
		: ModelNode(), brain(NULL){};

	UnitNode::UnitNode(Scene *nScene, Model *nModel)
		: ModelNode(nScene, nModel), velocity(Vector3::Zero()), brain(NULL) {};

	UnitNode::UnitNode(Scene *nScene, const Transform &nTransform, Model *nModel)
		: ModelNode(nScene, nTransform, nModel), velocity(Vector3::Zero()), brain(NULL) {};

	UnitNode::UnitNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, const Vector3 &nScale, Model *nModel)
		: ModelNode(nScene, nPosition, nOrientation, nScale, nModel), velocity(Vector3::Zero()), brain(NULL) {};

	UnitNode::UnitNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel)
		: ModelNode(nScene, nPosition, nOrientation, nScale, nModel), velocity(Vector3::Zero()), brain(NULL) {};

	UnitNode::UnitNode(Scene *nScene, TiXmlElement *entry)
		: ModelNode(nScene, entry), velocity(Vector3::Zero()), brain(NULL) {};

	UnitNode::UnitNode(Scene *nScene, TiXmlElement *entry, Model *nModel)
		: ModelNode(nScene, entry, nModel), velocity(Vector3::Zero()), brain(NULL) {};

	void UnitNode::Update(unsigned int Delta)
	{
		velocity.y = velocity.y - scene->MillisecondGravity().y * (float)Delta;

		if (velocity.y < -1.0f)		//replace with max fall speed in scene
			velocity.y = -1.0f;

		transform.SetPosition(transform.Position() + velocity);

		if (brain)
			brain->Update(Delta);

		ModelNode::Update(Delta);
	};

	void UnitNode::AddVelocity(float x, float y, float z)
	{
		velocity += Vector3(x, y, z);
	};

	void UnitNode::CollideProps(list<Node *> *props)
	{
		for (auto it : *props)
		{
			if (it == this)
				continue;

			if (this->GetBounds().Intersects(it->GetBounds()))
			{
				//undo move
				transform.SetPosition(transform.Position() - velocity);

				//X
				transform.SetPosition(transform.Position() + Vector3(velocity.x, 0, 0));
				if (this->GetBounds().Intersects(it->GetBounds()))
				{
					transform.SetPosition(transform.Position() - Vector3(velocity.x, 0, 0));
					velocity.x = 0.0f;

					//on wall hit here
				}
				transform.SetPosition(transform.Position() - Vector3(velocity.x, 0, 0));
				//end X

				//Y
				transform.SetPosition(transform.Position() + Vector3(0, velocity.y, 0));
				if (this->GetBounds().Intersects(it->GetBounds()))
				{
					transform.SetPosition(transform.Position() - Vector3(0, velocity.y, 0));
					velocity.y = 0.0f;

					//on floor hit here
				}
				transform.SetPosition(transform.Position() - Vector3(0, velocity.y, 0));
				//end Y

				//Z
				transform.SetPosition(transform.Position() + Vector3(0, 0, velocity.z));
				if (this->GetBounds().Intersects(it->GetBounds()))
				{
					transform.SetPosition(transform.Position() - Vector3(0, 0, velocity.z));
					velocity.z = 0.0f;

					//on wall hit here
				}
				transform.SetPosition(transform.Position() - Vector3(0, 0, velocity.z));
				//end Z

				//redo move
				transform.SetPosition(transform.Position() + velocity);
			}
		}
	};

	void UnitNode::CollideTerrain(list<WorldChunkNode*> *worldChunks)
	{
		for (auto it : *worldChunks)
		{
			BoundingBox bounds = GetBounds();
			if (bounds.Intersects(it->GetBounds()))
			{
				float height = it->GetTerrainHeight(GetTransform()->Position());

				if (height != FLT_MIN)
				{
					//initial version
					if (abs(height - GetTransform()->Position().y) <= abs(velocity.y) + (bounds.Max().y - bounds.Min().y) / 2.0f && velocity.y < 0.0f)
					{
						Vector3 v = GetTransform()->Position();
						v.y = height;
						velocity.y = 0.0f;
						GetTransform()->SetPosition(v);
						break;
					}
				}
			}
		}
	};

}