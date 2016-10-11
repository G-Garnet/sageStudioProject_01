#include "Scenes.h"

Room4::Room4()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	font = new Junk2DFont();

	Door1 = new Junk2DSprite();
	Door2 = new Junk2DSprite();
	Blood = new Junk2DSprite();
	Carpet = new Junk2DSprite();
	Pictures = new Junk2DSprite();
}

Room4::~Room4()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
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

	Blood->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\Room4_Blood.png", 352, 327, 1);
	Blood->setXY(838, 228);
	Carpet->settingTexture(graphics, "..\\Resources\\Floor1\\Room4\\Room4_Carpet.png", 1437, 170, 1);
	Carpet->setXY(360, 533);


	// Scene의 기본 요소들 //
	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	font->initialize(graphics, 15, true, false, "굴림체");
	/////////////////////////

	Map->mapMove(0, 0);

	// 태그 설정
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Door2, "Door2");
	objectManager->AddObject(Pictures, "Pictures");
	objectManager->AddObject(Blood, "Blood");
	objectManager->AddObject(Carpet, "Carpet");

	objectManager->AddObject(player, "Player");

	Map->MapAddObject(objectManager->getCGameObject("Door1"), "Door1");
	Map->MapAddObject(objectManager->getCGameObject("Door2"), "Door2");
	Map->MapAddObject(objectManager->getCGameObject("Blood"), "Blood");
	Map->MapAddObject(objectManager->getCGameObject("Carpet"), "Carpet");
	Map->MapAddObject(objectManager->getCGameObject("Pictures"), "Pictures");

	player->setMapszie(720);
	if (Player::p_PosScene == 3) {
		player->setX(370);
		player->setY(GAME_HEIGHT / 2 - 205);
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
	player->playerInput(input, Map);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	if (input->isKeyUp(VK_RETURN)) {
		Game *temp = new Room5;

		ChangeScene(temp);
	}

	//exitGame();
}

void Room4::render()
{
	graphics->spriteBegin();

	Map->getMapBG()->draw();
	objectManager->RenderAllObject();

	itemSlot->ItemSlotRender();
	cursor->draw();

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
