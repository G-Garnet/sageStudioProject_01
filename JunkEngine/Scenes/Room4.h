#ifndef _ROOM4_H             
#define _ROOM4_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room4 : public Game
{
private:
	ObjectManager* objectManager;

	Junk2DSprite* CutScene[6];
	Junk2DSprite* select;
	Junk2DSprite* newGame;
	Junk2DSprite* LoadGame;
	Junk2DSprite* Exit;
	Fade* fade;

	int scene = 0;
	int select_ = 1;

	float timeCount = 0;

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
