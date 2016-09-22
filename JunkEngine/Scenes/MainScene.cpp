#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Junk2DEntity;

	Map1 = new Junk2DMap();

	Door1 = new Junk2DSprite();
	Door2 = new Junk2DSprite();
}

MainScenes::~MainScenes()
{
	//SAFE_DELETE(map1);
	objectManager->RemoveAllObject();
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
	Map1->settingBGSprite(graphics, "..\\Resources\\Room1.png");

	Door1->settingTexture(graphics, "..\\Resources\\Door.png", 220, 460, 1);
	Door1->setXY(GAME_WIDTH / 2 - 200, 0+64);

	player->initialize(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	player->setXY(GAME_WIDTH/ 2, GAME_HEIGHT / 2);
	//player->set
	player->setLoop(true);
	player->setActive(true);
	player->setCollisionType(Junk2DentityNS::BOX);
	player->setAnimation(0, 3, 0, 3.0f);
	//player->setFrameDelay(0.1f);

	// �±� ����
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(player, "player");

	Map1->MapAddObject(objectManager->getCGameObject("Door1"),"Door1");

	Map1->mapMove(0, 0);

	playerSize = player->getSpriteDataRect().right;

	initialized = true;

	return;
}

void MainScenes::Update()
{ 
	// �÷��̾� �̵� Ŭ����
	// ���� �÷��̾� Ŭ������ ���� ��üȭ ���Ѽ� �̵��� ����
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
	// ���÷��̾� Ŭ������ �̵�

	//}

	//if () {
		// ĳ���Ͱ� �̵��ؾ� �� ���
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

