#include "Scenes.h"

Room3::Room3()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	font = new Junk2DFont();
	textWindow = new TextWindow();
	fade = new Fade();

	Door1 = new Junk2DSprite();
	Door2 = new Junk2DSprite();
	Candle1 = new Junk2DSprite();
	Candle2 = new Junk2DSprite();

	fireDeck = new Junk2DSprite();
	Box = new Junk2DSprite();
	Picture = new Junk2DSprite();
	Desk = new Junk2DSprite();
	Bear = new Junk2DSprite();

	filter = new Junk2DSprite();
	fire1 = new Junk2DSprite();
	fire2 = new Junk2DSprite();
}

Room3::~Room3()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
	SAFE_DELETE(fade);
	SAFE_DELETE(textWindow);
}

void Room3::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input��ü �ʱ�ȭ
	input->initialize(hwnd, false);
	// Ÿ�̸� ���
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	// �̹��� ������ �̸� ����
	Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room3\\Room3_bg.png");

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\Room3_LeftDoor.png", 163, 532, 1);
	Door1->setXY(85, 130);
	Door2->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\Room3_RightDoor.png", 220, 457, 1);
	Door2->setXY(1400, 70);

	Candle1->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\candle1.png", 35, 69, 1);
	Candle1->setXY(507, 160);
	Candle2->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\candle2.png", 35, 69, 1);
	Candle2->setXY(1296, 160);

	fireDeck->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\fire1.png", 469, 552, 1);
	fireDeck->setXY(680, 0);
	Box->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\box.png", 242, 250, 1);
	Box->setXY(348, 300);
	Picture->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\Picture.png", 223, 168, 1);
	Picture->setXY(810, 28);
	Desk->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\Desk.png", 169, 215, 1);
	Desk->setXY(1237, 333);

	Bear->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\Bear.png", 91, 101, 1);
	Bear->setXY(1264, 247);

	filter->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\3_roomd.png", 2000, 720, 1);
	filter->setXY(0, 0);

	fire1->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\fire.png", 10, 30, 5);
	fire1->setXY(507, 160);
	fire1->setLoop(true);
	fire1->setAnimation(0,8,0,0.4f);

	fire2->settingTexture(graphics, "..\\Resources\\Floor1\\Room3\\fire.png", 10, 30, 5);
	fire2->setXY(1296, 160);
	fire1->setLoop(true);
	fire2->setAnimation(0,8, 0, 0.4f);

	// Scene�� �⺻ ��ҵ� //
	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	textWindow->TextWindowSetting(graphics);
	textWindow->setActive(false);
	font->initialize(graphics, 15, true, false, "����ü");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	/////////////////////////

	Map->mapMove(0, 0);

	// �±� ����
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Door2, "Door2");
	objectManager->AddObject(Candle1, "Candle1");
	objectManager->AddObject(Candle2, "Candle2");
	objectManager->AddObject(fire1, "fire1");
	objectManager->AddObject(fire2, "fire2");
	objectManager->AddObject(fireDeck, "fireDeck");
	objectManager->AddObject(Box, "Box");
	objectManager->AddObject(Picture, "Picture");
	objectManager->AddObject(Desk, "Desk");
	objectManager->AddObject(Bear, "Bear");

	objectManager->AddObject(player, "Player");
	objectManager->AddObject(filter, "filter");

	Map->MapAddObject(objectManager->getCGameObject("Door1"), "Door1");
	Map->MapAddObject(objectManager->getCGameObject("Door2"), "Door2");
	Map->MapAddObject(objectManager->getCGameObject("Candle1"), "Candle1");
	Map->MapAddObject(objectManager->getCGameObject("Candle2"), "Candle2");
	Map->MapAddObject(objectManager->getCGameObject("fireDeck"), "fireDeck");
	Map->MapAddObject(objectManager->getCGameObject("fire1"), "fire1");
	Map->MapAddObject(objectManager->getCGameObject("fire2"), "fire2");
	Map->MapAddObject(objectManager->getCGameObject("Box"), "Box");
	Map->MapAddObject(objectManager->getCGameObject("Picture"), "Picture");
	Map->MapAddObject(objectManager->getCGameObject("Desk"), "Desk");
	Map->MapAddObject(objectManager->getCGameObject("Bear"), "Bear");
	Map->MapAddObject(objectManager->getCGameObject("filter"), "filter");

	Map->mapMove(-976+256, 0);
	player->setMapszie(976-256);

	if (Player::p_PosScene == 2) {
		player->setX(424+256);
		player->setY(156);
	}
	else if (Player::p_PosScene == 4) {
		player->setX(1080);
	}
	Player::p_PosScene = 3;

	initialized = true;

	audio->playCue("knock and rattle");

	return;
}

void Room3::Update()
{
	player->playerInput(input, Map);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	fire1->update((float)1 / 60);
	fire2->update((float)1 / 60);

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
		Game *temp = new Room4;

		ChangeScene(temp);
	}

	if (textWindow->getActive() &&
		(input->isKeyUp(VK_RETURN) || input->getMouseLButtonDown())) {

		switch (eventCount) {
		case 1:
			eventCount = 2;
			break; 
		case 2:
				eventCount = 3;
				break;
		default:
			textWindow->setActive(false);
			eventCount = 0;
			break;
		}

	}

	else if (!textWindow->getActive() && input->getMouseLButtonDown()) {
		// ��
		if (Bear != NULL) {
			if ((input->getMouseX() >= Bear->getX() && input->getMouseX() <= Bear->getX() + Bear->getWidth()) &&
				(input->getMouseY() >= Bear->getY() && input->getMouseY() <= Bear->getY() + Bear->getHeight())) {
				textWindow->setActive(true);
				eventCount = 1;
			}
		}

		// ����
		if ((input->getMouseX() >= Box->getX() && input->getMouseX() <= Box->getX() + Box->getWidth()) &&
			(input->getMouseY() >= Box->getY() && input->getMouseY() <= Box->getY() + Box->getHeight())) {
			textWindow->setActive(true);
			eventCount = 4;
		}

		// ������
		if ((input->getMouseX() >= fireDeck->getX() && input->getMouseX() <= fireDeck->getX() + fireDeck->getWidth()) &&
			(input->getMouseY() >= fireDeck->getY() && input->getMouseY() <= fireDeck->getY() + fireDeck->getHeight())) {
			textWindow->setActive(true);
			eventCount = 5;
		}
	}

	if (input->isKeyUp(VK_RETURN) && player->getX() <= 210 && player->getY() >= 160) {
		/*Game *temp = new Room4;

		ChangeScene(temp);*/
		fade->setalphaStart(true);
		audio->playCue("open_door_1");
	}


	if (input->isKeyUp(VK_RETURN) && player->getX() >= 640 && player->getY() <= 250) {
		/*Game *temp = new Room4;

		ChangeScene(temp);*/
		textWindow->setActive(true);
		eventCount = 6;
	}

	
	

	//exitGame();
}

void Room3::render()
{
	graphics->spriteBegin();

	Map->getMapBG()->draw();
	objectManager->RenderAllObject();

	itemSlot->ItemSlotRender();
	cursor->draw();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	switch (eventCount) {
	case 1:
		textWindow->TextWindowRender("���� �������̴�.\n����� �𸣰� ģ���� ������ ���.", 0);
		break;
	case 2:
		textWindow->TextWindowRender("\"�׷��� ���� �� �����ϳ�.\"", 0);
		break; 
	case 3:
		objectManager->RemoveObject("Bear");
		Map->RemoveObject("Bear");
		SAFE_DELETE(Bear);
		textWindow->TextWindowRender("�������� ȹ���ߴ�.", 0);
		player->playerItemIn(2);
		break;
	case 4:
		textWindow->TextWindowRender("...���� �Ÿ��� �� ����.\n�ǵ帮�� �ʴ°� ���� �� ����.", 0);
		break;
	case 5:
		textWindow->TextWindowRender("�����δ�.\n���� �鿩�ٺ��� ������ �ʴ�.", 0);
		break;
	case 6:
		textWindow->TextWindowRender("������ �ٽ� ���ư� ���ΰ� ���� �ʴ´�.", 0);
		break;
	}

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
