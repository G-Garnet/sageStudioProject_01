#ifndef _GAME_H                 // 다중정의 방지
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
	Graphics *graphics;         // Graphics 객체 포인터
	Input   *input;             // Input 객체 포인터
	HWND    hwnd;               // 윈도우 핸들
	HRESULT hr;                 // 표준 반환 타입
	LARGE_INTEGER timeStart;    // 성능 카운터 시작값
	LARGE_INTEGER timeEnd;      // 성능 카운터 종료 값
	LARGE_INTEGER timerFreq;    // 성능 카운터 빈도수
	float   frameTime;          // 마지막 프레임에 필요한 시간
	float   fps;                // 초당 프레임수
	DWORD   sleepTime;          // 프레임 사이의 대기 단위 시간
	bool    paused;             // 게임 일시정지 상태
	bool    initialized;        // 초기화


	Junk2DSound*  audio;		// 사운드 

	int Maps[1000][1000];
	int mapMaxX, mapMaxY;
	

public:
	Game(); // 생성자
	virtual ~Game(); // 소멸자

	static Game *nowScene;

					 // --------- 멤버 함수 ---------//

	//윈도우 메세지 핸들러
	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// 게임 초기화
	virtual void initialize(HWND hwnd); // hwnd는 윈도우 핸들러
	virtual void run(HWND);				// 반복 호출, 명령 실행
	virtual void releaseAll();          // 그래픽 디바이스 리셋
	virtual void resetAll();			// 표면 재생성 후 모든 개체 리셋
	virtual void deleteAll();           // 예약된 모든 메모리 삭제
	virtual void renderGame();          // 게임 렌더링

	virtual void handleLostGraphicsDevice(); // 로스트 상태가 된 그래픽 디바이스 처리

	Graphics* getGraphics() { return graphics; }	// Graphics 객체 포인터 반환
	Input* getInput() { return input; }		// Input 객체 포인터 반환

	/*virtual void addEntity(Junk2DEntity* entity);
	virtual void UpdateEntity();*/

	void exitGame() { // 게임 종료
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
	// ------------------------------//

	virtual void mapInput(const char* mapName);
	virtual void LoadMap();

	virtual void Update() = 0;		// 게임요소 갱신
	virtual void render() = 0;		// 렌더링

	virtual void ChangeScene(Game* var);
/*
	virtual void releaseAll() { Game::releaseAll(); return; };
	virtual void resetAll() { Game::resetAll(); return; };*/
};

#endif
