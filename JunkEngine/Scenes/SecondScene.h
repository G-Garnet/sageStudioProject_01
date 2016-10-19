#ifndef _SECONNDSCENE_H             
#define _SECONNDSCENE_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class SecondScene : public Game
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
	////////////////////////////////

	// ���� ��ҵ�
	Junk2DMap* Map;
	Junk2DSprite* Door1;
	Junk2DSprite* Door2;
	Junk2DSprite* Door3;

	Junk2DSprite* Window1;
	Junk2DSprite* Window2;

	Junk2DSprite* filter;
	Junk2DSprite* CutScene;

	bool girl;
	bool cutSceneActive = false;
	int eventCount = 0;
	float dtime = 0;

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
