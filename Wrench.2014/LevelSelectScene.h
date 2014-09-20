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

	list<Node*> staticProps;
	list<Node*> widgets;
	list<Node*> units;

public:
	LevelSelectScene();
	virtual void MouseButtonDown(float x, float y);
	virtual void MouseMotion(float x, float y);

	virtual WidgetNode *AddWidget(WidgetNode *widget);
	virtual ModelNode *AddStaticProp(ModelNode *prop);
	virtual PhysicsNode *AddUnit(PhysicsNode *unit);

	virtual void RemoveWidget(WidgetNode *widget);
	virtual void RemoveStaticProp(ModelNode *prop);
	virtual void RemoveUnit(PhysicsNode *unit);
};

#endif
