#include "MainMenuScene.h"
#include "DemoScene.h"
#include "LevelSelectScene.h"

MainMenuScene::MainMenuScene()
{
	viewport = new Viewport(0, 0, Wrench::ScreenWidth(), Wrench::ScreenHeight(), 0.1f, 1000.0f);
	camera = new Camera(Vector3(0, 0, 25), Vector3::Zero(), Vector3(0, 1, 0));

	WidgetNode *n = new WidgetNode(this, Vector3(-8, -2.5f, 0), Vector3(), 1.0f, new ModelObj("./Content/Models/NewGame/NewGame.obj", new Texture(Color4(1,1,1,1),4,4)));
	WidgetNode *l = new WidgetNode(this, Vector3(-8, -5.0f, 0), Vector3(), 1.0f, new ModelObj("./Content/Models/LoadGame/LoadGame.obj", new Texture(Color4(1, 1, 1, 1), 4, 4)));
	WidgetNode *s = new WidgetNode(this, Vector3(-8, -7.5f, 0), Vector3(), 1.0f, new ModelObj("./Content/Models/Settings/Settings.obj", new Texture(Color4(1, 1, 1, 1), 4, 4)));


	n->SetOnClick([this](WidgetNode *owner, Node *caller, const Vector2 &mousePos)
	{
		Wrench::PushScene(new LevelSelectScene());
	});

	textNode = NULL;
	direction = false;

	for (int a = 0; a < 3; a++)
	{
		ModelNode *c = new ModelNode(this, Vector3(-13, -a * 3 - 3.0f, -5), Vector3(), 1.0f, new ModelObj("./Content/Models/IcoSphere/IcoSphere.obj", new Texture(Color4(0, 0, 1, 1), 4, 4)));
		AddStaticProp(c);
		crystals.push_back(c);
	}

	logo = new ModelNode(this, Vector3(-10, 8, -5), Vector3(), 3.0f, new ModelObj("./Content/Models/Wrench/Wrench.obj", new Texture(Color4(0, 1, 0, 1), 4, 4)));
	AddStaticProp(logo);

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
	

	AddRenderPass(camera, viewport, NULL);

	this->AddWidget(n);
	this->AddWidget(l);
	this->AddWidget(s);

	//BasicShader::Get()->Bind();
};

void MainMenuScene::Update(unsigned int Delta)
{
	if (textNode)
	{
		Vector3 rot = textNode->GetTransform()->Orientation();

		if (direction)
			rot.y += 0.01f;
		else
			rot.y -= 0.01f;

		if (abs(rot.y) > 0.3f)
			direction = !direction;

		textNode->GetTransform()->SetOrientation(rot);
	}

	for (auto it : crystals)
	{
		Vector3 o = it->GetTransform()->Orientation();
		o.y += 0.05f;
		it->GetTransform()->SetOrientation(o);
	}

	Vector3 r = logo->GetTransform()->Orientation();
	r.y += 0.01f;
	logo->GetTransform()->SetOrientation(r);

	//if (KeyState('A'))
	//	exit(0);
};

void MainMenuScene::KeyDown(int KeyID)
{
	int a = GetKeyState('A');

	if (a & (1 << 8))
		SetMousePos(100, 200);
};

void MainMenuScene::KeyUp(int KeyID)
{
	//
};

void MainMenuScene::MouseButtonDown(float x, float y)
{
	Node *closestNode = Ray::FromScreenCoordinates(x, y, *camera, *viewport).ClosestIntersects(widgets);

	if (closestNode)
	{
		((WidgetNode*)closestNode)->OnClick(NULL, Vector2(x, Wrench::ScreenHeight() - y));
	}
};

void MainMenuScene::MouseMotion(float x, float y)
{
	Node *closestNode = Ray::FromScreenCoordinates(x, y, *camera, *viewport).ClosestIntersects(widgets);

	if (closestNode)
	{
		((WidgetNode*)closestNode)->OnHover(NULL, Vector2(x, Wrench::ScreenHeight() - y));

		if (textNode && textNode != (WidgetNode*)closestNode)
		{
			Vector3 rot = textNode->GetTransform()->Orientation();
			rot.y = 0;
			textNode->GetTransform()->SetOrientation(rot);
		}

		textNode = (WidgetNode*)closestNode;
	}
	else
	{
		if (textNode)
		{
			Vector3 rot = textNode->GetTransform()->Orientation();
			rot.y = 0;
			textNode->GetTransform()->SetOrientation(rot);
			textNode = NULL;
		}
	}
};



WidgetNode *MainMenuScene::AddWidget(WidgetNode *widget)
{
	widgets.push_back((Node*)widget);
	this->AddNode(widget);
	return widget;
};

ModelNode *MainMenuScene::AddStaticProp(ModelNode *prop)
{
	staticProps.push_back(prop);
	this->AddNode(prop);
	return prop;
};

PhysicsNode *MainMenuScene::AddUnit(PhysicsNode *unit)
{
	units.push_back(unit);
	this->AddNode(unit);
	return unit;
};

void MainMenuScene::RemoveWidget(WidgetNode *widget)
{
	widgets.remove((Node*)widget);
	this->RemoveNode(widget);
};

void MainMenuScene::RemoveStaticProp(ModelNode *prop)
{
	staticProps.remove(prop);
	this->RemoveNode(prop);
};

void MainMenuScene::RemoveUnit(PhysicsNode *unit)
{
	units.remove(unit);
	this->RemoveNode(unit);
};
