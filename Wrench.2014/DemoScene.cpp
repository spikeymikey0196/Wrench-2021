#include "DemoScene.h"

#include "GLee.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "Ray.h"
#include "Utils.h"
#include <iostream>
#include <utility>
#include <string>
#include "HTTPTexture.h"

using namespace std;

//Classes to create:
// * Waypoint - add spawner for terrain as well
// * Unit : ModelNode - health, pathing
// * UI button, slider, checkbox, controller
// * FPS counter

DemoScene::DemoScene()
{
	content->LoadFile("./Content/Content.xml");
	

	callbacks->AddUICallback("SwitchToMenu", [](UIElement *e, int x, int y){Wrench::PopScene(); });

	callbacks->AddUICallback("BeginRail", [this](UIElement *sender, int x, int y){

		this->ClearRenderPasses();

		//camera leak - convert
		this->camera = new RailCamera(Vector3(sin(0) * 128.0f + 128.0f, 30, cos(0) * 128.0f + 128.0f), Vector3(128, 18, 128), RAIL_ONCE);
		((RailCamera*)this->camera)->Play();
		for (int a = 1; a < 10; a++)
			((RailCamera*)this->camera)->AddRailPoint(Vector3(sin(0.25f * a) * 128.0f + 128.0f, 30, cos(0.25f * a) * 128.0f + 128.0f), Vector3(128, 18, 128));

		((RailCamera*)this->camera)->SetOnFinish(callbacks->GetRailCallback("SwitchToFollow"));


		AddRenderPass(this->camera, &this->viewport, this->ui);

		for (auto it : this->tempElements)
		{
			this->ui->RemoveElement(it);
			//delete it;	//another leak
		}
		this->tempElements.clear();
	});

	callbacks->AddRailCallback("SwitchToFollow", [this](RailCamera *cam)
	{
		this->ClearRenderPasses();

		this->camera = new FollowCamera(this->player, 5, 2, Vector3(0, 1, 0));
		AddRenderPass(this->camera, &this->viewport, this->ui);

		//convert to shared_ptr
		//delete cam;
	});

	callbacks->AddWidgetCallback("OpenMenu", [this](WidgetNode *owner, Node *caller, const Vector2 &mousePos)
	{
		owner->GetTransform()->SetScale(2.0f);
		for (int a = 0; a < 6; a++)
		{
			UIElement *e = new UIElement(NULL, Rect(mousePos.x + sin(a) * 120 - 25, mousePos.y + cos(a) * 120 - 25, 50, 50), callbacks->GetUICallback("BeginRail"));

			this->tempElements.push_back(e);
			this->ui->AddElement(e);
		}
	});









	Load("./Content/Levels/Test.xml");

	viewport = Viewport(0, 0, 800, 600, 0.1f, 1000);
	player = new PlayerNode(this, Vector3(125.0f, 30.0f, 80.0f), Vector3::Zero(), 1.0f, content->GetModel("Sora"));
	//skybox = new SkyBox(this, player);
	camera = new FollowCamera(player, 5, 2, Vector3(0,1,0));

	for (int a = 0; a < 4; a++)
	{
		UnitNode *u = new UnitNode(this, Vector3(a, 30.0f, -a * 2.0f - 2.0f), Vector3::Zero(), 1.0f, content->GetModel("Sora"));
		AddUnit(u);
	}

	units.push_back(player);
	
	

	//move into UI XML file
	//make nestable
	ui = new UI();
	ui->AddElement(new HealthBar(NULL, Rect(10, 10, 200, 50), player->GetHealth()));
	ui->AddElement(new UIElement(NULL, Rect(10, 100, 100, 50), callbacks->GetUICallback("SwitchToMenu")));
	
	AddRenderPass(camera, &viewport, ui);
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
				AddStaticProp(new ModelNode(this, entry, MissingModel::Get()));
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

				AddWorldChunk(new WorldChunkNode(this, position, content->GetTerrain(terrainName), waterHeight, content->GetTexture("Water")));
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

				AddStaticProp(new ModelNode(this, position, orientation, scale, content->GetModel(modelName)));
			}
			else if (!valueStr.compare("Widget"))
			{
				string modelName = "";
				Vector3 position = Vector3::Zero();
				Vector3 orientation = Vector3::Zero();
				float scale = 1.0f;

				string clickCallback = "";
				string hoverCallback = "";

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
					else if (!valueStr.compare("OnClick"))
						clickCallback = staticEntry->GetText();
					else if (!valueStr.compare("OnHover"))
						hoverCallback = staticEntry->GetText();
					else{}
				}

				WidgetNode *node = new WidgetNode(this, position, orientation, scale, content->GetModel(modelName));

				if (clickCallback.size() > 0) node->SetOnClick(callbacks->GetWidgetCallback(clickCallback));
				if (hoverCallback.size() > 0) node->SetOnHover(callbacks->GetWidgetCallback(hoverCallback));

				AddWidget(node);
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

	//TEMP - will go into a shader
	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);
	
	Scene::Draw();
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
	if (!ui->Click(x, y))
	{
		for (auto it : tempElements)
		{
			ui->RemoveElement(it);
			delete it;
		}
		tempElements.clear();

		Node *closestNode = Ray::FromScreenCoordinates(x, y, *camera, viewport).ClosestIntersects(widgets);

		if (closestNode)
			((WidgetNode*)closestNode)->OnClick(player, Vector2(x, 600-y));
	}
};

void DemoScene::MouseMotion(float x, float y)
{
	Node *closestNode = Ray::FromScreenCoordinates(x, y, *camera, viewport).ClosestIntersects(widgets);

	if (closestNode)
		((WidgetNode*)closestNode)->OnHover(player, Vector2(x, 600-y));
};
