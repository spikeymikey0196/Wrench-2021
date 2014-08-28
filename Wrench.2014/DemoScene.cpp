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

//Classes to create:
// * Rail camera - > list of pair<vector3, vector3>, position, lookat, lerp between points at SPEED
// * Waypoint - add spawner for terrain as well
// * Unit : ModelNode - initial npc
// * UI button, slider, checkbox, controller

DemoScene::DemoScene()
{
	content->LoadFile("./Content/Content.xml");

	viewport = Viewport(0, 0, 800, 600, 0.1f, 1000);

	player = new PlayerNode(this, Vector3(0.0f, 1.0f, 0.0f), Vector3::Zero(), 1.0f, content->GetModel("Sora"));

	Load("./Content/Levels/Test.xml");

	skybox = new SkyBox(this);

	healthbar = new HealthBar(NULL, Rect(10, 10, 200, 50), player->GetHealth());

	camera = new FollowCamera(player, 5, 2, Vector3(0,1,0));

	WidgetNode *test = new WidgetNode(this, Vector3(2, 2, 2), Vector3::Zero(), 1.0f, content->GetModel("Lightbulb"));
	test->SetOnClick([](WidgetNode *owner, Node *caller){ owner->GetTransform()->SetScale(2.0f); });

	widgets.push_back(test);
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
				staticProps.push_back(new ModelNode(this, entry, MissingModel::Get()));
			}
			else if (!valueStr.compare("Light"))
			{
				lights.push_back(new Light(entry));
			}
			else if (!valueStr.compare("WorldChunk"))
			{
				string terrainName = "";
				Vector3 position = Vector3::Zero();
				float waterHeight = FLT_MIN;

				entry->QueryStringAttribute("TerrainName", &terrainName);
				
				XmlLoop(entry, chunkEntry)
				{
					valueStr = chunkEntry->ValueStr();

					if (!valueStr.compare("Position"))
					{
						position = Vector3(chunkEntry);
					}
					else if (!valueStr.compare("WaterHeight"))
					{
						waterHeight = stof(chunkEntry->GetText());
					}
					else {}
				}

				worldChunks.push_back(new WorldChunkNode(this, position, content->GetTerrain(terrainName), waterHeight, content->GetTexture("Water")));
			}
			else if (!valueStr.compare("StaticProp"))
			{
				string modelName = "";
				Vector3 position = Vector3::Zero();
				Vector3 orientation = Vector3::Zero();
				float scale = 1.0f;

				XmlLoop(entry, staticEntry)
				{
					valueStr = staticEntry->ValueStr();

					if (!valueStr.compare("Model"))
						modelName = staticEntry->GetText();
					else if (!valueStr.compare("Position"))
						position = Vector3(staticEntry);
					else if (!valueStr.compare("Orientation"))
						orientation = Vector3(staticEntry);
					else if (!valueStr.compare("Scale"))
						scale = stof(staticEntry->GetText());
					else{}
				}

				staticProps.push_back(new ModelNode(this, position, orientation, scale, content->GetModel(modelName)));
			}
			else if (!valueStr.compare("Widget"))
			{
				//nodes.push_back(new ModelNode(this, Vector3(a*2.0f, b*2.0f, c * 2.0f), Vector3::Zero(), 0.5f, MissingModel::Get()));
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
	camera->Clear();
	viewport.UseViewport();
	camera->Begin();

	for (auto it : lights)
		it->Enable();
	
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
	//end tmep
	
	skybox->Render(camera->GetMatrix());
	
	for (auto it : worldChunks)
		it->RenderTerrain(camera->GetMatrix());

	for (auto it : staticProps)
		it->Render(camera->GetMatrix());

	for (auto it : widgets)
		it->Render(camera->GetMatrix());

	player->Render(camera->GetMatrix());

	for (auto it : worldChunks)
		it->RenderWater(camera->GetMatrix());

	for (auto it: lights)
		it->Disable();

	//2D TEST
	camera->Begin2D(viewport);
	healthbar->Render();
	//END 2D TEST

	camera->End();
};

void DemoScene::Update(unsigned int Delta)
{
	player->Update(Delta);
	player->CollideProps(&staticProps);
	player->CollideTerrain(&worldChunks);

	skybox->GetTransform()->SetPosition(player->GetTransform()->Position());
};

void DemoScene::KeyDown(int KeyID)
{
	player->SetKey(KeyID, 1);
};

void DemoScene::KeyUp(int KeyID)
{
	player->SetKey(KeyID, 0);
};

void DemoScene::MouseButtonDown(float x, float y)
{
	for (auto it : widgets)
		((ModelNode*)it)->GetTransform()->SetScale(1.0f);

	Node *closestNode = Ray::FromScreenCoordinates(x, y, *camera, viewport).ClosestIntersects(widgets);

	if (closestNode)
		((WidgetNode*)closestNode)->OnClick(NULL);
};

void DemoScene::MouseMotion(float x, float y)
{
	Node *closestNode = Ray::FromScreenCoordinates(x, y, *camera, viewport).ClosestIntersects(widgets);

	if (closestNode)
		((WidgetNode*)closestNode)->OnHover(NULL);
};
