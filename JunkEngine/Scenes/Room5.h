#ifndef _ROOM5_H             
#define _ROOM5_H             
#define WIN32_LEAN_AND_MEAN

#include <fstream>

#include "..\\Headers\Monster.h"
#include "..\\Headers\Game.h"

// 메인 게임 클래스, Game클래스로 부터 상속 받음
class Room5 : public Game
{
private:
	ObjectManager* objectManager;

	//// 씬의 기본 구성 요소들 ////
	Player* player;
	ItemSlot* itemSlot;
	Cursor* cursor;
	Junk2DFont *font;
	TextWindow *textWindow;
	Fade* fade;

	Junk2DSprite* filter;
	Junk2DSprite* shadows;
	Junk2DSprite* gameOver;
	////////////////////////////////
	Junk2DSprite* backfance;
	Junk2DSprite* frontfance;

	Junk2DSprite* House0;
	Junk2DSprite* Tree0;

	Monster* mop1;
	Monster* mop2;
	Monster* mop3;
	Monster* mop4;
	Monster* mop5;

	Monster* mop6;
	Monster* mop7;
	Monster* mop8;
	Monster* mop9;

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

	Junk2DSprite* itemSprite[4];

	bool start = false;
	bool firstlan = false;
	bool ending = false;

	int eventCount = 0;
	 
	bool colEvent = false;

	int monsterStart = 0;
	int monsterStart2 = false;
	bool KeySw = false;
	bool KnifeSw = false;
	bool HouseEvent = false;

	bool tmpSw = true;
	
	int TotemEvent = 0;
	int ShadowEventStart = 0;

	int shadowMonsterEvent = 0;
	int monsterStart3 = 0;
	float MonsterAlpha[3] = { 0, };

	float MonsterTime = 0;
	float MonsterTime2 = 0;
	float MonsterTime3 = 0;

	int MonsterAlpha1 = 255;
	int MonsterAlpha2 = 255;
	int MonsterAlpha3 = 255;

	float MonsterStartTime = 0;
	float TotemTime = 0;
	
	int gameOverAl = 0;
	bool gameOverSw = false;

	float LantenAlpha = 0;

	int saveX, saveY;

	int item[4] = { 0, };
	int storyText[10] = {0, };

	// 게임 요소들
	Junk2DMap* Map;

public:
	Room5();
	virtual ~Room5();

	// 게임 기본 구성 함수들
	void initialize(HWND hwnd);

	void Update();      // Game 클래스로부터 반드시 오버라이딩 해야하는 순수 가상함수
	void render();      // "

	void Save();

	void HuntPlayer(Monster* monster);

	//void GameOver();
						/*void releaseAll();
						void resetAll();*/

};

#endif
