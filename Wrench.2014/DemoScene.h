#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "Wrench.h"
#include <list>
#include "PlayerNode.h"
#include "SkyBox.h"
#include "Shader.h"
#include "HealthBar.h"

using namespace std;
using namespace Wrench;

class DemoScene : public Scene
{
protected:
	Viewport viewport;
	Camera camera;

	list<Node *> nodes;
	list<Node *> platforms;
	PlayerNode *player;

	list<Light*> lights;
	Node *skybox;

	list<WorldChunkNode*> worldChunks;

	list<Node *> clutter;

	HealthBar *healthbar;

	WorldChunkNode *chunk;

	void Load(const char *filename);

public:
	DemoScene();
	virtual void Draw();
	virtual void Update(unsigned int Delta);
	virtual void KeyDown(int KeyID);
	virtual void KeyUp(int KeyID);
	virtual void MouseButtonDown(float x, float y);
	virtual void MouseMotion(float x, float y);
};

#endif
