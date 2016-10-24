#include "Scenes.h"

MainMenu::MainMenu()
{
	videoPlayer = new Video();
}

MainMenu::~MainMenu()
{
	SAFE_DELETE(videoPlayer);
}

void MainMenu::initialize(HWND hwnd)
{
	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));


	//Map->mapMove(300, 0);

	initialized = true;

	return;
}

void MainMenu::Update()
{
	if (!start) {
		start = true;
		videoPlayer->play(hwnd,L"..\\\Resources\\Video\\openning.avi");
		Game *temp = new MainScenes;

		ChangeScene(temp);
	}
}

void MainMenu::render()
{
	graphics->spriteBegin();

	graphics->spriteEnd();
}
