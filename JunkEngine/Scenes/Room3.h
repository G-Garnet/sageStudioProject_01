#ifndef _ROOM3_H             
#define _ROOM3_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class Room3 : public Game
{
private:
	//// 씬의 기본 구성 요소들 ////
	Fade* fade;
	TextWindow *textWindow;

	Junk2DSprite *cutScene[10];
	Junk2DSprite *sideCut1;
	Junk2DSprite *sideCut2;

	////////////////////////////////

	float scenetime = 0;
	int sceneNum = 0;

	int eventCount = 0;

public:
	Room3();
	virtual ~Room3();

	// 게임 기본 구성 함수들
	void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
