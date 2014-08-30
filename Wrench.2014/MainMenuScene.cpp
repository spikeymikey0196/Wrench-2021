#include "MainMenuScene.h"
#include "DemoScene.h"

MainMenuScene::MainMenuScene()
{
	ui = new UI();
	viewport = new Viewport(0, 0, 800, 600);
	camera = new Camera();

	ui->AddElement(new UIElement(NULL, Rect(300, 200, 200, 50), [](UIElement *, int, int){ Wrench::PushScene(new DemoScene()); }));

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
