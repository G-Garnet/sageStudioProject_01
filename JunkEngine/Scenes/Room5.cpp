#include "Scenes.h"

Room5::Room5()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	font = new Junk2DFont();
	fade = new Fade();

	Door1 = new Junk2DSprite();
	cross1 = new Junk2DSprite();
	cross2 = new Junk2DSprite();
	light = new Junk2DSprite();
	videoPlayer = new Video();

	filter = new Junk2DSprite();
}

Room5::~Room5()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
	SAFE_DELETE(fade);
	SAFE_DELETE(videoPlayer);
}

void Room5::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	// 이미지 정보름 미리 선언
	Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room5\\Room5_bg.png");

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\Room5\\Room5_Door.png", 183, 379, 1);
	Door1->setXY(545, 144);

	cross1->settingTexture(graphics, "..\\Resources\\Floor1\\Room5\\Room5_CrossLeft.png", 173, 350, 1);
	cross1->setXY(47, 88);

	cross2->settingTexture(graphics, "..\\Resources\\Floor1\\Room5\\Room5_CrossRight.png", 173, 350, 1);
	cross2->setXY(1064, 88);

	light->settingTexture(graphics, "..\\Resources\\Floor1\\Room5\\Room5_light.png", 456, 86, 1);
	light->setXY(410, 88);

	filter->settingTexture(graphics, "..\\Resources\\Floor1\\Room5\\5_roomd.png", 2000, 720, 1);
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
	objectManager->AddObject(cross1, "cross1");
	objectManager->AddObject(cross2, "cross2");
	objectManager->AddObject(light, "light");

	objectManager->AddObject(player, "Player");
	objectManager->AddObject(filter, "filter");

	Map->MapAddObject(objectManager->getCGameObject("Door1"), "Door1");
	Map->MapAddObject(objectManager->getCGameObject("cross1"), "cross1");
	Map->MapAddObject(objectManager->getCGameObject("cross2"), "cross2");
	Map->MapAddObject(objectManager->getCGameObject("light"), "light");
	Map->MapAddObject(objectManager->getCGameObject("filter"), "filter");

	player->setMapszie(1);

	initialized = true;

	return;
}

void Room5::Update()
{
	player->playerInput(input, Map);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	if (fade->getalphaStart()) {
		fade->setAlpha(fade->getAlpha() + 1.05f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f) {
		player->setInputSW(false);
		fade->setAlpha(fade->getAlpha() - 1.05f);
	}
	else if (fade->getAlpha() <= 1.5f) {
		player->setInputSW(true);
	}

	if (fade->getAlpha() >= 255 && !ending) {
		ending = true;
		videoPlayer->play(hwnd, L"..\\Resources\\Video\\openinng1.avi");
		exit(0);
	}


	if (input->isKeyUp(VK_RETURN)) {

		fade->setalphaStart(true);
	}

	//exitGame();
}

void Room5::render()
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
