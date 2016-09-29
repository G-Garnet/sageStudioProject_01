#ifndef _SECONNDSCENE_H             
#define _SECONNDSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class SecondScene : public Game
{
private:
	ObjectManager* objectManager;

	Player* player;

	// ���� ��ҵ�
	Junk2DMap* Map;

public:
	SecondScene();
	virtual ~SecondScene();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
