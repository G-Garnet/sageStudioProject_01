#ifndef _ROOM5_H             
#define _ROOM5_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Monster.h"
#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room5 : public Game
{
private:
	ObjectManager* objectManager;

	//// ���� �⺻ ���� ��ҵ� ////
	Player* player;
	ItemSlot* itemSlot;
	Cursor* cursor;
	Junk2DFont *font;
	Fade* fade;

	Junk2DSprite* filter;
	////////////////////////////////

	Monster* mop1;

	Video* videoPlayer;
	bool ending = false;

	// ���� ��ҵ�
	Junk2DMap* Map;

public:
	Room5();
	virtual ~Room5();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
