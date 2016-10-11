#ifndef _MAINSCENE_H             
#define _MAINSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"
#include "Scenes.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class MainScenes : public Game
{
private:
	ObjectManager* objectManager;

	//// 씬의 기본 구성 요소들 ////
	Player* player;
	ItemSlot* itemSlot;
	Cursor* cursor;
	Junk2DFont *font;
	////////////////////////////////

	Junk2DMap* Map1;
	Junk2DSprite* Door1;
	Junk2DEntity* Desk;
	Junk2DEntity* Hanger;
	Junk2DEntity* Carpet;
	Junk2DSprite* Pipe;

	Fade* fade;

	RECT rc = { 0, 0, 100, 100 };

	LPD3DXFONT	g_pFont;
	ID3DXSprite*  Sprite;
	VECTOR2 CollisionVector;

public:

	MainScenes();
	~MainScenes();

	// 게임 기본 구성 함수들
	virtual void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

	/*void releaseAll();
	void resetAll();*/

};

#endif
