#ifndef _ROOM5_H             
#define _ROOM5_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class Room5 : public Game
{
private:
	ObjectManager* objectManager;

	Player* player;

	Junk2DSprite* Door1;
	Junk2DSprite* cross1;
	Junk2DSprite* cross2;
	Junk2DSprite* light;

	// 게임 요소들
	Junk2DMap* Map;

public:
	Room5();
	virtual ~Room5();

	// 게임 기본 구성 함수들
	void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
