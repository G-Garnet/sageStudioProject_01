#include "Scenes.h"

extern int p_PosScene;

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	font = new Junk2DFont();
	fade = new Fade();

	Map1 = new Junk2DMap();

	Door1 = new Junk2DSprite();
	Desk = new Junk2DEntity();
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
	SAFE_DELETE(font);
	SAFE_DELETE(fade);
}

void MainScenes::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);
	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	QueryPerformanceCounter(&timeStart);        // 시작 시간 가져오기

	// 텍스트 초기화
	// fontText->settingFontTexture(graphics, "..\\Resources\\m-water001.png");

	// 이미지 정보름 미리 선언
	Map1->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room1_bg.png");

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\room1_door.png", 220, 457, 1);
	Door1->setXY(370, 68);

	Desk->initialize(graphics, "..\\Resources\\Floor1\\room1_desk.png", 465, 312, 1);
	Desk->setXY(1180, 244);
	Desk->setActive(true);
	Desk->setCollisionType(Junk2DentityNS::BOX);
	Desk->setEdge(0,0,465,128);

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

	// Scene의 기본 요소들 //
	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	font->initialize(graphics, 15, true, false, "굴림체");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	/////////////////////////

	//player->setXY(720,300);
	//player->setFrameDelay(0.1f);

	// 태그 설정
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Desk, "Desk");
	objectManager->AddObject(Hanger, "Hanger");
	objectManager->AddObject(Carpet, "Carpet");
	objectManager->AddObject(Pipe, "Pipe");
	objectManager->AddObject(player, "player");
	objectManager->AddObject(filter, "filter");

	Map1->MapAddObject(objectManager->getCGameObject("Door1"),"Door1");
	Map1->MapAddObject(objectManager->getCGameObject("Desk"), "Desk");
	Map1->MapAddObject(objectManager->getCGameObject("Hanger"), "Hanger");
	Map1->MapAddObject(objectManager->getCGameObject("Carpet"), "Carpet");
	Map1->MapAddObject(objectManager->getCGameObject("Pipe"), "Pipe");
	Map1->MapAddObject(objectManager->getCGameObject("filter"), "filter");

	Map1->mapMove(0, 0);

	player->setMapszie(1120);

	if (Player::p_PosScene == 5) {
		player->setX(114);
	}
	Player::p_PosScene = 1;

	initialized = true;

	return;
}

void MainScenes::Update()
{ 
	player->playerInput(input, Map1);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	if (player->collidesWith(Carpet, CollisionVector) && 
		input->isKeyUp(VK_RETURN)) {
		//player->bounce(CollisionVector, *Desk);
		
		fade->setalphaStart(true);
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

	if (player->collidesWith(Desk, CollisionVector)){
		player->bounce(CollisionVector, *Desk);
	}
	/*if (player->collidesWith(Hanger, CollisionVector)) {
		player->bounce(CollisionVector, *Hanger);
	}*/
}

void MainScenes::render()
{
	graphics->spriteBegin();

	Map1->getMapBG()->draw();
	objectManager->RenderAllObject();
	itemSlot->ItemSlotRender();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	cursor->draw();

	//font->print("츄라이 츄라이", 100, 100);
	//font->print("ABCDEFGH", 100, 116);

	graphics->spriteEnd();
}

