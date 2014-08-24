#include "DemoScene.h"

#include "GLee.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "Ray.h"
#include "Utils.h"
#include <iostream>
#include <utility>
#include <string>

using namespace std;

DemoScene::DemoScene()
{
	content->LoadFile("./Content/Content.xml");

	viewport = Viewport(0, 0, 800, 600, 0.1f, 1000);
	camera = Camera(Vector3(0, 0, 10), Vector3::Zero(), Vector3::Up());

	for (int a = 0; a < 3; a++)
		for (int b = 0; b < 3; b++)
			for (int c = 0; c < 3; c++)
				nodes.push_back(new ModelNode(this, Vector3(a*2.0f, b*2.0f, c * 2.0f), Vector3::Zero(), 0.5f, MissingModel::Get()));

	player = new PlayerNode(this, Vector3(0.0f, 1.0f, 0.0f), Vector3::Zero(), 1.0f, content->GetModel("Sora"));

	Load("./Content/Levels/Test.xml");

	skybox = new SkyBox(this);


	for (float x = -6.0f; x <= 2.0f; x++)
	{
		for (float z = -6.0f; z <= 2.0f; z++)
		{
			for (int counter = 0; counter < 5; counter++)
			{
				clutter.push_back(new ModelNode(this, Vector3(x + cos(counter), -2.85f, z + sin(counter)), Vector3::Zero(), 1.0f, content->GetModel("Adiantum")));
			}
		}
	}

	healthbar = new HealthBar(NULL, Rect(10, 10, 200, 50), player->GetHealth());

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
};

void DemoScene::Load(const char *filename)
{
	TiXmlDocument doc;

	if (doc.LoadFile(filename))
	{
		TiXmlElement *root = doc.RootElement();
		
		XmlLoop(root, entry)
		{
			string valueStr = entry->ValueStr();

			if (!valueStr.compare("Platform"))
			{
				platforms.push_back(new ModelNode(this, entry, MissingModel::Get()));
			}
			else if (!valueStr.compare("Light"))
			{
				lights.push_back(new Light(entry));
			}
			else
			{
				//
			}
		}
	}
}

void DemoScene::Draw()
{
	camera.Clear();
	viewport.UseViewport();
	camera.Begin();

	for (auto it : lights)
		it->Enable();

	skybox->Render(camera.GetMatrix());

	for (auto it : nodes)
		it->Render(camera.GetMatrix());

	for (auto it : platforms)
		it->Render(camera.GetMatrix());

	for (auto it : clutter)
		it->Render(camera.GetMatrix());

	player->Render(camera.GetMatrix());

	for (auto it: lights)
		it->Disable();

	//2D TEST
	camera.Begin2D(viewport);

	healthbar->Render();
	//END 2D TEST

	camera.End();
};

void DemoScene::Update(unsigned int Delta)
{
	player->Update(Delta);
	player->CollidePlatforms(&platforms);

	camera.SetFocus(player->GetTransform()->Position() + Vector3(0,1.5,0));
	camera.SetEye(player->GetTransform()->Position() + player->GetTransform()->GetMatrix().Backward() * 5.0f + Vector3(0,2,0));
};

void DemoScene::KeyDown(int KeyID)
{
	if (KeyID == VK_UP)
		player->SetKey(PKEY_FORWARD, 1);

	if (KeyID == VK_DOWN)
		player->SetKey(PKEY_BACKWARD, 1);

	if (KeyID == VK_LEFT)
		player->SetKey(PKEY_LEFT, 1);

	if (KeyID == VK_RIGHT)
		player->SetKey(PKEY_RIGHT, 1);

	if (KeyID == VK_SPACE)
		player->SetKey(PKEY_JUMP, 1);

	if (KeyID == 'Q')
		player->SetKey(PKEY_LSTRAFE, 1);

	if (KeyID == 'E')
		player->SetKey(PKEY_RSTRAFE, 1);
	
	if (KeyID == VK_ESCAPE)
		exit(0);
};

void DemoScene::KeyUp(int KeyID)
{
	if (KeyID == VK_UP)
		player->SetKey(PKEY_FORWARD, 0);

	if (KeyID == VK_DOWN)
		player->SetKey(PKEY_BACKWARD, 0);

	if (KeyID == VK_LEFT)
		player->SetKey(PKEY_LEFT, 0);

	if (KeyID == VK_RIGHT)
		player->SetKey(PKEY_RIGHT, 0);

	if (KeyID == 'Q')
		player->SetKey(PKEY_LSTRAFE, 0);

	if (KeyID == 'E')
		player->SetKey(PKEY_RSTRAFE, 0);
};

void DemoScene::MouseButtonDown(float x, float y)
{
	for (auto it : nodes)
		((ModelNode*)it)->GetTransform()->SetScale(0.5f);

	Node *closestNode = Ray::FromScreenCoordinates(x, y, camera, viewport).ClosestIntersects(nodes);

	if (closestNode)
	{
		nodes.remove(closestNode);
		delete closestNode;
	}
};

void DemoScene::MouseMotion(float x, float y)
{
	for (auto it : nodes)
		((ModelNode*)it)->GetTransform()->SetScale(0.5f);

	Node *closestNode = Ray::FromScreenCoordinates(x, y, camera, viewport).ClosestIntersects(nodes);

	if (closestNode)
		closestNode->GetTransform()->SetScale(1.0f);;
};
