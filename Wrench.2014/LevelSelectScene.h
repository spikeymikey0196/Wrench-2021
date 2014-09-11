#ifndef LEVELSELECTSCENE_H
#define LEVELSELECTSCENE_H

#include "Wrench.h"
#include <list>

using namespace std;
using namespace Wrench;

class LevelSelectScene : public Scene
{
protected:
	Viewport *viewport;
	Camera *camera;
	list<WidgetNode*> planets;

public:
	LevelSelectScene();
	virtual void MouseButtonDown(float x, float y);
	virtual void MouseMotion(float x, float y);
};

#endif
