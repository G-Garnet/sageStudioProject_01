#ifndef _MAINSCENE_H             
#define _MAINSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"
#include "Scenes.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class MainScenes : public Game
{
private:
	ObjectManager* objectManager;

	//// ���� �⺻ ���� ��ҵ� ////
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

	// ���� �⺻ ���� �Լ���
	virtual void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

	/*void releaseAll();
	void resetAll();*/

};

#endif
