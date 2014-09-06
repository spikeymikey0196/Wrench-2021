#include "PlayerNode.h"
#include "Wrench.h"
#include <sstream>

using namespace std;

PlayerNode::PlayerNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel)
	: PhysicsNode(nScene, nPosition, nOrientation, nScale, nModel)
{
	for (int a = 0; a < 7; a++)
		keys[a] = 0;

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
		velocity = transform.GetMatrix().Forward().Normalize() * 0.1f;
	}
	else if (keys[PKEY_BACKWARD] > 0)
	{
		velocity = transform.GetMatrix().Forward().Normalize() * -0.1f;
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
	
	velocity.y = y;

	PhysicsNode::Update(Delta);
};

void PlayerNode::SetKey(int k, int status)
{
	switch (k)
	{
	case VK_UP: keys[PKEY_FORWARD] = status; break;
	case VK_DOWN: keys[PKEY_BACKWARD] = status; break;
	case VK_LEFT: keys[PKEY_LEFT] = status; break;
	case VK_RIGHT: keys[PKEY_RIGHT] = status; break;
	case VK_SPACE: keys[PKEY_JUMP] = status; break;

	case 'P':
	{
		stringstream S;
		S << "X: " << transform.Position().x << " Y: " << transform.Position().y << " Z: " << transform.Position().z;
		Wrench::SetWindowTitle(S.str().c_str());
	}
	break;

	case VK_ESCAPE: exit(0); break;

	case VK_F1:
	{
		if (status)
		{
			stringstream S;
			S << "SS_" << Wrench::GetTicks() << ".bmp";
			Wrench::TakeScreenshot(S.str().c_str());	//temp
		}
	}
	break;

	default: break;
	}
};

Range<int> *PlayerNode::GetHealth()
{
	return &health;
};
