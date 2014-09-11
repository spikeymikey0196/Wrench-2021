#include "MainMenuScene.h"
#include "DemoScene.h"

MainMenuScene::MainMenuScene()
{
	viewport = new Viewport(0, 0, Wrench::ScreenWidth(), Wrench::ScreenHeight(), 0.1f, 1000.0f);
	camera = new Camera(Vector3(0, 0, 25), Vector3::Zero(), Vector3(0, 1, 0));

	WidgetNode *w = new WidgetNode(this, Vector3(), Vector3(), 1.0f, new ModelObj("./Content/Models/NewGame/NewGame.obj", new Texture(Color4(1,1,1,1),4,4)));

	w->SetOnClick([this](WidgetNode *owner, Node *caller, const Vector2 &mousePos)
	{
		Wrench::PushScene(new DemoScene());
	});

	textNode = NULL;
	direction = false;

	for (int a = 0; a < 3; a++)
	{
		ModelNode *c = new ModelNode(this, Vector3(-3, -a * 3, -5), Vector3(), 1.0f, new ModelObj("./Content/Models/IcoSphere/IcoSphere.obj", new Texture(Color4(0, 0, 1, 1), 4, 4)));
		AddStaticProp(c);
		crystals.push_back(c);
	}



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

	this->AddWidget(w);
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
};

void MainMenuScene::KeyDown(int KeyID)
{
	//
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
