#ifndef _PLAYER_H             
#define _PLAYER_H             
#define WIN32_LEAN_AND_MEAN

#include "..\\Headers\Game.h"

class Player : public Junk2DEntity
{
private:
	int Movespeed = 2;
	int playerSize;

public:
	Player();
	virtual ~Player() {};

	void playerSetting(Graphics* graphics);

	void playerInput(Input* input, Junk2DMap* Map1);
	void getplayerWidth() {
		playerSize = this->getSpriteDataRect().right;
	};
};


#endif