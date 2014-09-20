#include "LevelSelectScene.h"
#include "DemoScene.h"

LevelSelectScene::LevelSelectScene()
{
	viewport = new Viewport(0, 0, Wrench::ScreenWidth(), Wrench::ScreenHeight(), 0.1f, 1000.0f);
	camera = new Camera(Vector3(0, 0, 25), Vector3::Zero(), Vector3(0, 1, 0));

	ModelObj *sphere = new ModelObj("./Content/Models/Sphere/Sphere.obj", new Texture("./Content/Models/Sphere/Sphere.png"));

	WidgetNode *p1 = new WidgetNode(this, Vector3(-8, 5, 0), Vector3(), 3.0f, sphere);
	WidgetNode *p2 = new WidgetNode(this, Vector3(6, 2, 0), Vector3(), 5.0f, sphere);
	WidgetNode *p3 = new WidgetNode(this, Vector3(-5, -5, 0), Vector3(), 2.0f, sphere);



	p1->SetOnClick([this](WidgetNode *owner, Node *caller, const Vector2 &mousePos)
	{
		Wrench::PushScene(new DemoScene("Island"));
	});

	AddWidget(p1);
	AddWidget(p2);
	AddWidget(p3);

	AddRenderPass(camera, viewport, NULL);

	//temp
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	float LightPos[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
	float Ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float diffuse[4] = { 1.0, 1.0, 1.0, 1.0 };
	float specular[4] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	//end temp
};

void LevelSelectScene::MouseButtonDown(float x, float y)
{
	Node *closestNode = Ray::FromScreenCoordinates(x, y, *camera, *viewport).ClosestIntersects(widgets);

	if (closestNode)
	{
		((WidgetNode*)closestNode)->OnClick(NULL, Vector2(x, Wrench::ScreenHeight() - y));
	}
};

void LevelSelectScene::MouseMotion(float x, float y)
{
	//
};


WidgetNode *LevelSelectScene::AddWidget(WidgetNode *widget)
{
	widgets.push_back((Node*)widget);
	this->AddNode(widget);
	return widget;
};

ModelNode *LevelSelectScene::AddStaticProp(ModelNode *prop)
{
	staticProps.push_back(prop);
	this->AddNode(prop);
	return prop;
};

PhysicsNode *LevelSelectScene::AddUnit(PhysicsNode *unit)
{
	units.push_back(unit);
	this->AddNode(unit);
	return unit;
};

void LevelSelectScene::RemoveWidget(WidgetNode *widget)
{
	widgets.remove((Node*)widget);
	this->RemoveNode(widget);
};

void LevelSelectScene::RemoveStaticProp(ModelNode *prop)
{
	staticProps.remove(prop);
	this->RemoveNode(prop);
};

void LevelSelectScene::RemoveUnit(PhysicsNode *unit)
{
	units.remove(unit);
	this->RemoveNode(unit);
};