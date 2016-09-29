#include "Scenes.h"

SecondScene::SecondScene()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
}

SecondScene::~SecondScene()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
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
	Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room2\\Room2_bg.png");

	player->playerSetting(graphics);

	objectManager->AddObject(player, "Player");

	Map->mapMove(0, 0);

	initialized = true;

	return;
}

void SecondScene::Update()
{
	player->playerInput(input, Map);

	if (input->isKeyUp(VK_RETURN)) {
		Game *temp = new MainScenes;

		ChangeScene(temp);
	}

	//exitGame();
}

void SecondScene::render()
{
	graphics->spriteBegin();

	Map->getMapBG()->draw();
	objectManager->RenderAllObject();

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
