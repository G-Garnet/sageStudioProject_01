#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	map1 = new Junk2DMap;

	Window = new Junk2DSprite;
	Door = new Junk2DSprite;

	/*player = new Junk2DEntity;
	Ghost = new Junk2DEntity;
	BackGround = new Junk2DSprite;
	fontText = new Junk2DFont();*/
}

MainScenes::~MainScenes()
{
	
}

void MainScenes::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	//// 텍스트 초기화
	//fontText->settingFontTexture(graphics, "..\\Resources\\m-water001.png");
	//fontText->setProportional(false);
	//fontText->setFontColor(graphicsNS::GRAY);
	//fontText->setBackColor(TRANSCOLOR);
	//fontText->setFontHeight(16 * 2);

	//// 이미지 정보름 미리 선언
	//BackGround->settingTexture(graphics, "..\\Resources\\orion.png", 1280, 720, 1);
	//BackGround->setXY(0, 0);

	//Ghost->initialize(graphics, "..\\Resources\\m-water001.png", 264, 264, 1);
	//Ghost->setCollisionType(Junk2DentityNS::BOX);
	//Ghost->setActive(true);
	//Ghost->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);

	//player->initialize(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	//player->setXY(0 , GAME_HEIGHT / 6);
	//player->setLoop(true);
	//player->setActive(true);
	//player->setCollisionType(Junk2DentityNS::BOX);
	//player->setAnimation(0, 3, 0, 3.0f);
	////player->setFrameDelay(0.1f);

	//// 태그 설정
	//objectManager->AddObject(BackGround, "BackGround");
	//objectManager->AddObject(Ghost, "Ghost");
	//objectManager->AddObject(player, "player");

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

	return;
}

void MainScenes::Update()
{
	// if () 맵이 이동해야 할 경우
	if (input->isKeyDown(VK_RIGHT)) map1->setMapPos(2, 0);
	if (input->isKeyDown(VK_LEFT))	map1->setMapPos(-2, 0);
	if (input->isKeyDown(VK_DOWN))	map1->setMapPos(0, 2);
	if (input->isKeyDown(VK_UP))	map1->setMapPos(0, -2);
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

