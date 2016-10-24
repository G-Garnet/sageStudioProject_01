#ifndef _MAINMENU_H           
#define _MAINMENU_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"
#include "..\\Headers\\video.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class MainMenu : public Game
{
private:
	ObjectManager* objectManager;

	Video* videoPlayer;

	bool start = false;

public:
	MainMenu();
	virtual ~MainMenu();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
