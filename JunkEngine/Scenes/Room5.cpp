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

	Door1 = new Junk2DSprite();
	cross1 = new Junk2DSprite();
	cross2 = new Junk2DSprite();
	light = new Junk2DSprite();
	videoPlayer = new Video();

	fire1 = new Junk2DSprite();
	fire2 = new Junk2DSprite();

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

	// Input��ü �ʱ�ȭ
	input->initialize(hwnd, false);
	// Ÿ�̸� ���
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	// �̹��� ������ �̸� ����
	//Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room5\\Room5_bg.png");

	// Scene�� �⺻ ��ҵ� //
	Map->MapDataInsert(graphics,"");
	Map->mapMove(1280/2 ,720/2 - 2100 + 64);

	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	font->initialize(graphics, 15, true, false, "����ü");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	/////////////////////////

	Map->mapMove(0, 0);

	player->setMapszie(1);

	initialized = true;

	//audio->playCue("door close");

	return;
}

void Room5::Update()
{
	player->playerInput(input, Map);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	fire1->update((float)1 / 60);
	fire2->update((float)1 / 60);

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


	/*if (input->isKeyUp(VK_RETURN)) {

		fade->setalphaStart(true);
	}*/

	//exitGame();
}

void Room5::render()
{
	graphics->spriteBegin();

	Map->getMapBG()->draw();
	player->draw();

	itemSlot->ItemSlotRender();
	cursor->draw();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	graphics->spriteEnd();
}

