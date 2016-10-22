#ifndef _ROOM4_H             
#define _ROOM4_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class Room4 : public Game
{
private:
	ObjectManager* objectManager;

	//// 씬의 기본 구성 요소들 ////
	Player* player;
	ItemSlot* itemSlot;
	Cursor* cursor;
	Junk2DFont *font;
	TextWindow *textWindow;
	Fade* fade;

	Junk2DSprite* filter;
	////////////////////////////////

	Junk2DSprite* Door1;
	Junk2DSprite* Door2;
	Junk2DSprite* Blood;
	Junk2DSprite* Carpet;
	Junk2DSprite* Pictures;

	Junk2DSprite* CutScene;


	// 게임 요소들
	Junk2DMap* Map;

	bool eventStart = false;
	int eventCount = -1;

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
