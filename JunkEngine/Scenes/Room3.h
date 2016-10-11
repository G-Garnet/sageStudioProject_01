#ifndef _ROOM3_H             
#define _ROOM3_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room3 : public Game
{
private:
	ObjectManager* objectManager;

	//// ���� �⺻ ���� ��ҵ� ////
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

	// ���� ��ҵ�
	Junk2DMap* Map;

public:
	Room3();
	virtual ~Room3();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
