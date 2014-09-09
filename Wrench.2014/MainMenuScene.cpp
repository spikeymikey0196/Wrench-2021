#include "MainMenuScene.h"
#include "DemoScene.h"

MainMenuScene::MainMenuScene()
{
	ui = new UI();
	viewport = new Viewport(0, 0, 800, 600);
	camera = new Camera();

	ui->AddElement(new UIElement(NULL, Rect(300, 200, 200, 50), new Texture("./Content/Textures/btnTest.png"), Rect(0, 0, 1, 1), [](UIElement *, int, int){ Wrench::PushScene(new DemoScene()); }));
	ui->AddElement(new UIElement(NULL, Rect(300, 500, 200, 50), new Texture("./Content/Textures/btnTest.png"), Rect(0, 0, 1, 1), [](UIElement *, int, int){ Wrench::PushScene(new DemoScene()); }));

	ui->AddElement(new UIString(NULL, Rect(0, 0, 0, 0), new Font("./Content/Fonts/DemoFont.png", Rect(0, 0, 20, 20), 32), "0123456ASJHLJHGs;ifjhsiegfsg", Color4(1, 0, 0, 1), 1.0f));

	AddRenderPass(camera, viewport, ui);
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
	ui->Click(x, y);
};

void MainMenuScene::MouseMotion(float x, float y)
{
	//
};
