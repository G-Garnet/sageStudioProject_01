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

	// �±� ����
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

	// ������ ���� Ŭ���� ȣ��
	// ����, �׽�Ʈ �� �÷��̾� Ŭ�������� ȣ���ϵ��� �̵�
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

