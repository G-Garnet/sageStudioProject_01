#include "Scenes.h"

SecondScene::SecondScene()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	fade = new Fade();
	font = new Junk2DFont();
	
	Door1 = new Junk2DSprite();
	Door2 = new Junk2DSprite();
	Door3 = new Junk2DSprite();

	Window1 = new Junk2DSprite();
	Window2 = new Junk2DSprite();


	filter = new Junk2DSprite();
}

SecondScene::~SecondScene()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
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

	filter->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\2_roomd.png", 1900, 720, 1);
	filter->setXY(0, 0);

	// Scene의 기본 요소들 //
	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	font->initialize(graphics, 15, true, false, "굴림체");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	/////////////////////////

	Map->mapMove(0, 0);

	// 태그 설정
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Door2, "Door2");
	objectManager->AddObject(Door3, "Door3");
	objectManager->AddObject(Window1, "Window1");
	objectManager->AddObject(Window2, "Window2");
	objectManager->AddObject(player, "Player");
	objectManager->AddObject(filter, "filter");

	Map->MapAddObject(objectManager->getCGameObject("Door1"), "Door1");
	Map->MapAddObject(objectManager->getCGameObject("Door2"), "Door2");
	Map->MapAddObject(objectManager->getCGameObject("Door3"), "Door3");
	Map->MapAddObject(objectManager->getCGameObject("Window1"), "Window1");
	Map->MapAddObject(objectManager->getCGameObject("Window2"), "Window2");
	Map->MapAddObject(objectManager->getCGameObject("filter"), "filter");

	player->setMapszie(618);
	if (Player::p_PosScene == 1) {
		player->setX(114);
	}
	else if (Player::p_PosScene == 3) {
		player->setX(1080);
	}
	Player::p_PosScene = 2;

	//Map->mapMove(300, 0);

	initialized = true;
	//player->setXY(64, 150);

	return;
}

void SecondScene::Update()
{
	player->playerInput(input, Map);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	if (fade->getalphaStart()) {
		fade->setAlpha(fade->getAlpha() + 1.75f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f) {
		fade->setAlpha(fade->getAlpha() - 1.75f);
	}
	else if (fade->getAlpha() <= 1.5f) {
		player->setInputSW(true);
	}

	if (fade->getAlpha() >= 255) {
		Game *temp = new SecondScene;

		ChangeScene(temp);
	}

	if (input->isKeyUp(VK_RETURN)) {
		/*Game *temp = new Room3;

		ChangeScene(temp);*/
		fade->setalphaStart(true);
	}

	//exitGame();
}

void SecondScene::render()
{
	graphics->spriteBegin();

	Map->getMapBG()->draw();
	objectManager->RenderAllObject();

	itemSlot->ItemSlotRender();
	cursor->draw();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

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
