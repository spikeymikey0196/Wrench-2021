#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Wrench.h"

using namespace Wrench;

class MainMenuScene : public Scene
{
protected:
	UI *ui;
	Viewport *viewport;
	Camera *camera;

public:
	MainMenuScene();
	virtual void KeyDown(int KeyID);
	virtual void KeyUp(int KeyID);
	virtual void MouseButtonDown(float x, float y);
	virtual void MouseMotion(float x, float y);
};

#endif
