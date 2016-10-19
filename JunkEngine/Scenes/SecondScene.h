#ifndef _SECONNDSCENE_H             
#define _SECONNDSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class SecondScene : public Game
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
	////////////////////////////////

	// 게임 요소들
	Junk2DMap* Map;
	Junk2DSprite* Door1;
	Junk2DSprite* Door2;
	Junk2DSprite* Door3;

	Junk2DSprite* Window1;
	Junk2DSprite* Window2;

	Junk2DSprite* filter;
	Junk2DSprite* CutScene;

	bool girl;
	bool cutSceneActive = false;
	int eventCount = 0;
	float dtime = 0;

public:
	SecondScene();
	virtual ~SecondScene();

	// 게임 기본 구성 함수들
	void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
