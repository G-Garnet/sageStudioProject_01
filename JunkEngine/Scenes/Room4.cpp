#include "Scenes.h"

Room4::Room4()
{
	objectManager = new ObjectManager;

	for (int i = 0; i < 6; i++) {
		CutScene[i] = new Junk2DSprite();
	}
	select = new Junk2DSprite();
	newGame = new Junk2DSprite();
	LoadGame = new Junk2DSprite();
	Exit = new Junk2DSprite();
	fade = new Fade();
}

Room4::~Room4()
{
	objectManager->RemoveAllObject();
	for (int i = 0; i < 6; i++) {
		SAFE_DELETE(CutScene[i]);
	}
	SAFE_DELETE(select);
	SAFE_DELETE(newGame);
	SAFE_DELETE(LoadGame);
	SAFE_DELETE(Exit);
	SAFE_DELETE(fade);
}

void Room4::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	CutScene[0]->settingTexture(graphics, "..\\Resources\\Main\\0.png", 1280, 720, 1);
	CutScene[1]->settingTexture(graphics, "..\\Resources\\Main\\1.png", 1280, 720, 1);
	CutScene[2]->settingTexture(graphics, "..\\Resources\\Main\\1-1.png", 1280, 720, 1);
	CutScene[3]->settingTexture(graphics, "..\\Resources\\Main\\1-3.png", 1280, 720, 1);
	CutScene[4]->settingTexture(graphics, "..\\Resources\\Main\\2-1.png", 1280, 720, 1);
	CutScene[5]->settingTexture(graphics, "..\\Resources\\Main\\2-2.png", 1280, 720, 1);
	
	for (int i = 0; i < 5; i++) {
		CutScene[0]->setXY(0, 0);
	}

	select->settingTexture(graphics, "..\\Resources\\Main\\menu_E.png", 154, 49, 1);
	newGame->settingTexture(graphics, "..\\Resources\\Main\\new game.png", 154, 50, 1);
	LoadGame->settingTexture(graphics, "..\\Resources\\Main\\load game.png", 154, 49, 1);
	Exit->settingTexture(graphics, "..\\Resources\\Main\\ext.png", 309, 53, 1);

	select->setXY(954, 392);
	newGame->setXY(1039, 394);
	LoadGame->setXY(1039, 472);
	Exit->setXY(1039, 556);

	fade->fadeSetting(graphics);
	fade->setAlpha(255);

	//audio->playCue("");
	initialized = true;

	return;
}

void Room4::Update()
{
	if (fade->getalphaStart()) {
		fade->setAlpha(fade->getAlpha() + 1.75f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f) {
		fade->setAlpha(fade->getAlpha() - 1.75f);
	}

	if (fade->getAlpha() >= 255) {
		if (select_ == 1) {
			Game *temp = new Room3;
			ChangeScene(temp);
		}

		if (select_ == 2) {
			Game *temp = new Room5;
			ChangeScene(temp);
		}

	}


	timeCount += 0.1f; 
	if (timeCount >= 40) {
		scene = 0;
		timeCount = 0;
	}
	else if (timeCount >= 38) {
		scene = 5;
	}
	else if (timeCount >= 36) {
		scene = 4;
	}
	else if (timeCount >= 32) {
		scene = 3;
	}
	else if (timeCount >= 31) {
		scene = 2;
	}
	else if (timeCount >= 30) {
		scene = 1;
	}

	if (input->isKeyUp(VK_UP)) {
		select_--;
		if (select_ == 0) {
			select_ = 3;
		}
	}

	if (input->isKeyUp(VK_DOWN)) {
		select_++;
		if (select_ == 4) {
			select_ = 1;
		}
	}

	if (input->isKeyUp(VK_ESCAPE)) {
		exit(0);
	}

	switch (select_) {
	case 1: select->setXY(954, 392); break;
	case 2: select->setXY(954, 470); break;
	case 3: select->setXY(954, 554); break;
	}

	if (input->isKeyUp(VK_RETURN)) {

		//audio->stopCue("");
		//audio->playCue("");

		switch (select_) {
		case 1: fade->setalphaStart(true); break;
		case 2: fade->setalphaStart(true); break;
		case 3: exit(0); break;
		}
	}

	//exitGame();
}

void Room4::render()
{
	graphics->spriteBegin();

	CutScene[scene]->draw();
	newGame->draw();
	LoadGame->draw();
	Exit->draw();
	select->draw();

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
