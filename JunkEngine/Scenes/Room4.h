#ifndef _ROOM4_H             
#define _ROOM4_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room4 : public Game
{
private:
	ObjectManager* objectManager;

	//// ���� �⺻ ���� ��ҵ� ////
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


	// ���� ��ҵ�
	Junk2DMap* Map;

	bool eventStart = false;
	int eventCount = -1;

public:
	Room4();
	virtual ~Room4();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
