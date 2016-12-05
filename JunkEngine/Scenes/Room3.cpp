#include "Scenes.h"

Room3::Room3()
{
	textWindow = new TextWindow();
	fade = new Fade();

	for (int i = 0; i < 10; i++) {
		cutScene[i] = new Junk2DSprite;
	}

	sideCut1 = new Junk2DSprite;
	sideCut2 = new Junk2DSprite;
}

Room3::~Room3()
{
	SAFE_DELETE(fade);
	SAFE_DELETE(textWindow);
	for (int i = 0; i < 10; i++) {
		SAFE_DELETE(cutScene[i]);
	}
	SAFE_DELETE(sideCut1);
	SAFE_DELETE(sideCut2);
}

void Room3::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	cutScene[0]->settingTexture(graphics, "..\\Resources\\openning\\1.png", 1280, 720, 1);
	cutScene[1]->settingTexture(graphics, "..\\Resources\\openning\\2.png", 1280, 720, 1);
	cutScene[2]->settingTexture(graphics, "..\\Resources\\openning\\3.png", 1280, 720, 1);
	cutScene[3]->settingTexture(graphics, "..\\Resources\\openning\\4.png", 1280, 720, 1);
	cutScene[4]->settingTexture(graphics, "..\\Resources\\openning\\5.png", 1280, 720, 1);
	cutScene[5]->settingTexture(graphics, "..\\Resources\\openning\\6.png", 1280, 720, 1);
	cutScene[6]->settingTexture(graphics, "..\\Resources\\openning\\7.png", 1280, 720, 1);
	cutScene[7]->settingTexture(graphics, "..\\Resources\\openning\\8.png", 1280, 720, 1);
	cutScene[8]->settingTexture(graphics, "..\\Resources\\openning\\9.png", 1280, 720, 1);
	cutScene[9]->settingTexture(graphics, "..\\Resources\\openning\\10.png", 1280, 720, 1);

	sideCut1->settingTexture(graphics, "..\\Resources\\openning\\3-1.png", 1280, 720, 1);
	sideCut2->settingTexture(graphics, "..\\Resources\\openning\\4-1.png", 1280, 720, 1);

	// Scene의 기본 요소들 //
	textWindow->TextWindowSetting(graphics);
	textWindow->setActive(false);
	//font->initialize(graphics, 12, true, false, "굴림체");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	/////////////////////////


	//audio->playCue("knock and rattle");

	initialized = true;

	return;
}

void Room3::Update()
{
	if (fade->getalphaStart()) {
		fade->setAlpha(fade->getAlpha() + 1.0f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f) {
		fade->setAlpha(fade->getAlpha() - 1.75f);
	}

	if (fade->getAlpha() >= 255) {
		std::ofstream out("save.ini");
		out << 10 << " " << 9;


		Game *temp = new Room5;

		ChangeScene(temp);
	}

	if (textWindow->getActive() &&
		(input->isKeyUp(VK_RETURN) || input->getMouseLButtonDown())) {

		switch (eventCount) {
		case 1:
			textWindow->resetStrLength();
			eventCount = 2;
			break; 
		case 2:
			textWindow->resetStrLength();
			eventCount = 3;
			break;
		case 3:
			textWindow->resetStrLength();
			eventCount = 4;
			break;
		case 4:
			textWindow->resetStrLength();
			eventCount = 5;
			break;
		case 5:
			textWindow->resetStrLength();
			eventCount = 6;
			break;
		case 6:
			textWindow->resetStrLength();
			eventCount = 7;
			break;
		case 7:
			textWindow->resetStrLength();
			eventCount = 8;
			break;
		case 8:
			textWindow->resetStrLength();
			eventCount = 9;
			break;
		case 9:
			textWindow->resetStrLength();
			eventCount = 10;
			break;
		case 10:
			textWindow->setActive(false);
			fade->setalphaStart(true);
			break;
		default:
			break;
		}

		sceneNum = eventCount - 1;
	}

	if (eventCount == 0 &&
		(input->isKeyUp(VK_RETURN) || input->getMouseLButtonDown())) {
		eventCount = 1;
		textWindow->resetStrLength();
		textWindow->setActive(true);
	}
	if (input->isKeyUp(VK_ESCAPE)) {
		exit(0);
	}
	//exitGame();
}

void Room3::render()
{
	graphics->spriteBegin();

	cutScene[sceneNum]->draw();

	if (scenetime > 4 && (sceneNum == 3 || sceneNum == 4)){
		if (sceneNum == 3) sideCut1->draw();
		else if (sceneNum == 4) sideCut2->draw();

		if (scenetime > 4.5f) scenetime = 0;
	}
	scenetime += 0.01f;


	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	switch (eventCount) {
	case 1:
		textWindow->TextWindowRender("옛날 옛적, 아주 깊은 산 속 마을에...", 1);
		break;
	case 2:
		textWindow->TextWindowRender("착한 소녀와 어머니가 살고 있었어요.", 1);
		break; 
	case 3:
		textWindow->TextWindowRender("소녀는 어머니의...", 1);
		break;
	case 4:
		textWindow->TextWindowRender("사랑과...", 1);
		break;
	case 5:
		textWindow->TextWindowRender("보살핌을 받으며...", 1);
		break;
	case 6:
		textWindow->TextWindowRender("무럭무럭 자랐답니다.", 1);
		break;
	case 7:
		textWindow->TextWindowRender("그러나 어느 날, 어머니가 눈을 뜨지 않게 되었어요.", 1);
		break;
	case 8:
		textWindow->TextWindowRender("\'할머니에게 찾아가자.\' 소녀는 생각했어요.", 1);
		break;
	case 9:
		textWindow->TextWindowRender("밖은 어둡고 무섭지만, 전등과 빨간 망토가 있다면 소녀는 두려울 게 없었지요.", 1);
		break;
	case 10:
		textWindow->TextWindowRender("소녀는 할머니를 만나기 위해 긴 여정을 떠나게 됩니다.", 1);
		break;
	}

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
