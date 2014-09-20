#include "PlayerNode.h"
#include "Wrench.h"
#include <sstream>

using namespace std;

PlayerNode::PlayerNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel)
	: PhysicsNode(nScene, nPosition, nOrientation, nScale, nModel)
{
	//for (int a = 0; a < 7; a++)
	//	keys[a] = 0;
	prevKBS = KeyboardState::GetState();

	health = Range<int>(0, 100, 100);
};

void PlayerNode::Update(unsigned int Delta)
{
	float y = velocity.y;
	velocity = Vector3::Zero();

	KeyboardState kbs = KeyboardState::GetState();

	if(kbs.IsKeyDown(VK_LEFT))
	{
		transform.SetOrientation(transform.Orientation() + Vector3(0, 0.05f, 0));
	}
	else if (kbs.IsKeyDown(VK_RIGHT))
	{
		transform.SetOrientation(transform.Orientation() + Vector3(0, -0.05f, 0));
	}
	else{}

	if (kbs.IsKeyDown(VK_UP))
	{
		velocity = transform.GetMatrix().Forward().Normalize() * 0.1f;
	}
	else if (kbs.IsKeyDown(VK_DOWN))
	{
		velocity = transform.GetMatrix().Forward().Normalize() * -0.1f;
	}
	else{}

	if (kbs.IsKeyDown(VK_SPACE) && prevKBS.IsKeyUp(VK_SPACE))
	{
		if (abs(y) < 0.1f)
			y += 0.2f;
	}
	
	velocity.y = y;

	prevKBS = kbs;
	PhysicsNode::Update(Delta);
};

void PlayerNode::SetKey(int k, int status)
{
	switch (k)
	{
	//case VK_UP: keys[PKEY_FORWARD] = status; break;
	//case VK_DOWN: keys[PKEY_BACKWARD] = status; break;
	//case VK_LEFT: keys[PKEY_LEFT] = status; break;
	//case VK_RIGHT: keys[PKEY_RIGHT] = status; break;
	//case VK_SPACE: keys[PKEY_JUMP] = status; break;

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
