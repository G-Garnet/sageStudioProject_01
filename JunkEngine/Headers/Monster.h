#ifndef _MONSTER_H      
#define _MONSTER_H             
#define WIN32_LEAN_AND_MEAN

#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>

#include "..\\Headers\Game.h"

const int dir = 4;

class Monster : public Junk2DEntity
{
private:
	const int Movespeed = 1;

	int mapSize;
	int motionSW;
	bool inputSW;

	int moveCounter = 0;

	int Dir_;

	Junk2DMap* map;
	int moveRoute[100];


public:

	// 게임 데이터들
	int m_PosX;
	int m_PosY;

	Monster();
	virtual ~Monster() {};

	void findPlayer(int playerX, int playerY);
	int FindPath(int xStart, int yStart, int xEnd, int yEnd);

	void MonseterSetting(Graphics* graphics);

	void setMap(Junk2DMap *map) { this->map = map; };
};

class node
{
private:
	int xPos;
	int yPos;
	int level;
	int priority;

public:
	node(int xp, int yp, int d, int p) {
		xPos = xp; yPos = yp; level = d; priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority() {
		priority = level;
	}

	void nextLevel() {
		level += 1;
	}


};


#endif