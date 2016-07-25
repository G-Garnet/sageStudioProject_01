#ifndef _MAINSCENE_H             
#define _MAINSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class MainScenes : public Game
{
private:
	ObjectManager* objectManager;

	// ���� ��ҵ�
	Junk2DSprite* player;
	Junk2DSprite* Ghost;

	Junk2DSprite* BackGround;


public:
	MainScenes();
	virtual ~MainScenes();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

	/*void releaseAll();
	void resetAll();*/

};

#endif