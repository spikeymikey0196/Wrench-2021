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
	UI *ui;

	//temp
	PlayerNode *player;
	WidgetNode *terrainCursor;

	list<UIElement *> tempElements;

	list<Node*> staticProps;
	list<Node*> widgets;
	list<Node*> units;

	void Load(const char *filename);

public:
	DemoScene(const char *levelName);
	virtual void Draw();
	virtual void KeyDown(int KeyID);
	virtual void KeyUp(int KeyID);
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
