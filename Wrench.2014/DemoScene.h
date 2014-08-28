#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "Wrench.h"
#include <list>
#include "PlayerNode.h"
#include "SkyBox.h"
#include "Shader.h"
#include "HealthBar.h"
#include "UI.h"

using namespace std;
using namespace Wrench;

class DemoScene : public Scene
{
protected:
	Viewport viewport;
	Camera *camera;

	//temp
	PlayerNode *player;
	UI *ui;

	list<UIElement *> tempElements;

	void Load(const char *filename);

public:
	DemoScene();
	virtual void Draw();
	virtual void KeyDown(int KeyID);
	virtual void KeyUp(int KeyID);
	virtual void MouseButtonDown(float x, float y);
	virtual void MouseMotion(float x, float y);
};

#endif
