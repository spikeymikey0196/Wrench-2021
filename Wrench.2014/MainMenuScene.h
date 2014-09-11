#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Wrench.h"
#include <list>

using namespace std;
using namespace Wrench;

class MainMenuScene : public Scene
{
protected:
	Viewport *viewport;
	Camera *camera;

	WidgetNode *textNode;
	bool direction;

	list<ModelNode*> crystals;
	ModelNode *logo;

public:
	MainMenuScene();
	virtual void KeyDown(int KeyID);
	virtual void KeyUp(int KeyID);
	virtual void MouseButtonDown(float x, float y);
	virtual void MouseMotion(float x, float y);
	virtual void Update(unsigned int Delta);
};

#endif
