#include "Scenes.h"

Room4::Room4()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	font = new Junk2DFont();
	fade = new Fade();
	textWindow = new TextWindow();

	Door1 = new Junk2DSprite();
	Door2 = new Junk2DSprite();
	Blood = new Junk2DSprite();
	Carpet = new Junk2DSprite();
	Pictures = new Junk2DSprite();

	filter = new Junk2DSprite();
}

Room4::~Room4()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
	SAFE_DELETE(fade);
	SAFE_DELETE(textWindow);
}

void Room4::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	// 이미지 정보름 미리 선언
	Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room4\\Room4_bg.png");

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\Room4_LeftDoor.png", 220, 457, 1);
	Door1->setXY(370, 68);
	Door2->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\Room4_RightDoor.png", 220, 457, 1);
	Door2->setXY(1495, 68);

	Pictures->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\Room4_Pictures.png", 668, 269, 1);
	Pictures->setXY(700, 48);

	Blood->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\Room4_Blood.png", 650, 480, 7);
	Blood->setLoop(false);
	Blood->setAnimation(0, 27, 0, 0.1f);
	Blood->setXY(731, 91);

	Carpet->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\Room4_Carpet.png", 1437, 170, 1);
	Carpet->setXY(360, 533);

	filter->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\4_roomd.png", 2100, 720, 1);
	filter->setXY(0, 0);

	// Scene의 기본 요소들 //
	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	textWindow->TextWindowSetting(graphics);
	textWindow->setActive(false);
	font->initialize(graphics, 15, true, false, "굴림체"); 
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	/////////////////////////

	Map->mapMove(0, 0);

	// 태그 설정
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Door2, "Door2");
	objectManager->AddObject(Pictures, "Pictures");
	objectManager->AddObject(Blood, "Blood");
	objectManager->AddObject(Carpet, "Carpet");

	objectManager->AddObject(player, "Player");
	objectManager->AddObject(filter, "filter");

	Map->MapAddObject(objectManager->getCGameObject("Door1"), "Door1");
	Map->MapAddObject(objectManager->getCGameObject("Door2"), "Door2");
	Map->MapAddObject(objectManager->getCGameObject("Blood"), "Blood");
	Map->MapAddObject(objectManager->getCGameObject("Carpet"), "Carpet");
	Map->MapAddObject(objectManager->getCGameObject("Pictures"), "Pictures");
	Map->MapAddObject(objectManager->getCGameObject("filter"), "filter");

	player->setMapszie(1076-256);

	Map->mapMove(-1076+256, 0);

	if (Player::p_PosScene == 3) {
		player->setX(495);
		player->setY(156);
	}
	else if (Player::p_PosScene == 5) {
		player->setX(1080);
	}
	Player::p_PosScene = 4;

	initialized = true;

	return;
}

void Room4::Update()
{
	if (!textWindow->getActive()) {
		player->playerInput(input, Map);
	}
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
		Game *temp = new Room5;

		ChangeScene(temp);
	}

	if (eventCount == 2 && eventStart) {
		Sleep(1500);
		eventCount = 3;
	}

	if (textWindow->getActive() && (input->isKeyUp(VK_RETURN) || input->getMouseLButtonDown())) {

		switch (eventCount) {
		case 1:
			eventCount = 2;
			textWindow->setActive(false);
			eventStart = true;
			break;
		default:
			textWindow->setActive(false);
			eventCount = 0;
			break;
		}
	}

	

	if (player->getX() >= 630 && Map->getMapX() >= -480 && !eventStart) {
		eventCount = 1;
		textWindow->setActive(true);
	}

	if (input->isKeyUp(VK_RETURN)) {
		fade->setalphaStart(true);
	}


	//exitGame();
}

void Room4::render()
{
	graphics->spriteBegin();

	Map->getMapBG()->draw();
	objectManager->RenderAllObject();

	switch (eventCount) {
	case 1:
		// 컷신 드로우
		textWindow->TextWindowRender("기분 나쁘게 생긴 그림들 사이로", 0);
		break;
	case 2:
		break;
	case 3:
		Blood->update(1.0f / 60.0f);
		break;
	}

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
