#ifndef _ROOM4_H             
#define _ROOM4_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class Room4 : public Game
{
private:
	ObjectManager* objectManager;

	Junk2DSprite* CutScene[6];
	Junk2DSprite* select;
	Junk2DSprite* newGame;
	Junk2DSprite* LoadGame;
	Junk2DSprite* Exit;
	Fade* fade;

	int scene = 0;
	int select_ = 1;

	float timeCount = 0;

public:
	Room4();
	virtual ~Room4();

	// 게임 기본 구성 함수들
	void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
