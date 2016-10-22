#include "Scenes.h"

SecondScene::SecondScene()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap;

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	fade = new Fade();
	font = new Junk2DFont();
	textWindow = new TextWindow();
	
	Door1 = new Junk2DSprite();
	Door2 = new Junk2DSprite();
	Door3 = new Junk2DSprite();

	Window1 = new Junk2DSprite();
	Window2 = new Junk2DSprite();
	Ghost = new Junk2DEntity();

	filter = new Junk2DSprite();
	CutScene = new Junk2DSprite();

	girl = false;
}

SecondScene::~SecondScene()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
	SAFE_DELETE(textWindow);
	SAFE_DELETE(CutScene);
	SAFE_DELETE(Ghost);
	SAFE_DELETE(filter);
}

void SecondScene::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	// 이미지 정보름 미리 선언
	Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room2\\Room2_bg.png");

	Door1->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_LeftDoor.png", 163, 532, 1);
	Door1->setXY(64, 148);
	Door2->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_RightDoor.png", 163, 532, 1);
	Door2->setXY(1670, 148);
	Door3->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_Door.png", 398, 498, 1);
	Door3->setXY(750, 24);

	Window1->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_Window2.png", 356, 326, 1);
	Window1->setXY(350, 30);
	Window2->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Room2_Window1.png", 365, 206, 1);
	Window2->setXY(1172, 48);

	filter->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\2_roomd.png", 1900, 720, 1);
	filter->setXY(0, 0);

	Ghost->settingTexture(graphics, "..\\Resources\\Floor1\\Room2\\Ch_02_flying.png", 250, 400, 7);
	Ghost->setAnimation(0,6,0,0.2f);
	Ghost->setXY(350, 200);
	Ghost->setActive(true);
	Ghost->setCollisionType(Junk2DentityNS::BOX);
	Ghost->setEdge(64, 0, 72, 400);
	Ghost->flipHorizontal(true);

	CutScene->settingTexture(graphics, "..\\Resources\\Etc\\CutScene1.png", 1280, 720, 1);
	CutScene->setXY(0, 0);

	// Scene의 기본 요소들 //
	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	font->initialize(graphics, 15, true, false, "굴림체");
	fade->fadeSetting(graphics);
	textWindow->TextWindowSetting(graphics);
	textWindow->setActive(true);
	fade->setAlpha(254);
	/////////////////////////

	Map->mapMove(0, 0);

	// 태그 설정
	objectManager->AddObject(Door1, "Door1");
	objectManager->AddObject(Door2, "Door2");
	objectManager->AddObject(Door3, "Door3");
	objectManager->AddObject(Window1, "Window1");
	objectManager->AddObject(Window2, "Window2");
	objectManager->AddObject(player, "Player");

	Map->MapAddObject(objectManager->getCGameObject("Door1"), "Door1");
	Map->MapAddObject(objectManager->getCGameObject("Door2"), "Door2");
	Map->MapAddObject(objectManager->getCGameObject("Door3"), "Door3");
	Map->MapAddObject(objectManager->getCGameObject("Window1"), "Window1");
	Map->MapAddObject(objectManager->getCGameObject("Window2"), "Window2");
	Map->MapAddObject(filter, "filter");
	Map->MapAddObject(Ghost, "Ghost");

	player->setMapszie(876-256);
	if (Player::p_PosScene == 1) {
		player->setX(114);
	}
	else if (Player::p_PosScene == 3) {
		player->setX(1080);
	}
	Player::p_PosScene = 2;

	//Map->mapMove(300, 0);

	initialized = true;
	//player->setXY(64, 150);

	return;
}

void SecondScene::Update()
{
	if (!textWindow->getActive()) {
		player->playerInput(input, Map);
	}
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);
	 
	// FADE //
	if (fade->getalphaStart()) {
		fade->setAlpha(fade->getAlpha() + 1.75f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f) {
		fade->setAlpha(fade->getAlpha() - 1.75f);
	}
	else if (fade->getAlpha() <= 1.5f) {
		player->setInputSW(true);
		if (StartEvent) {
			eventCount = 1;
			StartEvent = false;
		}
	}

	if (fade->getAlpha() >= 255) {
		Game *temp = new Room3;

		ChangeScene(temp);
	}
	///////

	// 등장 이벤트
	if (girl) {
		dtime += 0.01f;
		
		if (dtime >= 0.4f) {
			cutSceneActive = true;
		}
		
		if (dtime>=0.55f){
			dtime = 0;
		}
		else {
			cutSceneActive = false;
		}
	}

	if (eventCount == 3) {
		eventCount = 4;
		Sleep(2000);
	}

	// 클릭 이벤트 //
	if (textWindow->getActive() && (input->isKeyUp(VK_RETURN) || input->getMouseLButtonDown())) {

		switch (eventCount) {
		case 2:
			eventCount = 3;
			textWindow->setActive(false);
			girl = true;
			break;
		default:
			textWindow->setActive(false);
			eventCount = 0;
			break;
		}
	}

	

	else if (!textWindow->getActive() && input->getMouseLButtonDown()) {
		if ((input->getMouseX() >= Window1->getX() && input->getMouseX() <= Window1->getX() + Window1->getWidth()) &&
			(input->getMouseY() >= Window1->getY() && input->getMouseY() <= Window1->getY() + Window1->getHeight())) {
			eventCount = -1;
			textWindow->setActive(true);
		}
		if ((input->getMouseX() >= Window2->getX() && input->getMouseX() <= Window2->getX() + Window2->getWidth()) &&
			(input->getMouseY() >= Window2->getY() && input->getMouseY() <= Window2->getY() + Window2->getHeight())) {
			eventCount = -1;
			textWindow->setActive(true);
		}

		if ((input->getMouseX() >= Door3->getX() && input->getMouseX() <= Door3->getX() + Door3->getWidth()) &&
			(input->getMouseY() >= Door3->getY() && input->getMouseY() <= Door3->getY() + Door3->getHeight())) {
			eventCount = 2;
			textWindow->setActive(true);
		}

		
	}

	// 다음방으로
	if (input->isKeyUp(VK_RETURN) && player->getX() >= 665 && player->getY() >= 230) {
		/*Game *temp = new Room3;

		ChangeScene(temp);*/
		fade->setalphaStart(true);
	}

	
	if (girl) {
		Ghost->setX(Ghost->getX()+2);

		if (player->collidesWith(Ghost, CollisionVector)) {

			exitGame();
		}
	}

	//exitGame();
}

void SecondScene::render()
{
	graphics->spriteBegin();

	Map->getMapBG()->draw();
	objectManager->RenderAllObject();

	if (girl) {
		Ghost->update(1.0f / 60.0f);
		Ghost->draw();
	}

	filter->draw();

	switch (eventCount) {
	case -1:
		textWindow->TextWindowRender("빨리 나가야해.", 0);
		break;
	case 1:
		textWindow->TextWindowRender("어제 그 방이다.", 0);
		break;
	case 2:
		textWindow->TextWindowRender("열리지 않는다.", 0);
		break;
	}

	if (cutSceneActive) {
		CutScene->draw();
	}

	

	itemSlot->ItemSlotRender();
	cursor->draw();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	graphics->spriteEnd();
}

//void MainScenes::releaseAll()
//{
//	Game::releaseAll();
//	return;
//}

//void MainScenes::resetAll()
//{
//	Game::resetAll();
//	return;
//}
