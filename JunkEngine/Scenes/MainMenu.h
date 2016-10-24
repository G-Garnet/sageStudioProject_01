#ifndef _MAINMENU_H           
#define _MAINMENU_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"
#include "..\\Headers\\video.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class MainMenu : public Game
{
private:
	ObjectManager* objectManager;

	Video* videoPlayer;

	bool start = false;

public:
	MainMenu();
	virtual ~MainMenu();

	// 게임 기본 구성 함수들
	void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
