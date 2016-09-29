#ifndef _MAINSCENE_H             
#define _MAINSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"
#include "..\\Headers\Player.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class MainScenes : public Game
{
private:
	ObjectManager* objectManager;

	//// ���� ��ҵ�
	Player* player;

	Junk2DMap* Map1;
	Junk2DSprite* Door1;
	Junk2DEntity* Desk;
	Junk2DEntity* Hanger;
	Junk2DEntity* Carpet;
	Junk2DSprite* Pipe;

	//Junk2DFont *fontText;
	VECTOR2 CollisionVector;

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
