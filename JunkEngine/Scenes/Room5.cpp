#include "Scenes.h"

Room5::Room5()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap();

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	font = new Junk2DFont();
	fade = new Fade();

	mop1 = new Monster();

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
	//Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room5\\Room5_bg.png");

	// Scene의 기본 요소들 //
	Map->MapDataInsert(graphics,"");
	Map->mapMove(0,0);

	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	font->initialize(graphics, 15, true, false, "굴림체");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	
	player->setXY(64*10,64*4);
	player->p_PosX = 10;
	player->p_PosY = 5;
	/////////////////////////

	mop1->MonseterSetting(graphics);
	mop1->setXY(64 * 4, 64 * 7);
	mop1->m_PosX = 4;
	mop1->m_PosY = 8;

	Map->mapMove(0, 0);
	mop1->setMap(Map);

	player->setMapszie(1);

	Map->MapAddObject(mop1,"mop1");

	initialized = true;

	//audio->playCue("door close");

	return;
}

void Room5::Update()
{
	player->playerInput(input, Map);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	if (fade->getalphaStart()) {
		player->setInputSW(false);
		fade->setAlpha(fade->getAlpha() + 0.8f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f) {
		player->setInputSW(false);
		fade->setAlpha(fade->getAlpha() - 1.5f);
	}
	else if (fade->getAlpha() <= 1.5f) {
		player->setInputSW(true);
	}

	mop1->update((float)1 / 60);
	mop1->findPlayer(player->p_PosX,player->p_PosY);

	/*if (input->isKeyUp(VK_RETURN)) {

		fade->setalphaStart(true);
	}*/

	//exitGame();
}

void Room5::render()
{
	graphics->spriteBegin();
	Map->getMapBG()->draw();

	for (int i = 0;i<=142;i++) {
		Map->Line1->draw();
		Map->Line1->setXY(Map->getMapBG()->getX() + i * 64,0);
	}
	for (int i = 0; i<=35; i++) {
		Map->Line2->draw();
		Map->Line2->setXY(0, Map->getMapBG()->getY() + i * 64);
	}

	player->draw();
	mop1->draw();

	itemSlot->ItemSlotRender();
	cursor->draw();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	graphics->spriteEnd();
}

