#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Junk2DEntity;
	Ghost = new Junk2DEntity;
	BackGround = new Junk2DSprite;
}

MainScenes::~MainScenes()
{
	
}

void MainScenes::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// �ؽ�Ʈ �ʱ�ȭ
	if (!fontCK->initialize(graphics, "..\\Resources\\font.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing font"));

	// �̹��� ������ �̸� ����
	BackGround->settingTexture(graphics, "..\\Resources\\orion.jpg", 1920, 1080, 1);
	BackGround->setXY(0, 0);

	Ghost->initialize(graphics, "..\\Resources\\m-water001.png", 264, 264, 1);
	Ghost->setCollisionType(Junk2DentityNS::BOX);
	Ghost->setActive(true);
	Ghost->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);

	player->initialize(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	player->setXY(0 , GAME_HEIGHT / 6);
	player->setLoop(true);
	player->setActive(true);
	player->setCollisionType(Junk2DentityNS::BOX);
	player->setAnimation(0, 3, 0, 3.0f);
	//player->setFrameDelay(0.1f);

	// �±� ����
	objectManager->AddObject(BackGround, "BackGround");
	objectManager->AddObject(Ghost, "Ghost");
	objectManager->AddObject(player, "player");

	return;
}

void MainScenes::Update()
{

	if (input->isKeyDown(VK_RIGHT)) player->setX(player->getX() + 1);
	if (input->isKeyDown(VK_LEFT))	player->setX(player->getX() - 1);
	if (input->isKeyDown(VK_DOWN))	player->setY(player->getY() + 1);
	if (input->isKeyDown(VK_UP))	player->setY(player->getY() - 1);

	VECTOR2 CollisionVector;
	if (Ghost != NULL && player->collidesWith(Ghost, CollisionVector)){
		//objectManager->RemoveObject("Ghost");
		player->bounce(CollisionVector, *Ghost);
		audio->playCue("beep2");
		//Ghost = NULL;
	}

	player->update(0.1f);

	fontCK->setProportional(false);
	fontCK->setFontColor(graphicsNS::BLACK);
	fontCK->setBackColor(TRANSCOLOR);
	fontCK->setFontHeight(62 * 2);
	fontCK->print("C", 20, 100);
	fontCK->setFontHeight(62);
	fontCK->print("C", 114, 148);
	fontCK->setFontHeight(62 / 4);
	fontCK->print("C", 164, 184);


	if (input->isKeyUp(VK_RETURN)) {
		Game *temp = new SecondScene;

		ChangeScene(temp);
	}
}

void MainScenes::render()
{
	graphics->spriteBegin();

	objectManager->RenderAllObject();

	graphics->spriteEnd();
}

