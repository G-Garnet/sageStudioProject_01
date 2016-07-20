#include "Scenes.h"

SecondScene::SecondScene()
{
	player = new Junk2DSprite;
}

SecondScene::~SecondScene()
{
}

void SecondScene::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// 이미지 정보름 미리 선언
	player->settingTexture(graphics, "..\\Resources\\player.png", 32, 32, 1);
	player->setDegrees(0);
	player->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 16);

	return;
}

void SecondScene::Update()
{
	if (input->isKeyUp(VK_RETURN)) {
		Game *temp = new MainScenes; 

		ChangeScene(temp);
	}

	if (input->isKeyDown(VK_RIGHT)) player->setX(player->getX() + 1);
	if (input->isKeyDown(VK_LEFT))	player->setX(player->getX() - 1);
	if (input->isKeyDown(VK_DOWN))	player->setY(player->getY() + 1);
	if (input->isKeyDown(VK_UP))	player->setY(player->getY() - 1);

	//exitGame();
}

void SecondScene::render()
{
	graphics->spriteBegin();

	player->draw();

	graphics->spriteEnd();
}

//void MainScenes::releaseAll()
//{
//	Game::releaseAll();
//	return;
//}

//void MainScenes::resetAll()
//{
//	Game::resetAll();
//	return;
//}
