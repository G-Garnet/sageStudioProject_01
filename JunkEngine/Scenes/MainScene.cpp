#include "Scenes.h"

MainScenes::MainScenes()
{
	objectManager = new ObjectManager;

	player = new Junk2DEntity;
	Ghost = new Junk2DEntity;
	BackGround = new Junk2DSprite;
	fontText = new Junk2DFont();
}

MainScenes::~MainScenes()
{
	
}

void MainScenes::initialize(HWND hwnd)
{
	Game::initialize(hwnd);

	// 텍스트 초기화
	fontText->settingFontTexture(graphics, "..\\Resources\\m-water001.png");

	// 이미지 정보름 미리 선언
	BackGround->settingTexture(graphics, "..\\Resources\\orion.png", 1280, 720, 1);
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

	// 태그 설정
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


	if (input->isKeyUp(VK_RETURN)) {
		Game *temp = new SecondScene;

		ChangeScene(temp);
	}
}

void MainScenes::render()
{
	graphics->spriteBegin();

	objectManager->RenderAllObject();

	fontText->setProportional(false);
	fontText->setFontColor(graphicsNS::BLACK);
	fontText->setBackColor(TRANSCOLOR);
	fontText->setFontHeight(62 * 2);
	fontText->print("C", 100, 100);

	graphics->spriteEnd();
}

