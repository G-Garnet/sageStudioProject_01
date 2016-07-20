#ifndef _SCENES_H             
#define _SCENES_H             
#define WIN32_LEAN_AND_MEAN

#include "game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Scenes : public Game
{
private:	

	// ���� ��ҵ�
	// Junk2DSprite player;

    // ����
	// bool vibrate = true;

public:
	Scenes() {};
	virtual ~Scenes() { releaseAll(); };

    // ���� �⺻ ���� �Լ���
    virtual void initialize(HWND hwnd) = 0;
    
	virtual void Update() = 0;      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
    virtual void render() = 0;      // "

	

};

#endif
