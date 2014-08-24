#include "PlayerNode.h"

PlayerNode::PlayerNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel)
	: ModelNode(nScene, nPosition, nOrientation, nScale, nModel)
{
	velocity = Vector3::Zero();
	for (int a = 0; a < 7; a++)
		keys[a] = 0;

	if (nModel)
		nModel->ShrinkXZ();

	health = Range<int>(0, 100, 100);
};

void PlayerNode::Update(unsigned int Delta)
{
	float y = velocity.y;
	
	velocity = Vector3::Zero();

	if(keys[PKEY_LEFT] > 0)
	{
		transform.SetOrientation(transform.Orientation() + Vector3(0, 0.05f, 0));
	}
	else if(keys[PKEY_RIGHT] > 0)
	{
		transform.SetOrientation(transform.Orientation() + Vector3(0, -0.05f, 0));
	}
	else{}

	if (keys[PKEY_FORWARD] > 0)
	{
		velocity = transform.GetMatrix().Forward() * 0.1f;
	}
	else if (keys[PKEY_BACKWARD] > 0)
	{
		velocity = transform.GetMatrix().Forward() * -0.1f;
	}
	else{}

	if (keys[PKEY_LSTRAFE] > 0)
	{
		velocity = transform.GetMatrix().Left() * 0.1f;
	}
	else if (keys[PKEY_RSTRAFE] > 0)
	{
		velocity = transform.GetMatrix().Left() * -0.1f;
	}
	else{}

	if (keys[PKEY_JUMP] > 0)
	{
		if (abs(y) < 0.1f)
			y += 0.2f;
		keys[PKEY_JUMP] = 0;
	}
	
	velocity.y = y - 0.01f;

	if (velocity.y < -1.0f)
		velocity.y = -1.0f;

	transform.SetPosition(transform.Position() + velocity);

	ModelNode::Update(Delta);
	IBrain::Update(Delta);
};

void PlayerNode::CollidePlatforms(list<Node *> *platforms)
{
	for (auto it : *platforms)
	{
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

void PlayerNode::AddVelocity(float x, float y, float z)
{
	velocity += Vector3(x, y, z);
};

void PlayerNode::SetKey(int k, int status)
{
	keys[k] = status;
};

Range<int> *PlayerNode::GetHealth()
{
	return &health;
};
