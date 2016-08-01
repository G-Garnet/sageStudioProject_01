#ifndef _GAME_H                 // �������� ����
#define _GAME_H                 
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include <fstream>
#include <iostream>

#include "gameError.h"
#include "graphics.h"
#include "input.h"
#include "Junk2DSprite.h"
#include "Junk2DFont.h"
#include "ObjectManager.h"

#include "Sounds.h"

class Game
{
protected:
	Graphics *graphics;         // Graphics ��ü ������
	Input   *input;             // Input ��ü ������
	HWND    hwnd;               // ������ �ڵ�
	HRESULT hr;                 // ǥ�� ��ȯ Ÿ��
	LARGE_INTEGER timeStart;    // ���� ī���� ���۰�
	LARGE_INTEGER timeEnd;      // ���� ī���� ���� ��
	LARGE_INTEGER timerFreq;    // ���� ī���� �󵵼�
	float   frameTime;          // ������ �����ӿ� �ʿ��� �ð�
	float   fps;                // �ʴ� �����Ӽ�
	DWORD   sleepTime;          // ������ ������ ��� ���� �ð�
	bool    paused;             // ���� �Ͻ����� ����
	bool    initialized;        // �ʱ�ȭ


	Junk2DSound*  audio;		// ���� 

	int Maps[1000][1000];
	int mapMaxX, mapMaxY;
	

public:
	Game(); // ������
	virtual ~Game(); // �Ҹ���

	static Game *nowScene;

					 // --------- ��� �Լ� ---------//

	//������ �޼��� �ڵ鷯
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// ���� �ʱ�ȭ
	virtual void initialize(HWND hwnd); // hwnd�� ������ �ڵ鷯
	virtual void run(HWND);				// �ݺ� ȣ��, ��� ����
	virtual void releaseAll();          // �׷��� ����̽� ����
	virtual void resetAll();			// ǥ�� ����� �� ��� ��ü ����
	virtual void deleteAll();           // ����� ��� �޸� ����
	virtual void renderGame();          // ���� ������

	virtual void handleLostGraphicsDevice(); // �ν�Ʈ ���°� �� �׷��� ����̽� ó��

	Graphics* getGraphics() { return graphics; }	// Graphics ��ü ������ ��ȯ
	Input* getInput() { return input; }		// Input ��ü ������ ��ȯ

	/*virtual void addEntity(Junk2DEntity* entity);
	virtual void UpdateEntity();*/

	void exitGame() { // ���� ����
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
	// ------------------------------//

	virtual void mapInput(const char* mapName);
	virtual void LoadMap();

	virtual void Update() = 0;		// ���ӿ�� ����
	virtual void render() = 0;		// ������

	virtual void ChangeScene(Game* var);
/*
	virtual void releaseAll() { Game::releaseAll(); return; };
	virtual void resetAll() { Game::resetAll(); return; };*/
};

#endif
