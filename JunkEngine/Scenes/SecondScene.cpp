#include "Scenes.h"

SecondScene::SecondScene()
{
	player = new Junk2DSprite;
}

SecondScene::~SecondScene()
{
	SAFE_DELETE(player);
}

void SecondScene::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	// 이미지 정보름 미리 선언
	player->settingTexture(graphics, "..\\Resources\\player.png", 32, 32, 1);
	player->setDegrees(0);
	player->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2 + 16);

	initialized = true;

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
