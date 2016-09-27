#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Junk2DEntity;

	Map1 = new Junk2DMap();

	Door1 = new Junk2DSprite();
	Desk = new Junk2DSprite();
	Hanger = new Junk2DSprite();
	Carpet = new Junk2DSprite();
	Pipe = new Junk2DSprite();
}

MainScenes::~MainScenes()
{
	//SAFE_DELETE(map1);
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

	// 텍스트 초기화
	// fontText->settingFontTexture(graphics, "..\\Resources\\m-water001.png");

	// 이미지 정보름 미리 선언
	Map1->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room1_bg.png");

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\room1_door.png", 220, 457, 1);
	Door1->setXY(370, 68);
	Desk->settingTexture(graphics, "..\\Resources\\Floor1\\room1_desk.png", 465, 312, 1);
	Desk->setXY(1180, 244);
	Hanger->settingTexture(graphics, "..\\Resources\\Floor1\\room1_.png", 155, 462, 1);
	Hanger->setXY(600, 100);
	Carpet->settingTexture(graphics, "..\\Resources\\Floor1\\room1_carpet.png", 315, 71, 1);
	Carpet->setXY(282, 526);
	Pipe->settingTexture(graphics, "..\\Resources\\Floor1\\room1_pipe.png", 297, 392, 1);
	Pipe->setXY(2104, 314);

	player->initialize(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	player->setXY(GAME_WIDTH/ 2, GAME_HEIGHT / 2);
	//player->set
	player->setLoop(true);
	player->setActive(true);
	player->setCollisionType(Junk2DentityNS::BOX);
	player->setAnimation(0, 3, 0, 3.0f);
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

	playerSize = player->getSpriteDataRect().right;

	initialized = true;

	return;
}

void MainScenes::Update()
{ 
	// 플레이어 이동 클래스
	// 전부 플레이어 클래스로 만들어서 객체화 시켜서 이동할 예정
	if (input->isKeyDown(VK_DOWN)) {
		player->setY(player->getY() + Movespeed/2);
		if (player->getY() >= GAME_HEIGHT - 200) {
			player->setY(player->getY() - Movespeed/2);
		}
	}
	if (input->isKeyDown(VK_UP)) {
		player->setY(player->getY() - Movespeed/2);
		if (player->getY() <= GAME_HEIGHT / 2 - 24) {
			player->setY(player->getY() + Movespeed/2);
		}

		if (player->getX() - Movespeed <
			0 + (GAME_HEIGHT - player->getY() * 1.5f)) {
			player->setX(0 + (GAME_HEIGHT - player->getY() * 1.5f));
		}

		else if (player->getX() + playerSize + Movespeed >
				(GAME_WIDTH - playerSize) - (GAME_HEIGHT - player->getY() * 1.5f)) {
			player->setX((GAME_WIDTH - playerSize) - (GAME_HEIGHT - player->getY() * 1.5f));
		}
	}

	if (input->isKeyDown(VK_RIGHT)) {
		if (Map1->getMapX() < -1120 || player->getX() < GAME_WIDTH / 2) {
			if (player->getX() + playerSize + Movespeed <
				GAME_WIDTH - (GAME_HEIGHT - player->getY() * 1.5f)) {
				player->setX(player->getX() + Movespeed);
			}
		}
		else {
			Map1->mapMove(-Movespeed, 0);
		}
		player->update(0.05f);
	}
	if (input->isKeyDown(VK_LEFT)) {
		if ((Map1->getMapX() >= 0 || player->getX() > GAME_WIDTH / 2)) {
			if (player->getX() - Movespeed > 
				0 + (GAME_HEIGHT - player->getY() * 1.5f)) {
				player->setX(player->getX() - Movespeed);
			}
		}
		else {
			Map1->mapMove(Movespeed, 0);
		}
		player->update(0.05f);
	}	
    
	//////////////////////////////////////////////////////////////////
	// ㄴ플레이어 클래스로 이동

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
		exit(0);
	}
}

void MainScenes::render()
{
	graphics->spriteBegin();

	Map1->getMapBG()->draw();
	objectManager->RenderAllObject();

	//fontText->print("Hello WORLD!", 100, 100);
	//fontText->print("ABCDEFGH", 100, 164);

	graphics->spriteEnd();
}

