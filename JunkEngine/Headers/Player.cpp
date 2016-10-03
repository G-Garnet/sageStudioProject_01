#include "Player.h"

Player::Player()
{
	
}

void Player::playerSetting(Graphics* graphics)
{
	this->initialize(graphics, "..\\Resources\\spritesheet.png", 240, 210, 2);
	this->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	this->setLoop(true);
	this->setActive(true);
	this->setCollisionType(Junk2DentityNS::BOX);
	this->setAnimation(0, 3, 0, 3.0f);

	this->getplayerWidth();
}

void Player::playerInput(Input* input, Junk2DMap* Map1)
{
	// 플레이어 이동 클래스
	// 전부 플레이어 클래스로 만들어서 객체화 시켜서 이동할 예정
	if (input->isKeyDown(VK_DOWN)) {
		this->setY(this->getY() + Movespeed / 2);
		if (this->getY() >= GAME_HEIGHT - 200) {
			this->setY(this->getY() - Movespeed / 2);
		}
	}
	if (input->isKeyDown(VK_UP)) {
		this->setY(this->getY() - Movespeed / 2);
		if (this->getY() <= GAME_HEIGHT / 2 - 24) {
			this->setY(this->getY() + Movespeed / 2);
		}

		if (this->getX() - Movespeed <
			(GAME_HEIGHT - this->getY() * 1.5f)) {
			this->setX(0 + (GAME_HEIGHT - this->getY() * 1.5f));
		}

		else if (this->getX() + playerSize + Movespeed >
			GAME_WIDTH - (GAME_HEIGHT - this->getY() * 1.5f)) {
			this->setX((GAME_WIDTH - playerSize) - (GAME_HEIGHT - this->getY() * 1.5f));
		}
	}

	if (input->isKeyDown(VK_RIGHT)) {
		if (Map1->getMapX() < -mapSize || this->getX() < GAME_WIDTH / 2) {
			if (this->getX() + playerSize + Movespeed <
				GAME_WIDTH - (GAME_HEIGHT - this->getY() * 1.5f)) {
				this->setX(this->getX() + Movespeed);
			}
		}
		else {
			Map1->mapMove(-Movespeed, 0);
		}
		this->update(0.05f);
	}
	if (input->isKeyDown(VK_LEFT)) {
		if ((Map1->getMapX() >= 0 || this->getX() > GAME_WIDTH / 2)) {
			if (this->getX() - Movespeed >
				0 + (GAME_HEIGHT - this->getY() * 1.5f)) {
				this->setX(this->getX() - Movespeed);
			}
		}
		else {
			Map1->mapMove(Movespeed, 0);
		}
		this->update(0.05f);
	}


	if (input->isKeyDown(VK_ESCAPE)) {
		exit(0);
	}

	//////////////////////////////////////////////////////////////////
	// ㄴ플레이어 클래스로 이동
}
