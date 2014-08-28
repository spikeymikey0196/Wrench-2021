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
	Camera *camera;

	//temp
	HealthBar *healthbar;
	list<Light*> lights;
	
	//keep
	PlayerNode *player;

	//move into scene
	Node *skybox;
	list<WorldChunkNode*> worldChunks;	//terrain
	list<Node*> staticProps;			//solid unmoving
	list<Node*> widgets;				//can be interacted with
	list<Node*> units;					//todo

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
