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

	// Input��ü �ʱ�ȭ
	input->initialize(hwnd, false);
	// Ÿ�̸� ���
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

	// Scene�� �⺻ ��ҵ� //
	textWindow->TextWindowSetting(graphics);
	textWindow->setActive(false);
	//font->initialize(graphics, 12, true, false, "����ü");
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
		textWindow->TextWindowRender("���� ����, ���� ���� �� �� ������...", 1);
		break;
	case 2:
		textWindow->TextWindowRender("���� �ҳ�� ��Ӵϰ� ��� �־����.", 1);
		break; 
	case 3:
		textWindow->TextWindowRender("�ҳ�� ��Ӵ���...", 1);
		break;
	case 4:
		textWindow->TextWindowRender("�����...", 1);
		break;
	case 5:
		textWindow->TextWindowRender("�������� ������...", 1);
		break;
	case 6:
		textWindow->TextWindowRender("�������� �ڶ���ϴ�.", 1);
		break;
	case 7:
		textWindow->TextWindowRender("�׷��� ��� ��, ��Ӵϰ� ���� ���� �ʰ� �Ǿ����.", 1);
		break;
	case 8:
		textWindow->TextWindowRender("\'�ҸӴϿ��� ã�ư���.\' �ҳ�� �����߾��.", 1);
		break;
	case 9:
		textWindow->TextWindowRender("���� ��Ӱ� ��������, ����� ���� ���䰡 �ִٸ� �ҳ�� �η��� �� ��������.", 1);
		break;
	case 10:
		textWindow->TextWindowRender("�ҳ�� �ҸӴϸ� ������ ���� �� ������ ������ �˴ϴ�.", 1);
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
