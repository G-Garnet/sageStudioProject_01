#ifndef _PLAYER_H             
#define _PLAYER_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

class Player : public Junk2DEntity
{
private:
	const int Movespeed = 1;

	int playerSize;
	int mapSize;
	int motionSW;
	bool inputSW;

	int Dir_;

	int moveCounter = 0;

	Junk2DSprite* lanten;

public:
	int nowDir_;

	// 게임 데이터들
	static int inCounter[100];
	static int Item[10];
	static int p_PosX;
	static int p_PosY;
	static int p_PosScene;	

	Player();
	virtual ~Player() {};

	void playerSetting(Graphics* graphics);
	void setMapszie(int a) { mapSize = a; };
	void setInputSW(bool a) { inputSW = a; };

	void playerInput(Input* input, Junk2DMap* Map1);
	void getplayerWidth() {
		playerSize = this->getSpriteDataRect().right;
	};

	void playerItemIn(int itemCode);
	void playerItemOut(int itemCode);

	void setLanten(Junk2DSprite* lanten);
};


#endif