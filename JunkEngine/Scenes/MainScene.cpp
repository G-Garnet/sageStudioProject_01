#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	/*player = new Junk2DEntity;
	Ghost = new Junk2DEntity;
	BackGround = new Junk2DSprite;
	fontText = new Junk2DFont();*/

	map1 = new Junk2DMap();
	Window = new Junk2DSprite();
	Door = new Junk2DSprite();
}

MainScenes::~MainScenes()
{
	SAFE_DELETE(map1);
	objectManager->RemoveAllObject();
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

	map1->settingBGSprite(graphics, "..\\Resources\\ex.png");

	Window->settingTexture(graphics, "..\\Resources\\Window.png", 305,250, 1);
	Door->settingTexture(graphics, "..\\Resources\\Door.png", 220, 460, 1);

	Window->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2 - 300);
	Door->setXY((GAME_WIDTH / 2) - 600, GAME_HEIGHT / 2 - 300);

	objectManager->AddObject(map1->getMapBG(), "Map");
	objectManager->AddObject(Window, "Window");
	objectManager->AddObject(Door, "Door");

	map1->MapAddObject(Window, "Window");
	map1->MapAddObject(Door, "Door");

	initialized = true;

	return;
}

void MainScenes::Update()
{
	// if () 맵이 이동해야 할 경우
	if (input->isKeyDown(VK_RIGHT)) map1->mapMove(1, 0);
	if (input->isKeyDown(VK_LEFT))	map1->mapMove(-1, 0);
	if (input->isKeyDown(VK_DOWN))	map1->mapMove(0, 1);
	if (input->isKeyDown(VK_UP))	map1->mapMove(0, -1);
	//}

	//if () {
		// 캐릭터가 이동해야 할 경우
	//}

	VECTOR2 CollisionVector;
	//if (Ghost != NULL && player->collidesWith(Ghost, CollisionVector)){
	//	//objectManager->RemoveObject("Ghost");
	//	player->bounce(CollisionVector, *Ghost);
	//	audio->playCue("beep1");
	//	//Ghost = NULL;
	//}

	//player->update(0.1f);


	if (input->isKeyUp(VK_RETURN)) {
		Game *temp = new SecondScene;

		ChangeScene(temp);
	}

	if (input->isKeyDown(VK_ESCAPE)) {
		exitGame();
	}
}

void MainScenes::render()
{
	graphics->spriteBegin();

	objectManager->RenderAllObject();

	//fontText->print("Hello WORLD!", 100, 100);
	//fontText->print("ABCDEFGH", 100, 164);

	graphics->spriteEnd();
}

