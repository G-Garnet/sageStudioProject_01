#ifndef _ROOM3_H             
#define _ROOM3_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room3 : public Game
{
private:
	//// ���� �⺻ ���� ��ҵ� ////
	Fade* fade;
	TextWindow *textWindow;

	Junk2DSprite *cutScene[10];
	Junk2DSprite *sideCut1;
	Junk2DSprite *sideCut2;

	////////////////////////////////

	float scenetime = 0;
	int sceneNum = 0;

	int eventCount = 0;

public:
	Room3();
	virtual ~Room3();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
