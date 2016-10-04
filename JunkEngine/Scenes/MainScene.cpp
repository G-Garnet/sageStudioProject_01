#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Player();
	itemSlot = new ItemSlot();

	Map1 = new Junk2DMap();

	Door1 = new Junk2DSprite();
	Desk = new Junk2DEntity();
	Hanger = new Junk2DEntity();
	Carpet = new Junk2DEntity();
	Pipe = new Junk2DSprite();

	Cursor = new Junk2DSprite();
}

MainScenes::~MainScenes()
{
	//SAFE_DELETE(map1);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(Cursor);
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

	Cursor->settingTexture(graphics, "..\\Resources\\Etc\\cursor.png", 420, 420, 1);
	Cursor->setXY(input->getMouseX(), input->getMouseY());

	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	//player->setXY(720,300);
	//player->setFrameDelay(0.1f);

	// 태그 설정
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Desk, "Desk");
	objectManager->AddObject(Hanger, "Hanger");
	objectManager->AddObject(Carpet, "Carpet");
	objectManager->AddObject(Pipe, "Pipe");
	objectManager->AddObject(player, "player");

	Map1->MapAddObject(objectManager->getCGameObject("Door1"),"Door1");
	Map1->MapAddObject(objectManager->getCGameObject("Desk"), "Desk");
	Map1->MapAddObject(objectManager->getCGameObject("Hanger"), "Hanger");
	Map1->MapAddObject(objectManager->getCGameObject("Carpet"), "Carpet");
	Map1->MapAddObject(objectManager->getCGameObject("Pipe"), "Pipe");

	Map1->mapMove(0, 0);

	player->setMapszie(1120);

	initialized = true;

	return;
}

void MainScenes::Update()
{ 
	player->playerInput(input, Map1);
	itemSlot->ItemSlotInput(input);


	if (player->collidesWith(Carpet, CollisionVector) && 
		input->isKeyUp(VK_RETURN)) {


		//player->bounce(CollisionVector, *Desk);
		Game *temp = new SecondScene;

		ChangeScene(temp);
	}

	if (player->collidesWith(Desk, CollisionVector)){
		player->bounce(CollisionVector, *Desk);
	}
	
	Cursor->setXY(input->getMouseX(), input->getMouseY());

	// 아이템 슬롯 클래스 호출
	// 제작, 테스트 후 플레이어 클래스에서 호출하도록 이동
	if (input->isKeyUp(1)) {
	}
}

void MainScenes::render()
{
	graphics->spriteBegin();

	Map1->getMapBG()->draw();
	objectManager->RenderAllObject();
	itemSlot->ItemSlotRender();

	Cursor->draw();

	//fontText->print("Hello WORLD!", 100, 100);
	//fontText->print("ABCDEFGH", 100, 164);

	graphics->spriteEnd();
}

