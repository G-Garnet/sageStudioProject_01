#ifndef _ROOM5_H             
#define _ROOM5_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room5 : public Game
{
private:
	ObjectManager* objectManager;

	Player* player;

	Junk2DSprite* Door1;
	Junk2DSprite* cross1;
	Junk2DSprite* cross2;
	Junk2DSprite* light;

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
