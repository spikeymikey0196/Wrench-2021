#ifndef PLAYERNODE_H
#define PLAYERNODE_H

#include "Wrench.h"
#include <list>

using namespace std;
using namespace Wrench;

enum PlayerKeys
{
	PKEY_FORWARD = 0,
	PKEY_BACKWARD= 1,
	PKEY_LEFT	 = 2,
	PKEY_RIGHT	 = 3,
	PKEY_JUMP	 = 4,
	PKEY_LSTRAFE = 5,
	PKEY_RSTRAFE = 6,
};

class PlayerNode : public ModelNode, public IBrain
{
protected:
	Vector3 velocity;
	int keys[7];
	Range<int> health;

public:
	PlayerNode(Scene *nScene, const Vector3 &nPosition, const Vector3 &nOrientation, float nScale, Model *nModel);
	virtual void Update(unsigned int Delta);

	virtual void CollidePlatforms(list<Node *> *platforms);
	void AddVelocity(float x, float y, float z);

	void SetKey(int k, int status);

	Range<int> *GetHealth();
};

#endif
