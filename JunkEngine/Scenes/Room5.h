#ifndef _ROOM5_H             
#define _ROOM5_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Monster.h"
#include "..\\Headers\Game.h"

// ���� ���� Ŭ����, GameŬ������ ���� ��� ����
class Room5 : public Game
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

	Junk2DSprite* filter;
	Junk2DSprite* shadows;
	////////////////////////////////
	Monster* mop1;

	Junk2DSprite* Lanten1;
	Junk2DSprite* Tree1;
	Junk2DSprite* animalDeath1;
	Junk2DSprite* animalDeath2;
	Junk2DSprite* animalDeath3;
	Junk2DSprite* animalDeath4;

	Junk2DSprite* signPost;

	Junk2DSprite* Tree2;
	Junk2DSprite* Tree3;
	Junk2DSprite* Tree4;

	Junk2DSprite* Tree5;
	////////////////////////////////

	////////////////////////////////
	Junk2DSprite* Monster1;
	Junk2DSprite* Monster2;
	Junk2DSprite* Monster3;
	Junk2DSprite* Tree6;

	Junk2DSprite* House1;

	Junk2DSprite* Tree7;
	Junk2DSprite* DeadMen;
	////////////////////////////////

	////////////////////////////////
	Junk2DSprite* Lanten2;
	Junk2DSprite* Totem1;
	Junk2DSprite* Totem2;
	////////////////////////////////

	////////////////////////////////
	Junk2DSprite* sign1;
	Junk2DSprite* sign2;
	Junk2DSprite* fake1;
	Junk2DSprite* fake2;
	Junk2DSprite* sign3;

	Junk2DSprite* graves;

	Junk2DSprite* Lanten3;
	Junk2DSprite* Lanten4;

	Junk2DSprite* House2;
	Junk2DSprite* House3;

	Junk2DSprite* knife;
	////////////////////////////////

	bool ending = false;

	int eventCount = 0;

	bool colEvent = false;

	bool ShadowEventStart = false;
	bool monsterStart = false;

	int shadowMonsterEvent = 0;
	float MonsterAlpha[3] = { 0, };

	// ���� ��ҵ�
	Junk2DMap* Map;

public:
	Room5();
	virtual ~Room5();

	// ���� �⺻ ���� �Լ���
	void initialize(HWND hwnd);

	void Update();      // Game Ŭ�����κ��� �ݵ�� �������̵� �ؾ��ϴ� ���� �����Լ�
	void render();      // "

						/*void releaseAll();
						void resetAll();*/

};

#endif
