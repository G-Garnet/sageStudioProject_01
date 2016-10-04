#include "Player.h"

Player::Player()
{

}

void Player::playerSetting(Graphics* graphics)
{
	this->initialize(graphics, "..\\Resources\\Player\\Walk.png", 218, 398, 1);
	this->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	this->setLoop(true);
	this->setActive(true);
	this->setCollisionType(Junk2DentityNS::BOX);
	this->setAnimation(0, 0, 0, 3.0f);

	this->getplayerWidth();
	this->setEdge(0, 150, 218, 398);

	this->setXY(640,270);
}

void Player::playerInput(Input* input, Junk2DMap* Map1)
{
	// �÷��̾� �̵� Ŭ����
	// ���� �÷��̾� Ŭ������ ���� ��üȭ ���Ѽ� �̵��� ����
	if (input->isKeyDown(VK_DOWN)) {
		this->setY(this->getY() + Movespeed / 2);
		if (this->getY() >= GAME_HEIGHT - 390) {
			this->setY(this->getY() - Movespeed / 2);
		}
	}
	if (input->isKeyDown(VK_UP)) {
		this->setY(this->getY() - Movespeed / 2);
		if (this->getY() <= GAME_HEIGHT / 2 - 200) {
			this->setY(this->getY() + Movespeed / 2);
		}

		if (this->getX() - Movespeed <
			(GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
			this->setX(0 + (GAME_HEIGHT - 188 - this->getY() * 1.6f));
		}

		else if (this->getX() + playerSize + Movespeed >
			GAME_WIDTH - (GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
			this->setX((GAME_WIDTH - playerSize) - (GAME_HEIGHT - 188 - this->getY() * 1.6f));
		}
	}

	if (input->isKeyDown(VK_RIGHT)) {
		if (Map1->getMapX() < -mapSize || this->getX() < GAME_WIDTH / 2) {
			if (this->getX() + playerSize + Movespeed <
				GAME_WIDTH - (GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
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
				0 + (GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
				this->setX(this->getX() - Movespeed);
			}
		}
		else {
			Map1->mapMove(Movespeed, 0);
		}
		this->update(0.05f);
	}


	//if (input->isKeyDown(VK_ESCAPE)) {
	//	exit(0);
	//}

	//////////////////////////////////////////////////////////////////
	// ���÷��̾� Ŭ������ �̵�
}
