#ifndef _SCENES_H             
#define _SCENES_H             
#define WIN32_LEAN_AND_MEAN

#include "game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class Scenes : public Game
{
private:	

	// 게임 요소들
	// Junk2DSprite player;

    // 변수
	// bool vibrate = true;

public:
	Scenes() {};
	virtual ~Scenes() { releaseAll(); };

    // 게임 기본 구성 함수들
    virtual void initialize(HWND hwnd) = 0;
    
	virtual void Update() = 0;      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
    virtual void render() = 0;      // "

	

};

#endif
