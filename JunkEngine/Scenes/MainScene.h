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
	//Junk2DEntity* player;
	//Junk2DEntity* Ghost;

	//Junk2DSprite* BackGround;

	//Junk2DFont *fontText;

	


public:
	Junk2DMap* map1;
	Junk2DSprite* Window;
	Junk2DSprite* Door;

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
