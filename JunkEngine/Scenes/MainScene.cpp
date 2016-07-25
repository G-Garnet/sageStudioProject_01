#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Junk2DSprite;
	Ghost = new Junk2DSprite;
	BackGround = new Junk2DSprite;
}

MainScenes::~MainScenes()
{
}

void MainScenes::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// 이미지 정보름 미리 선언
	BackGround->settingTexture(graphics, "..\\Resources\\orion.jpg", 640, 480, 1);
	BackGround->setXY(0, 0);

	Ghost->settingTexture(graphics, "..\\Resources\\m-water002.png", 264, 264, 1);
	Ghost->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);

	player->settingTexture(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	player->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	player->setLoop(true);
	player->setAnimation(0, 3, 0, 3.0f);
	//player->setFrameDelay(0.1f);

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

	player->update(0.1f);

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

