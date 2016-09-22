#ifndef _MAINSCENE_H             
#define _MAINSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class MainScenes : public Game
{
private:
	ObjectManager* objectManager;

	//// ���� ��ҵ�
	Junk2DEntity* player;

	Junk2DMap* Map1;
	Junk2DSprite* Door1;
	Junk2DSprite* Door2;

	int Movespeed = 2;
	int playerSize;
	//Junk2DFont *fontText;

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
