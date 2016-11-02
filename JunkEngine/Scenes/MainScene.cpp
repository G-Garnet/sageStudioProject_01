#include "Scenes.h"

extern int p_PosScene;

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	textWindow = new TextWindow();
	fade = new Fade();

	Map1 = new Junk2DMap();

	Door1 = new Junk2DSprite();
	Desk = new Junk2DEntity();

	bottle = new Junk2DEntity();
	candle = new Junk2DEntity();
	papers = new Junk2DEntity();

	Hanger = new Junk2DEntity();
	Carpet = new Junk2DEntity();
	Pipe = new Junk2DSprite();

	filter = new Junk2DSprite();
}

MainScenes::~MainScenes()
{
	//SAFE_DELETE(map1);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(textWindow);
	SAFE_DELETE(fade);
}

void MainScenes::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);
	// Input��ü �ʱ�ȭ
	input->initialize(hwnd, false);
	// Ÿ�̸� ���
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	QueryPerformanceCounter(&timeStart);        // ���� �ð� ��������

	// �ؽ�Ʈ �ʱ�ȭ
	// fontText->settingFontTexture(graphics, "..\\Resources\\m-water001.png");

	// �̹��� ������ �̸� ����
	Map1->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room1_bg.png");

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\room1_door.png", 220, 457, 1);
	Door1->setXY(370, 68);

	Desk->initialize(graphics, "..\\Resources\\Floor1\\room1_desk.png", 463, 202, 1);
	Desk->setXY(1019, 352);
	Desk->setActive(true);
	Desk->setCollisionType(Junk2DentityNS::BOX);
	Desk->setEdge(0,0,463,163);

	bottle->settingTexture(graphics, "..\\Resources\\Floor1\\bottle.png", 34, 77, 1);
	bottle->setXY(1192, 292);
	candle->settingTexture(graphics, "..\\Resources\\Floor1\\candle.png", 83, 128, 1);
	candle->setXY(1102, 242);
	papers->settingTexture(graphics, "..\\Resources\\Floor1\\papers.png", 156, 51, 1);
	papers->setXY(1296, 318);

	Pipe->settingTexture(graphics, "..\\Resources\\Floor1\\room1_pipe.png", 297, 392, 1);
	Pipe->setXY(2104, 314);
	Pipe->settingTexture(graphics, "..\\Resources\\Floor1\\room1_pipe.png", 297, 392, 1);
	Pipe->setXY(2104, 314);
	Pipe->settingTexture(graphics, "..\\Resources\\Floor1\\room1_pipe.png", 297, 392, 1);
	Pipe->setXY(2104, 314);

	Hanger->settingTexture(graphics, "..\\Resources\\Floor1\\room1_.png", 155, 462, 1);
	Hanger->setXY(600, 100);

	Carpet->settingTexture(graphics, "..\\Resources\\Floor1\\room1_carpet.png", 315, 71, 1);
	Carpet->setXY(282, 526);
	Carpet->setActive(true);
	Carpet->setCollisionType(Junk2DentityNS::BOX);
	Carpet->setEdge(0, 0, 315, 71);
	//Carpet->setTrigger(true);

	Pipe->settingTexture(graphics, "..\\Resources\\Floor1\\room1_pipe.png", 297, 392, 1);
	Pipe->setXY(2104, 314);

	filter->settingTexture(graphics, "..\\Resources\\Floor1\\1_roomd.png", 2400, 720, 1);
	filter->setXY(0, 0);

	// Scene�� �⺻ ��ҵ� //
	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	textWindow->TextWindowSetting(graphics);
	textWindow->setActive(false);
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	/////////////////////////

	//player->setXY(720,300);
	//player->setFrameDelay(0.1f);

	// �±� ����
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Desk, "Desk");
	objectManager->AddObject(bottle, "bottle");
	objectManager->AddObject(candle, "candle");
	objectManager->AddObject(papers, "papers");
	objectManager->AddObject(Hanger, "Hanger");
	objectManager->AddObject(Carpet, "Carpet");
	objectManager->AddObject(Pipe, "Pipe");
	objectManager->AddObject(player, "player");
	objectManager->AddObject(filter, "filter");

	Map1->MapAddObject(objectManager->getCGameObject("Door1"),"Door1");
	Map1->MapAddObject(objectManager->getCGameObject("Desk"), "Desk");
	Map1->MapAddObject(objectManager->getCGameObject("bottle"), "bottle");
	Map1->MapAddObject(objectManager->getCGameObject("candle"), "candle");
	Map1->MapAddObject(objectManager->getCGameObject("papers"), "papers");
	Map1->MapAddObject(objectManager->getCGameObject("Hanger"), "Hanger");
	Map1->MapAddObject(objectManager->getCGameObject("Carpet"), "Carpet");
	Map1->MapAddObject(objectManager->getCGameObject("Pipe"), "Pipe");
	Map1->MapAddObject(objectManager->getCGameObject("filter"), "filter");

	Map1->mapMove(-1200+256, 0);

	player->setMapszie(1376-256);

	if (Player::p_PosScene == 5) {
		player->setX(114);
	}
	Player::p_PosScene = 1;

	initialized = true;

	audio->playCue("rain bgm");

	return;
}

void MainScenes::Update()
{ 
	// �ؽ�Ʈ �����찡 �����ȵ����� ��Ȱ��ȭ //

	if(!textWindow->getActive()) {
		player->playerInput(input, Map1);
	}
	itemSlot->ItemSlotInput(input);
	textWindow->TextWindowInput(input);
	cursor->CursorInput(input);

	// Ŭ�� �̺�Ʈ //
	if (eventCount == 6) {
		if (input->isKeyUp(VK_UP)) {
			textWindow->setSelect(1);
		}

		else if (input->isKeyUp(VK_DOWN)) {
			textWindow->setSelect(2);
		}
	}

	if (textWindow->getActive() &&
		(input->isKeyUp(VK_RETURN) || input->getMouseLButtonDown())) {

		switch (eventCount) {
		case -1:
			textWindow->resetStrLength();
			eventCount = -2;
			break;
		case 6:
			if (textWindow->getSelect() == 1) {
				textWindow->resetStrLength();
				eventCount = 7;
			}
			else {
				textWindow->setActive(false);
				textWindow->resetStrLength();
				eventCount = 0;
			}
			break;
		default:
			textWindow->setActive(false);
			textWindow->resetStrLength();
			eventCount = 0;
			break;
		}

	}

	else if (!textWindow->getActive() && input->getMouseLButtonDown()) {
		// ����
		if ((input->getMouseX() >= papers->getX() && input->getMouseX() <= papers->getX() + papers->getWidth()) &&
			(input->getMouseY() >= papers->getY() && input->getMouseY() <= papers->getY() + papers->getHeight())) {
			textWindow->setActive(true);
			textWindow->resetStrLength();
			eventCount = -1;
		}

		// ������
		if ((input->getMouseX() >= Desk->getX() && input->getMouseX() <= Desk->getX() + Desk->getWidth()) &&
			(input->getMouseY() >= Desk->getY() && input->getMouseY() <= Desk->getY() + Desk->getHeight())) {
			textWindow->setActive(true);
			textWindow->resetStrLength();
			eventCount = 4;
		}

		// ī��
		if (!key &&
			(input->getMouseX() >= Carpet->getX() && input->getMouseX() <= Carpet->getX() + Carpet->getWidth()) &&
			(input->getMouseY() >= Carpet->getY() && input->getMouseY() <= Carpet->getY() + Carpet->getHeight())) {
			textWindow->setActive(true);
			textWindow->resetStrLength();
			eventCount = 6;
		}

		// ������
		if ((input->getMouseX() >= Pipe->getX() && input->getMouseX() <= Pipe->getX() + Pipe->getWidth()) &&
			(input->getMouseY() >= Pipe->getY() && input->getMouseY() <= Pipe->getY() + Pipe->getHeight())) {
			textWindow->setActive(true);
			textWindow->resetStrLength();
			eventCount = 3;
		}

		// �д�
		if ((input->getMouseX() >= candle->getX() && input->getMouseX() <= candle->getX() + candle->getWidth()) &&
			(input->getMouseY() >= candle->getY() && input->getMouseY() <= candle->getY() + candle->getHeight())) {
			textWindow->setActive(true);
			textWindow->resetStrLength();
			eventCount = 0;
		}

		// ��
		if ((input->getMouseX() >= bottle->getX() && input->getMouseX() <= bottle->getX() + bottle->getWidth()) &&
			(input->getMouseY() >= bottle->getY() && input->getMouseY() <= bottle->getY() + bottle->getHeight())) {
			textWindow->setActive(true);
			textWindow->resetStrLength();
			eventCount = 0;
		}

		// �ʰ���
		if ((input->getMouseX() >= Hanger->getX() && input->getMouseX() <= Hanger->getX() + Hanger->getWidth()) &&
			(input->getMouseY() >= Hanger->getY() && input->getMouseY() <= Hanger->getY() + Hanger->getHeight())) {
			textWindow->setActive(true);
			textWindow->resetStrLength();
			eventCount = 2;
		}
	}

	else if (!textWindow->getActive()) {

		bool sw = false;
		// ����
		if ((input->getMouseX() >= papers->getX() && input->getMouseX() <= papers->getX() + papers->getWidth()) &&
			(input->getMouseY() >= papers->getY() && input->getMouseY() <= papers->getY() + papers->getHeight())) {
			sw = true;
		}

		// ������
		if ((input->getMouseX() >= Desk->getX() && input->getMouseX() <= Desk->getX() + Desk->getWidth()) &&
			(input->getMouseY() >= Desk->getY() && input->getMouseY() <= Desk->getY() + Desk->getHeight())) {
			sw = true;
		}

		// ī��
		if (!key &&
			(input->getMouseX() >= Carpet->getX() && input->getMouseX() <= Carpet->getX() + Carpet->getWidth()) &&
			(input->getMouseY() >= Carpet->getY() && input->getMouseY() <= Carpet->getY() + Carpet->getHeight())) {
			sw = true;
		}

		// ������
		if ((input->getMouseX() >= Pipe->getX() && input->getMouseX() <= Pipe->getX() + Pipe->getWidth()) &&
			(input->getMouseY() >= Pipe->getY() && input->getMouseY() <= Pipe->getY() + Pipe->getHeight())) {
			sw = true;
		}

		// �д�
		if ((input->getMouseX() >= candle->getX() && input->getMouseX() <= candle->getX() + candle->getWidth()) &&
			(input->getMouseY() >= candle->getY() && input->getMouseY() <= candle->getY() + candle->getHeight())) {
			sw = true;
		}

		// ��
		if ((input->getMouseX() >= bottle->getX() && input->getMouseX() <= bottle->getX() + bottle->getWidth()) &&
			(input->getMouseY() >= bottle->getY() && input->getMouseY() <= bottle->getY() + bottle->getHeight())) {
			sw = true;
		}

		// �ʰ���
		if ((input->getMouseX() >= Hanger->getX() && input->getMouseX() <= Hanger->getX() + Hanger->getWidth()) &&
			(input->getMouseY() >= Hanger->getY() && input->getMouseY() <= Hanger->getY() + Hanger->getHeight())) {
			sw = true;
		}

		if (sw) {
			cursor->Cursorchange(true);
		}
		else {
			cursor->Cursorchange(false);
		}
	}
	////////////////

	// Fade & SceneChange //
	if (player->collidesWith(Carpet, CollisionVector)){
		if (input->isKeyUp(VK_RETURN)) {
			if (key) {
				audio->playCue("open_door_1");
				fade->setalphaStart(true);
			}
			else if (textWindow->getActive()) {
				textWindow->setActive(false);
			}
			else {
				textWindow->setActive(true);
				textWindow->resetStrLength();
				eventCount = 5;
				blockDoor = false;
			}
		}
		
	}

	if (fade->getalphaStart()) {
		fade->setAlpha(fade->getAlpha() + 1.75f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f){
		fade->setAlpha(fade->getAlpha() - 1.75f);
	}
	else if (fade->getAlpha() <= 1.5f) {
		player->setInputSW(true);
	}

	if (fade->getAlpha() >= 255) {
		Game *temp = new SecondScene;

		ChangeScene(temp);
	}


}

void MainScenes::render()
{
	graphics->spriteBegin();

	Map1->getMapBG()->draw();
	objectManager->RenderAllObject();

	switch (eventCount) {
	case -2:
		textWindow->MiddleTextWindowRender("���� �ܿ��� ���̰� ���Ƽ� �˾ƺ� �� ����.", 0);
		break;
	case -1 :
		textWindow->MiddleTextWindowRender((std::string)"�̰��� ó�� ���� ���� �� �ͼ��� ��� �츮�� �׵��� ���Դ�. \n"
			 + (std::string)"�׷����� �׵��� ������ ���ݾ� �̻������� �ִ�.\n" + (std::string)"�����뿡 �ö� �츮���� ���� �ٷ� �� �����̴�.",0);
		break;
	case 0 :
		textWindow->TextWindowRender("���̽�� ��ĥ�� ������ ����.", 0);
		break;
	case 1:
		textWindow->TextWindowRender("�������� ��� ����ִ�.", 0);
		break;
	case 2:
		textWindow->TextWindowRender("�ɷ��ִ� �͵��� ��� ��Ƽ� ���¸� �˾ƺ� �� ����.", 0);
		break;
	case 3:
		textWindow->TextWindowRender("������ ���� ������ �Ҹ��� ����.", 0);
		break;
	case 4:
		textWindow->TextWindowRender("�������� ��� ����ִ�.", 0);
		break;
	case 5:
		if (!blockDoor){
			audio->playCue("rattle twice");
			blockDoor = true;
		}
		textWindow->TextWindowRender("������ �ʴ´�.", 0);
		break;
	case 6:
		textWindow->TextWindowRender("�ö� �� ���� �������� ���� ������ ������ ����.", 0);
		textWindow->SelectTextWindowRender(2,"���纻��.","���ư���.");
		break;
	case 7:
		textWindow->TextWindowRender("���踦 ã�Ҵ�.", 0);
		if (!key) {
			audio->playCue("item");
		}
		key = true;
		break;

	}

	itemSlot->ItemSlotRender();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	cursor->draw();

	//font->print("����� �����", 100, 100);
	//font->print("ABCDEFGH", 100, 116);

	graphics->spriteEnd();
}

