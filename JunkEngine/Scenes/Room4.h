#ifndef _ROOM4_H             
#define _ROOM4_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room4 : public Game
{
private:
	ObjectManager* objectManager;

	Player* player;

	Junk2DSprite* Door1;
	Junk2DSprite* Door2;
	Junk2DSprite* Blood;
	Junk2DSprite* Carpet;
	Junk2DSprite* Pictures;

	// ���� ��ҵ�
	Junk2DMap* Map;

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