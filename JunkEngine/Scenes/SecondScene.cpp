#include "Scenes.h"

SecondScene::SecondScene()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
	
	Door1 = new Junk2DSprite();
	Door2 = new Junk2DSprite();
	Door3 = new Junk2DSprite();

	Window1 = new Junk2DSprite();
	Window2 = new Junk2DSprite();
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

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_LeftDoor.png", 163, 532, 1);
	Door1->setXY(64, 148);
	Door2->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_RightDoor.png", 163, 532, 1);
	Door2->setXY(1670, 148);
	Door3->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_Door.png", 398, 498, 1);
	Door3->setXY(750, 24);

	Window1->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_Window2.png", 356, 326, 1);
	Window1->setXY(350, 30);
	Window2->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_Window1.png", 365, 206, 1);
	Window2->setXY(1172, 48);

	player->playerSetting(graphics);

	Map->mapMove(0, 0);

	// 태그 설정
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Door2, "Door2");
	objectManager->AddObject(Door3, "Door3");
	objectManager->AddObject(Window1, "Window1");
	objectManager->AddObject(Window2, "Window2");
	objectManager->AddObject(player, "Player");

	Map->MapAddObject(objectManager->getCGameObject("Door1"), "Door1");
	Map->MapAddObject(objectManager->getCGameObject("Door2"), "Door2");
	Map->MapAddObject(objectManager->getCGameObject("Door3"), "Door3");
	Map->MapAddObject(objectManager->getCGameObject("Window1"), "Window1");
	Map->MapAddObject(objectManager->getCGameObject("Window2"), "Window2");

	player->setMapszie(618);

	initialized = true;

	return;
}

void SecondScene::Update()
{
	player->playerInput(input, Map);

	if (input->isKeyUp(VK_RETURN)) {
		Game *temp = new Room3;

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
