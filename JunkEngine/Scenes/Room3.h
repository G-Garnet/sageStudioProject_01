#ifndef _ROOM3_H             
#define _ROOM3_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class Room3 : public Game
{
private:
	ObjectManager* objectManager;

	//// 씬의 기본 구성 요소들 ////
	Player* player;
	ItemSlot* itemSlot;
	Cursor* cursor;
	Junk2DFont *font;
	////////////////////////////////

	Junk2DSprite* Door1;
	Junk2DSprite* Door2;
	Junk2DSprite* Candle1;
	Junk2DSprite* Candle2;
	Junk2DSprite* fire1;
	Junk2DSprite* Box;
	Junk2DSprite* Picture;
	Junk2DSprite* Desk;

	// 게임 요소들
	Junk2DMap* Map;

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
